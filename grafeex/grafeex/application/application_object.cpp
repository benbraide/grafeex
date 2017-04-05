#include "application_object.h"
#include "../window/window_object.h"

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
	if (message_dispatcher == instance->dispatcher_list_.end()){//Unrecognized message

	}
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
	return (active_dialog_ != nullptr && cache_.is_dialog(active_dialog_));
}

grafeex::application::object::hwnd_type grafeex::application::object::create_(window_type &owner, const create_info_type &info){
	auto hook = ::SetWindowsHookExW(WH_CBT, hook_, nullptr, id_);//Install hook to intercept window creation
	auto value = ::CreateWindowExW(
		info.dwExStyle,
		(info.lpszClass == nullptr) ? class_ : info.lpszClass,
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
	dispatcher_list_[WM_NCCREATE] = std::make_shared<messaging::event_dispatcher<messaging::nc_create_event> >();
	dispatcher_list_[WM_CREATE] = std::make_shared<messaging::event_dispatcher<messaging::create_event> >();
	dispatcher_list_[WM_NCDESTROY] = std::make_shared<messaging::event_dispatcher<messaging::nc_destroy_event> >();
	dispatcher_list_[WM_DESTROY] = std::make_shared<messaging::event_dispatcher<messaging::destroy_event> >();

	dispatcher_list_[WM_CLOSE] = std::make_shared<messaging::event_dispatcher<messaging::close_event> >();

	dispatcher_list_[WM_ACTIVATE] = std::make_shared<messaging::event_dispatcher<messaging::activate_event> >();
	dispatcher_list_[WM_ENABLE] = std::make_shared<messaging::event_dispatcher<messaging::enable_event> >();

	dispatcher_list_[WM_STYLECHANGING] = std::make_shared<messaging::event_dispatcher<messaging::changing_style_event> >();
	dispatcher_list_[WM_STYLECHANGED] = std::make_shared<messaging::event_dispatcher<messaging::changed_style_event> >();

	dispatcher_list_[WM_SHOWWINDOW] = std::make_shared<messaging::event_dispatcher<messaging::visibility_event> >();

	dispatcher_list_[WM_NCPAINT] = std::make_shared<messaging::event_dispatcher<messaging::nc_paint_event> >();
	dispatcher_list_[WM_PAINT] = std::make_shared<messaging::event_dispatcher<messaging::client_paint_event> >();

	dispatcher_list_[WM_CONTEXTMENU] = std::make_shared<messaging::event_dispatcher<messaging::context_menu_event> >();
	dispatcher_list_[WM_INITMENU] = std::make_shared<messaging::event_dispatcher<messaging::menu_init_event> >();
	dispatcher_list_[WM_INITMENUPOPUP] = std::make_shared<messaging::event_dispatcher<messaging::menu_popup_init_event> >();
	dispatcher_list_[WM_UNINITMENUPOPUP] = std::make_shared<messaging::event_dispatcher<messaging::menu_popup_uninit_event> >();
	dispatcher_list_[WM_NEXTMENU] = std::make_shared<messaging::event_dispatcher<messaging::menu_next_event> >();
	dispatcher_list_[WM_MENURBUTTONUP] = std::make_shared<messaging::event_dispatcher<messaging::menu_rbutton_up_event> >();
	dispatcher_list_[WM_MENUCOMMAND] = std::make_shared<messaging::event_dispatcher<messaging::menu_command_event> >();
	dispatcher_list_[WM_MENUSELECT] = std::make_shared<messaging::event_dispatcher<messaging::menu_select_event> >();
}

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
