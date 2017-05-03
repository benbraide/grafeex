#include "static_control.h"

grafeex::window::controls::static_control::static_control()
	: object(control_type::static_){
	reset_persistent_styles_();
}

grafeex::window::controls::static_control::static_control(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &size)
	: object(control_type::static_){
	reset_persistent_styles_();
	create(parent, label, offset, size);
}

grafeex::window::controls::static_control::static_control(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &size)
	: object(control_type::static_){
	reset_persistent_styles_();
	create(sibling, label, offset, size);
}

grafeex::window::controls::static_control::~static_control(){
	destroy();
}

grafeex::window::object::dword_type grafeex::window::controls::static_control::white_listed_styles(bool is_extended) const{
	return (base_type::white_listed_styles(is_extended) | (is_extended ? 0ul : SS_CENTER));
}

bool grafeex::window::controls::static_control::create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &size){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(label, offset, size);
}

bool grafeex::window::controls::static_control::create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &size){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(label, offset, size);
}

grafeex::window::controls::static_control &grafeex::window::controls::static_control::label(const std::wstring &value){
	view().caption(value);
	return *this;
}

const std::wstring &grafeex::window::controls::static_control::label(){
	return view().caption();
}

void grafeex::window::controls::static_control::reset_persistent_styles_(){
	object::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, SS_CENTER);
}
