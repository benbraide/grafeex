#include "msg_wrapper.h"

grafeex::wrappers::msg::msg()
	: base_type(value_type{}){}

grafeex::wrappers::msg::msg(const value_type &value)
	: base_type(value){}

bool grafeex::wrappers::msg::translate() const{
	return (::TranslateMessage(&value_) != FALSE);
}

grafeex::wrappers::msg::result_type grafeex::wrappers::msg::dispatch() const{
	return (::DispatchMessageW(&value_) != FALSE);
}

grafeex::wrappers::msg::result_type grafeex::wrappers::msg::send() const{
	return hwnd(value_.hwnd).send_message(value_.message, value_.wParam, value_.lParam);
}

grafeex::wrappers::msg &grafeex::wrappers::msg::code(uint_type value){
	value_.message = value;
	return *this;
}

grafeex::wrappers::msg::uint_type grafeex::wrappers::msg::code() const{
	return value_.message;
}

grafeex::wrappers::msg &grafeex::wrappers::msg::owner(hwnd value){
	value_.hwnd = value;
	return *this;
}

grafeex::wrappers::hwnd grafeex::wrappers::msg::owner() const{
	return value_.hwnd;
}

grafeex::wrappers::msg &grafeex::wrappers::msg::time(dword_type value){
	value_.time = value;
	return *this;
}

grafeex::wrappers::msg::dword_type grafeex::wrappers::msg::time() const{
	return value_.time;
}

grafeex::wrappers::msg &grafeex::wrappers::msg::mouse_position(const structures::point &value){
	value_.pt = value;
	return *this;
}

grafeex::structures::point grafeex::wrappers::msg::mouse_position() const{
	return value_.pt;
}

bool grafeex::wrappers::msg::is_quit() const{
	return (value_.message == WM_QUIT);
}

bool grafeex::wrappers::msg::is_dialog(hwnd target){
	return (::IsDialogMessageW(target, &value_) != FALSE);
}
