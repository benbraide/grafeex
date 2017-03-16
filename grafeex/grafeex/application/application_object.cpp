#include "application_object.h"

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

/*
grafeex::application::object::hwnd_type grafeex::application::object::create(window_type &owner, const create_info_type &info){
	return execute<hwnd_type>([&]() -> hwnd_type{
		return create_(owner, info);
	}, 1);
}*/

grafeex::application::object::instance_type grafeex::application::object::get_instance() const{
	return instance_;
}

grafeex::application::object::result_type CALLBACK grafeex::application::object::entry(hwnd_type::value_type window_handle,
	uint_type msg, wparam_type wparam, lparam_type lparam){
	return 0;
}

grafeex::application::object *grafeex::application::object::instance;

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

/*
grafeex::application::object::hwnd_type grafeex::application::object::create_(window_type &owner, const create_info_type &info){
	auto hook = ::SetWindowsHookExW(WH_CBT, hook_, nullptr, id_);
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
		reinterpret_cast<void *>(&owner)
	);

	::UnhookWindowsHookEx(hook);
	return value;
}*/

void grafeex::application::object::create_dispatchers_(){
	typedef messaging::scope_event::option scope_option_type;
	typedef messaging::typed_scope_event<scope_option_type::create> nc_create_event_type;
	typedef messaging::typed_scope_event<scope_option_type::create | scope_option_type::client> create_event_type;
	typedef messaging::typed_scope_event<scope_option_type::nil> nc_destroy_event_type;
	typedef messaging::typed_scope_event<scope_option_type::client> destroy_event_type;

	typedef messaging::typed_style_event<true> changing_style_event_type;
	typedef messaging::typed_style_event<false> changed_style_event_type;

	dispatcher_list_[WM_NCCREATE] = std::make_shared<messaging::event_dispatcher<nc_create_event_type> >();
	dispatcher_list_[WM_CREATE] = std::make_shared<messaging::event_dispatcher<create_event_type> >();
	dispatcher_list_[WM_NCDESTROY] = std::make_shared<messaging::event_dispatcher<nc_destroy_event_type> >();
	dispatcher_list_[WM_DESTROY] = std::make_shared<messaging::event_dispatcher<destroy_event_type> >();

	dispatcher_list_[WM_CLOSE] = std::make_shared<messaging::event_dispatcher<messaging::close_event> >();

	dispatcher_list_[WM_ACTIVATE] = std::make_shared<messaging::event_dispatcher<messaging::activate_event> >();
	dispatcher_list_[WM_ENABLE] = std::make_shared<messaging::event_dispatcher<messaging::enable_event> >();

	dispatcher_list_[WM_STYLECHANGING] = std::make_shared<messaging::event_dispatcher<changing_style_event_type> >();
	dispatcher_list_[WM_STYLECHANGED] = std::make_shared<messaging::event_dispatcher<changed_style_event_type> >();
}

grafeex::application::object::result_type CALLBACK grafeex::application::object::hook_(int code, wparam_type wparam, lparam_type lparam){
	/*if (code == HCBT_CREATEWND){
	auto window_handle = reinterpret_cast<hwnd_type::value_type>(wparam);
	if (current_window != nullptr){
	(*current_window->get_handle() = window_handle).set_data(current_window);
	if (reinterpret_cast<create_hook_info_type *>(lparam)->lpcs->lpCreateParams != nullptr)
	wnd(window_handle).set_data<procedure_type>(&object::entry, wnd_types::data_index::procedure);//Replace procedure
	current_window = nullptr;
	}
	}*/

	return ::CallNextHookEx(nullptr, code, wparam, lparam);
}
