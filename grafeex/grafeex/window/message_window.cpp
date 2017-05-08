#include "message_window.h"

grafeex::window::message::message(bool create){
	if (create)
		this->create();
}

grafeex::window::message::~message(){
	destroy();
}

grafeex::window::object::dword_type grafeex::window::message::black_listed_styles(bool is_extended) const{
	return ~0ul;
}

bool grafeex::window::message::create(){
	return create_(L"", point_type{}, size_type{});
}

void grafeex::window::message::reset_persistent_styles_(){
	persistent_styles_ = {};
}

grafeex::window::object::hwnd_type grafeex::window::message::get_parent_handle_(){
	return HWND_MESSAGE;
}
