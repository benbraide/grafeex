#include "command_link_control.h"

grafeex::window::controls::command_link::command_link(){
	reset_persistent_styles_();
}

grafeex::window::controls::command_link::command_link(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(parent, label, offset, padding);
}

grafeex::window::controls::command_link::command_link(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(sibling, label, offset, padding);
}

grafeex::window::controls::command_link::~command_link(){
	destroy();
}

grafeex::window::controls::command_link &grafeex::window::controls::command_link::note(const std::wstring &value){
	value_.send_message(BCM_SETNOTE, 0, (note_ = value).c_str());
	return *this;
}

const std::wstring &grafeex::window::controls::command_link::note() const{
	return note_;
}

void grafeex::window::controls::command_link::created_(){
	button::created_();
	if (!note_.empty())
		value_.send_message(BCM_SETNOTE, 0, note_.c_str());
}

void grafeex::window::controls::command_link::reset_persistent_styles_(){
	button::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, BS_COMMANDLINK);
}

grafeex::window::object::size_type grafeex::window::controls::command_link::compute_size_(const std::wstring &label){
	return object::compute_size_(label);
}

grafeex::window::object::size_type grafeex::window::controls::command_link::compute_additional_size_(const std::wstring &label){
	return size_type{};
}
