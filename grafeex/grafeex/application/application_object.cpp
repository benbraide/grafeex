#include "application_object.h"

#include "../window/modal_dialog_window.h"
#include "../controls/control_object.h"
#include "../messaging/command_message_event_handler.h"

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
		return create_(owner, info);
	}, 1);
}

grafeex::application::object::unit_ptr_type grafeex::application::object::set_timer(window_type &owner,
	unit_ptr_type id, uint_type duration){
	return execute<unit_ptr_type>([&]() -> unit_ptr_type{
		return ::SetTimer(owner, id, duration, nullptr);
	}, 1);
}

bool grafeex::application::object::kill_timer(window_type &owner, unit_ptr_type id){
	return execute<bool>([&]() -> bool{
		return (::KillTimer(owner, id) != FALSE);
	}, 1);
}

grafeex::application::object::instance_type grafeex::application::object::get_instance() const{
	return instance_;
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

grafeex::application::object::result_type CALLBACK grafeex::application::object::entry(hwnd_type::value_type window_handle,
	uint_type msg, wparam_type wparam, lparam_type lparam){
	auto target = hwnd_type(window_handle).get_owner();
	if (target == nullptr){//Unidentified window
		instance->stored_message_info.is_active = false;
		return ::CallWindowProcW(::DefWindowProcW, window_handle, msg, wparam, lparam);
	}

	auto is_modal = (instance->modal_ != nullptr);
	if (is_modal && dynamic_cast<threading::modal_loop *>(instance->modal_)->consume(*target, msg, wparam, lparam))
		return 0;//Message consumed

	auto is_sent = !is_modal ? instance->is_sent_() : instance->modal_->is_sent_();
	auto &cache = !is_modal ? instance->cache_ : instance->modal_->cache_;

	if (is_sent || (!is_sent && cache.code() != msg)){//Sent on same thread
		dword_type time;
		point_type mouse_position;

		if (instance->stored_message_info.is_active){
			instance->stored_message_info.is_active = false;
			time = instance->stored_message_info.time;
			mouse_position = instance->stored_message_info.mouse_position;
		}
		else{//No stored info
			time = 0;
			::GetCursorPos(mouse_position);//Get current mouse position
		}

		msg_type msg_object(msg_type::value_type{//Populate message
			window_handle,
			msg,
			wparam,
			lparam,
			time,
			mouse_position
		});

		return instance->dispatch_(msg_object, is_sent, *target);
	}

	instance->status_.is_posted = false;
	return instance->dispatch_(cache, is_sent, *target);
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
	::GetSystemMetrics;

	default_font = ::CreateFontIndirectW(&metrics.lfMessageFont);
}

grafeex::application::object *grafeex::application::object::instance;

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
	return top_level_windows_.empty();
}

bool grafeex::application::object::is_dialog_message_(){
	return (active_dialog_ != nullptr && cache_.is_dialog(*active_dialog_));
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

void grafeex::application::object::init_(){
	typedef std::wstring::size_type size_type;

	instance = this;
	if ((instance_ = class_.instance()) == nullptr)
		class_.instance(instance_ = ::GetModuleHandleW(nullptr));

	common::random_string random_string;
	::GetClassInfoExW(nullptr, L"#32770", dialog_class_);

	dialog_class_.styles(dialog_class_.styles() | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS);
	dialog_class_.procedure(entry);
	dialog_class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));
	dialog_class_.instance(instance_);
	dialog_class_.create();

	if (class_.name().empty())//Use a random string
		class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));

	if (class_.cursor() == nullptr)
		class_.cursor(dialog_class_.cursor());

	class_.create();
	d2d_factory->GetDesktopDpi(&d2d_dpi_scale.x, &d2d_dpi_scale.y);
	d2d_dpi_scale.x /= 96.0f;
	d2d_dpi_scale.y /= 96.0f;

	create_default_font();
	create_dispatchers_();

	messaging::static_command_event_handler::create_forwarder_list();
}

grafeex::application::object::hwnd_type grafeex::application::object::create_(window_type &owner, const create_info_type &info){
	auto hook = ::SetWindowsHookExW(WH_CBT, hook_, nullptr, id_);//Install hook to intercept window creation

	auto &target_default_class = (dynamic_cast<window::dialog *>(&owner) != nullptr) ? dialog_class_ : class_;
	auto target_class = (info.lpszClass == nullptr) ? target_default_class.operator const wchar_t *() : info.lpszClass;

	auto value = ::CreateWindowExW(
		info.dwExStyle,
		target_class,
		info.lpszName,
		info.style,
		info.x,
		info.y,
		info.cx,
		info.cy,
		info.hwndParent,
		info.hMenu,
		(info.hInstance == nullptr) ? instance_ : info.hInstance,
		recent_owner_ = reinterpret_cast<void *>(&owner)
	);

	::UnhookWindowsHookEx(hook);//Uninstall hook
	return value;
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
	GAPP_DISPATCH(WM_CANCELMODE, cancel_mode_event);
	GAPP_DISPATCH(WM_ENABLE, enable_event);

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
}

void grafeex::application::object::app_activate_(messaging::activate_app_event &e){}

grafeex::application::object::result_type CALLBACK grafeex::application::object::hook_(int code, wparam_type wparam, lparam_type lparam){
	if (code == HCBT_CREATEWND){//Respond to window creation
		auto info = reinterpret_cast<create_hook_info_type *>(lparam)->lpcs;
		if (instance->recent_owner_ != nullptr && info->lpCreateParams == instance->recent_owner_){//Ensure target is valid
			auto owner_window = reinterpret_cast<window_type *>(instance->recent_owner_);
			hwnd_type target_hwnd(reinterpret_cast<hwnd_type::value_type>(wparam));

			target_hwnd.set_data(owner_window);//Store window object in handle
			if (dynamic_cast<window::controls::object *>(owner_window) != nullptr)//Replace window procedure
				target_hwnd.set_data<procedure_type>(&object::entry, hwnd_type::data_index::procedure);

			instance->recent_owner_ = nullptr;//Reset
		}
	}

	return ::CallNextHookEx(nullptr, code, wparam, lparam);
}
