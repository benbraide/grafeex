#include "application_object.h"
#include "../window/dialog_window.h"

grafeex::application::object::~object(){}

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

	auto is_sent = instance->is_sent_();
	instance->status_.is_posted = false;

	if (is_sent){//Sent on same thread
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

		instance->cache_ = msg_type(msg_type::value_type{//Populate message
			window_handle,
			msg,
			wparam,
			lparam,
			time,
			mouse_position
		});
	}

	messaging::object meesage_object(instance->cache_, is_sent, target->previous_procedure_);
	auto message_dispatcher = instance->dispatcher_list_.find(instance->cache_.code());
	if (message_dispatcher == instance->dispatcher_list_.end())//Unrecognized message
		instance->dispatcher_list_[WM_NULL]->dispatch(meesage_object);
	else//Dispatch message
		message_dispatcher->second->dispatch(meesage_object);

	return meesage_object.handle().value();
}

grafeex::application::object *grafeex::application::object::instance;

grafeex::application::object::factory_type grafeex::application::object::d2d_factory;

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

grafeex::application::object::hwnd_type grafeex::application::object::create_(window_type &owner, const create_info_type &info){
	auto hook = ::SetWindowsHookExW(WH_CBT, hook_, nullptr, id_);//Install hook to intercept window creation
	auto is_dialog = (dynamic_cast<window::dialog *>(&owner) != nullptr);
	if (is_dialog)
		pending_dialog_info_ = { &owner, point_type{ info.x, info.y }, size_type{ info.cx, info.cy } };

	auto &target_class = is_dialog ? dialog_class_ : class_;
	auto value = ::CreateWindowExW(
		info.dwExStyle,
		(info.lpszClass == nullptr) ? target_class : info.lpszClass,
		info.lpszName,
		info.style,
		is_dialog ? 0 : info.x,
		is_dialog ? 0 : info.y,
		is_dialog ? 0 : info.cx,
		is_dialog ? 0 : info.cy,
		info.hwndParent,
		info.hMenu,
		(info.hInstance == nullptr) ? instance_ : info.hInstance,
		recent_owner_ = reinterpret_cast<void *>(&owner)
	);

	::UnhookWindowsHookEx(hook);//Uninstall hook
	if (is_dialog)//Clear pending info
		pending_dialog_info_ = {};

	return value;
}

void grafeex::application::object::create_dispatchers_(){
	GAPP_DISPATCH(WM_NULL, message_event);

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

	GAPP_DISPATCH(WM_ERASEBKGND, erase_background_event);
	GAPP_DISPATCH(WM_NCPAINT, nc_paint_event);
	GAPP_DISPATCH(WM_PAINT, client_paint_event);

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
}

void grafeex::application::object::app_activate_(messaging::activate_app_event &e){}

grafeex::application::object::result_type CALLBACK grafeex::application::object::hook_(int code, wparam_type wparam, lparam_type lparam){
	if (code == HCBT_CREATEWND){//Respond to window creation
		auto info = reinterpret_cast<create_hook_info_type *>(lparam)->lpcs;
		if (instance->recent_owner_ != nullptr && info->lpCreateParams == instance->recent_owner_){//Ensure target is valid
			auto owner_window = reinterpret_cast<window_type *>(instance->recent_owner_);
			hwnd_type target_hwnd(reinterpret_cast<hwnd_type::value_type>(wparam));

			target_hwnd.set_data(owner_window);//Store window object in handle
			if (owner_window->previous_procedure_ == nullptr)//Replace window procedure
				owner_window->previous_procedure_ = target_hwnd.set_data<procedure_type>(&object::entry, hwnd_type::data_index::procedure);

			owner_window->background_color_;//TODO: Retrieve color from brush inside class
			instance->recent_owner_ = nullptr;//Reset
		}
	}

	return ::CallNextHookEx(nullptr, code, wparam, lparam);
}
