#include "application_object.h"

#include "../window/modal_dialog_window.h"
#include "../controls/control_object.h"

#include "../messaging/command_message_event_handler.h"
#include "../messaging/notify_message_event_handler.h"

grafeex::application::object::object()
	: instance_(nullptr), pool_(GAPP_THREAD_POOL_MIN, GAPP_THREAD_POOL_MAX), window_manager_(*this){
	pump = this;
	instance = this;

	window_manager_.instance = &window_manager_;
	if ((instance_ = window_manager_.class_.instance()) == nullptr)
		window_manager_.class_.instance(instance_ = ::GetModuleHandleW(nullptr));

	d2d_factory->GetDesktopDpi(&d2d_dpi_scale.x, &d2d_dpi_scale.y);
	d2d_dpi_scale.x /= 96.0f;
	d2d_dpi_scale.y /= 96.0f;

	create_default_font();
	create_dispatchers_();
}

grafeex::application::object::~object() = default;

void grafeex::application::object::quit(int exit_code){
	if (threading::get_current_id() != id_){
		scheduler_.add([exit_code]{
			threading::message_queue::post_quit(exit_code);
		});
		queue_.wake_wait();//Release message loop
	}
	else//Same thread
		threading::message_queue::post_quit(exit_code);
}

grafeex::application::object::hwnd_type grafeex::application::object::create(window_type &owner, const create_info_type &info){
	return execute<hwnd_type>([&]() -> hwnd_type{
		return window_manager_.create_(owner, info);
	}, 1);
}

grafeex::application::object::uint_ptr_type grafeex::application::object::set_timer(window_type &owner,
	uint_ptr_type id, uint_type duration){
	return execute<uint_ptr_type>([&]() -> uint_ptr_type{
		return ::SetTimer(owner, id, duration, nullptr);
	}, 1);
}

bool grafeex::application::object::kill_timer(window_type &owner, uint_ptr_type id){
	return execute<bool>([&]() -> bool{
		return (::KillTimer(owner, id) != FALSE);
	}, 1);
}

grafeex::application::object::instance_type grafeex::application::object::get_instance() const{
	return instance_;
}

grafeex::messaging::event_forwarder_base *grafeex::application::object::get_event_forwarder(window_type *target, uint_type code) const{
	if (target == nullptr)
		return nullptr;

	auto control_target = dynamic_cast<window::controls::object *>(target);
	if (control_target == nullptr)
		return nullptr;

	auto list = control_forwarder_list_.find(control_target->type_);
	if (list == control_forwarder_list_.end())
		return nullptr;

	auto forwarder = list->second.find(code);
	return (forwarder == list->second.end()) ? nullptr : forwarder->second.get();
}

void grafeex::application::object::schedule(std::function<void()> method, int priority){
	pump->scheduler_.add(method, priority);
}

bool grafeex::application::object::task(pool_task_type task, bool is_persistent){
	return pool_.add(task, is_persistent);
}

void grafeex::application::object::cache_timer(uint_ptr_type id, timer_type &timer){
	window_manager_.lock_.lock();
	timer_cache_[id] = &timer;
	window_manager_.lock_.unlock();
}

void grafeex::application::object::remove_timer(uint_ptr_type id){
	window_manager_.lock_.lock();
	timer_cache_.erase(id);
	window_manager_.lock_.unlock();
}

grafeex::application::object::timer_type *grafeex::application::object::find_timer(uint_ptr_type id) const{
	window_manager_.lock_.lock();

	timer_type *value = nullptr;
	auto entry = timer_cache_.find(id);
	if (entry != timer_cache_.end())//Found in cache
		value = entry->second;

	window_manager_.lock_.unlock();
	return value;
}

grafeex::application::window_manager &grafeex::application::object::win_manager(){
	return window_manager_;
}

void grafeex::application::object::enable_gdi_manager(bool monitor){
	GRAFEEX_SET(gdi_manager_states_, gdi_manager_state::active);
	if (monitor && GRAFEEX_IS(gdi_manager_states_, gdi_manager_state::monitoring)){
		GRAFEEX_SET(gdi_manager_states_, gdi_manager_state::monitoring);
		gdi::manager::init();
	}
	else if (!monitor){
		GRAFEEX_REMOVE(gdi_manager_states_, gdi_manager_state::monitoring);
		gdi::manager::uninit();
	}
}

void grafeex::application::object::disable_gdi_manager(bool monitor_only){
	if (GRAFEEX_IS(gdi_manager_states_, gdi_manager_state::monitoring)){
		GRAFEEX_REMOVE(gdi_manager_states_, gdi_manager_state::monitoring);
		gdi::manager::uninit();
	}

	if (!monitor_only && !GRAFEEX_IS(gdi_manager_states_, gdi_manager_state::active)){
		GRAFEEX_REMOVE(gdi_manager_states_, gdi_manager_state::active);
		gdi::manager::guard_type guard(gdi::manager::lock_);
		gdi::manager::owner_cache_.clear();
	}
}

bool grafeex::application::object::gdi_manager_is_enabled() const{
	return GRAFEEX_IS(gdi_manager_states_, gdi_manager_state::active);
}

bool grafeex::application::object::gdi_manager_is_monitoring() const{
	return GRAFEEX_IS(gdi_manager_states_, gdi_manager_state::monitoring);
}

grafeex::application::object::d2d_point_type grafeex::application::object::pixel_to_dip(const point_type &value){
	return d2d_point_type{ pixel_to_dip_x(value.x()), pixel_to_dip_y(value.y()) };
}

grafeex::application::object::d2d_size_type grafeex::application::object::pixel_to_dip(const size_type &value){
	return d2d_size_type{ pixel_to_dip_x(value.width()), pixel_to_dip_y(value.height()) };
}

grafeex::application::object::d2d_rect_type grafeex::application::object::pixel_to_dip(const rect_type &value){
	return d2d_rect_type{ pixel_to_dip_x(value.left()), pixel_to_dip_y(value.top()), pixel_to_dip_x(value.right()),
		pixel_to_dip_y(value.bottom()) };
}

grafeex::application::object::point_type grafeex::application::object::dip_to_pixel(const d2d_point_type &value){
	return point_type{ dip_to_pixel_x<int>(value.x), dip_to_pixel_y<int>(value.y) };
}

grafeex::application::object::size_type grafeex::application::object::dip_to_pixel(const d2d_size_type &value){
	return size_type{ dip_to_pixel_x<int>(value.width), dip_to_pixel_y<int>(value.height) };
}

grafeex::application::object::rect_type grafeex::application::object::dip_to_pixel(const d2d_rect_type &value){
	return rect_type{ dip_to_pixel_x<int>(value.left), dip_to_pixel_y<int>(value.top), dip_to_pixel_x<int>(value.right),
		dip_to_pixel_y<int>(value.bottom) };
}

void grafeex::application::object::create_default_font(){
	nc_metrics_type metrics{ sizeof(nc_metrics_type) };
	::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
	default_font = ::CreateFontIndirectW(&metrics.lfMessageFont);
}

grafeex::application::object *grafeex::application::object::instance;

grafeex::threading::object *grafeex::application::object::pump;

grafeex::application::object::factory_type grafeex::application::object::d2d_factory;

grafeex::application::object::write_factory_type grafeex::application::object::d2d_write_factory;

grafeex::application::object::d2d_point_type grafeex::application::object::d2d_dpi_scale = { 1.0f, 1.0f };

grafeex::application::object::font_type grafeex::application::object::default_font;

bool grafeex::application::object::is_filtered_message_() const{
	return false;
}

void grafeex::application::object::dispatch_(){
	if (!is_dialog_message_())
		base_type::dispatch_();
}

bool grafeex::application::object::is_stopped_() const{
	return window_manager_.top_level_windows_.empty();
}

bool grafeex::application::object::is_dialog_message_(){
	return (window_manager_.active_dialog_ != nullptr && cache_.is_dialog(*window_manager_.active_dialog_));
}

grafeex::application::object::result_type grafeex::application::object::dispatch_(msg_type &msg, bool is_sent, window_type &target){
	messaging::object meesage_object(msg, is_sent, target.previous_procedure_);
	auto message_dispatcher = dispatcher_list_.find(msg.code());
	if (message_dispatcher == dispatcher_list_.end())//Unrecognized message
		unhandled_dispatcher_->dispatch(meesage_object);
	else//Dispatch message
		message_dispatcher->second->dispatch(meesage_object);

	return meesage_object.handle().value();
}

void grafeex::application::object::create_dispatchers_(){
	unhandled_dispatcher_ = GAPP_MAKE_DISPATCHER(unhandled_event);
	GAPP_DISPATCH(WM_NULL, null_event);

	GAPP_DISPATCH(WM_NCCREATE, nc_create_event);
	GAPP_DISPATCH(WM_CREATE, create_event);
	GAPP_DISPATCH(WM_NCDESTROY, nc_destroy_event);
	GAPP_DISPATCH(WM_DESTROY, destroy_event);

	GAPP_DISPATCH(WM_CLOSE, close_event);

	GAPP_DISPATCH(WM_ACTIVATEAPP, activate_app_event);
	GAPP_DISPATCH(WM_NCACTIVATE, nc_activate_event);
	GAPP_DISPATCH(WM_ACTIVATE, activate_event);
	GAPP_DISPATCH(WM_MOUSEACTIVATE, mouse_activate_event);
	GAPP_DISPATCH(WM_CANCELMODE, cancel_mode_event);
	GAPP_DISPATCH(WM_ENABLE, enable_event);
	GAPP_DISPATCH(WM_SETFOCUS, set_focus_event);
	GAPP_DISPATCH(WM_KILLFOCUS, kill_focus_event);

	GAPP_DISPATCH(WM_STYLECHANGING, changing_style_event);
	GAPP_DISPATCH(WM_STYLECHANGED, changed_style_event);

	GAPP_DISPATCH(WM_SHOWWINDOW, visibility_event);

	GAPP_DISPATCH(WM_WINDOWPOSCHANGING, changing_position_event);
	GAPP_DISPATCH(WM_WINDOWPOSCHANGED, changed_position_event);

	GAPP_DISPATCH(WM_MOVING, changing_movement_event);
	GAPP_DISPATCH(WM_MOVE, changed_movement_event);

	GAPP_DISPATCH(WM_SIZING, changing_size_event);
	GAPP_DISPATCH(WM_SIZE, changed_size_event);

	GAPP_DISPATCH(WM_GETMINMAXINFO, min_max_event);

	GAPP_DISPATCH(WM_ENTERSIZEMOVE, enter_size_move_event);
	GAPP_DISPATCH(WM_EXITSIZEMOVE, exit_size_move_event);

	GAPP_DISPATCH(WM_QUERYOPEN, query_open_event);
	GAPP_DISPATCH(WM_QUERYDRAGICON, query_drag_icon_event);

	GAPP_DISPATCH(WM_NCHITTEST, hit_test_event);

	GAPP_DISPATCH(WM_ERASEBKGND, erase_background_event);
	GAPP_DISPATCH(WM_NCPAINT, nc_paint_event);
	GAPP_DISPATCH(WM_PAINT, client_paint_event);
	GAPP_DISPATCH(WM_PRINT, print_event);
	GAPP_DISPATCH(WM_PRINTCLIENT, print_client_event);

	GAPP_DISPATCH(WM_CONTEXTMENU, context_menu_event);
	GAPP_DISPATCH(WM_INITMENU, menu_init_event);
	GAPP_DISPATCH(WM_INITMENUPOPUP, menu_popup_init_event);
	GAPP_DISPATCH(WM_UNINITMENUPOPUP, menu_popup_uninit_event);
	GAPP_DISPATCH(WM_NEXTMENU, menu_next_event);
	GAPP_DISPATCH(WM_MENURBUTTONUP, menu_rbutton_up_event);
	GAPP_DISPATCH(WM_MENUCOMMAND, menu_command_event);
	GAPP_DISPATCH(WM_MENUSELECT, menu_select_event);

	GAPP_DISPATCH(WM_THEMECHANGED, theme_changed_event);
	GAPP_DISPATCH(WM_USERCHANGED, user_changed_event);
	GAPP_DISPATCH(WM_INPUTLANGCHANGE, input_language_changed_event);
	GAPP_DISPATCH(WM_INPUTLANGCHANGEREQUEST, input_language_change_request_event);
	GAPP_DISPATCH(WM_DISPLAYCHANGE, display_changed_event);
	GAPP_DISPATCH(WM_CAPTURECHANGED, capture_changed_event);

	GAPP_DISPATCH(WM_COMMAND, command_event);
	GAPP_DISPATCH(WM_NOTIFY, notify_event);

	GAPP_DISPATCH(WM_TIMER, timer_event);

	GAPP_DISPATCH(WM_KEYDOWN, normal_key_down_event);
	GAPP_DISPATCH(WM_KEYUP, normal_key_up_event);
	GAPP_DISPATCH(WM_CHAR, normal_char_event);
	GAPP_DISPATCH(WM_DEADCHAR, normal_dead_char_event);

	GAPP_DISPATCH(WM_SYSKEYDOWN, system_key_down_event);
	GAPP_DISPATCH(WM_SYSKEYUP, system_key_up_event);
	GAPP_DISPATCH(WM_SYSCHAR, system_char_event);
	GAPP_DISPATCH(WM_SYSDEADCHAR, system_dead_char_event);

	GAPP_DISPATCH(WM_NCMOUSELEAVE, mouse_leave_event);
	GAPP_DISPATCH(WM_MOUSELEAVE, mouse_client_leave_event);

	GAPP_DISPATCH(WM_NCMOUSEMOVE, mouse_nc_move_event);
	GAPP_DISPATCH(WM_MOUSEMOVE, mouse_client_move_event);

	GAPP_DISPATCH(WM_NCLBUTTONDOWN, mouse_nc_left_button_down_event);
	GAPP_DISPATCH(WM_LBUTTONDOWN, mouse_client_left_button_down_event);
	GAPP_DISPATCH(WM_NCMBUTTONDOWN, mouse_nc_middle_button_down_event);
	GAPP_DISPATCH(WM_MBUTTONDOWN, mouse_client_middle_button_down_event);
	GAPP_DISPATCH(WM_NCRBUTTONDOWN, mouse_nc_right_button_down_event);
	GAPP_DISPATCH(WM_RBUTTONDOWN, mouse_client_right_button_down_event);

	GAPP_DISPATCH(WM_NCLBUTTONUP, mouse_nc_left_button_up_event);
	GAPP_DISPATCH(WM_LBUTTONUP, mouse_client_left_button_up_event);
	GAPP_DISPATCH(WM_NCMBUTTONUP, mouse_nc_middle_button_up_event);
	GAPP_DISPATCH(WM_MBUTTONUP, mouse_client_middle_button_up_event);
	GAPP_DISPATCH(WM_NCRBUTTONUP, mouse_nc_right_button_up_event);
	GAPP_DISPATCH(WM_RBUTTONUP, mouse_client_right_button_up_event);

	GAPP_DISPATCH(WM_NCLBUTTONDBLCLK, mouse_nc_left_button_dbl_click_event);
	GAPP_DISPATCH(WM_LBUTTONDBLCLK, mouse_client_left_button_dbl_click_event);
	GAPP_DISPATCH(WM_NCMBUTTONDBLCLK, mouse_nc_middle_button_dbl_click_event);
	GAPP_DISPATCH(WM_MBUTTONDBLCLK, mouse_client_middle_button_dbl_click_event);
	GAPP_DISPATCH(WM_NCRBUTTONDBLCLK, mouse_nc_right_button_dbl_click_event);
	GAPP_DISPATCH(WM_RBUTTONDBLCLK, mouse_client_right_button_dbl_click_event);

	GAPP_DISPATCH(WM_MOUSEWHEEL, mouse_vertical_wheel_event);
	GAPP_DISPATCH(WM_MOUSEHWHEEL, mouse_horizontal_wheel_event);

	GAPP_DISPATCH(WM_SETFONT, set_font_event);
	GAPP_DISPATCH(WM_GETFONT, get_font_event);

	GAPP_DISPATCH(WM_SETTEXT, set_text_event);
	GAPP_DISPATCH(WM_GETTEXT, get_text_event);
	GAPP_DISPATCH(WM_GETTEXTLENGTH, get_text_length_event);

	create_command_forwarders_();
	create_notify_forwarders_();
}

void grafeex::application::object::create_command_forwarders_(){
	auto &slist = control_forwarder_list_[control_object_type::static_];
	{//Static commands
		GAPP_CMD_UFORWARD(slist, STN_DISABLE, messaging::static_command_event_handler, disable);
		GAPP_CMD_UFORWARD(slist, STN_ENABLE, messaging::static_command_event_handler, enable);
		GAPP_CMD_UFORWARD(slist, STN_CLICKED, messaging::static_command_event_handler, click);
		GAPP_CMD_UFORWARD(slist, STN_DBLCLK, messaging::static_command_event_handler, dbl_click);
	}

	auto &blist = control_forwarder_list_[control_object_type::button];
	{//Button commands
		GAPP_CMD_UFORWARD(blist, BN_KILLFOCUS, messaging::button_command_event_handler, kill_focus);
		GAPP_CMD_UFORWARD(blist, BN_SETFOCUS, messaging::button_command_event_handler, set_focus);
		GAPP_CMD_UFORWARD(blist, BN_CLICKED, messaging::button_command_event_handler, click);
		GAPP_CMD_UFORWARD(blist, BN_DBLCLK, messaging::button_command_event_handler, dbl_click);
	}
}

void grafeex::application::object::create_notify_forwarders_(){
	auto &blist = control_forwarder_list_[control_object_type::button];
	{//Button notifications
		GAPP_NOT_UFORWARD2(blist, NM_CUSTOMDRAW, messaging::button_notify_event_handler, dword_type, messaging::custom_draw_event, draw);
		GAPP_NOT_VOID_UFORWARD(blist, BCN_DROPDOWN, messaging::button_notify_event_handler, dropdown);
		GAPP_NOT_VOID_UFORWARD(blist, BCN_HOTITEMCHANGE, messaging::button_notify_event_handler, highlight_change);
	}

	auto &ttlist = control_forwarder_list_[control_object_type::tool_tip];
	{//Tooltip notifications
		GAPP_NOT_UFORWARD2(ttlist, NM_CUSTOMDRAW, messaging::tool_tip_notify_event_handler, dword_type, messaging::custom_draw_event, draw);
		GAPP_NOT_UFORWARD2(ttlist, TTN_GETDISPINFOW, messaging::tool_tip_notify_event_handler, const std::wstring &, messaging::tool_tip_get_text_event, get_text);
		GAPP_NOT_UFORWARD(ttlist, TTN_SHOW, messaging::tool_tip_notify_event_handler, bool, show);
		GAPP_NOT_VOID_UFORWARD(ttlist, TTN_POP, messaging::tool_tip_notify_event_handler, hide);
		GAPP_NOT_VOID_UFORWARD(ttlist, TTN_LINKCLICK, messaging::tool_tip_notify_event_handler, link_click);
	}

	auto &tlist = control_forwarder_list_[control_object_type::tab];
	{//Tab notifications
		GAPP_NOT_VOID_UFORWARD(tlist, NM_CLICK, messaging::tab_notify_event_handler, click);
		GAPP_NOT_VOID_UFORWARD(tlist, NM_DBLCLK, messaging::tab_notify_event_handler, dbl_click);
		GAPP_NOT_VOID_UFORWARD(tlist, NM_RCLICK, messaging::tab_notify_event_handler, right_click);
		GAPP_NOT_VOID_UFORWARD(tlist, NM_RDBLCLK, messaging::tab_notify_event_handler, right_dbl_click);
		GAPP_NOT_VOID_UFORWARD(tlist, NM_RELEASEDCAPTURE, messaging::tab_notify_event_handler, capture_release);
		GAPP_NOT_VOID_UFORWARD(tlist, TCN_FOCUSCHANGE, messaging::tab_notify_event_handler, focus_change);
		GAPP_NOT_VOID_UFORWARD(tlist, TCN_KEYDOWN, messaging::tab_notify_event_handler, key_down);
		GAPP_NOT_VOID_UFORWARD(tlist, TCN_SELCHANGE, messaging::tab_notify_event_handler, selection_change);
		GAPP_NOT_UFORWARD(tlist, TCN_SELCHANGING, messaging::tab_notify_event_handler, bool, selection_changing);
	}
}

void grafeex::application::object::app_activate_(messaging::activate_app_event &e){}
