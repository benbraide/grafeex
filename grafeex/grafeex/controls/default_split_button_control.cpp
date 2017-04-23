#include "default_split_button_control.h"

grafeex::window::controls::default_split_button::default_split_button(){
	reset_persistent_styles_();
}

grafeex::window::controls::default_split_button::default_split_button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(parent, label, offset, padding);
}

grafeex::window::controls::default_split_button::default_split_button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(sibling, label, offset, padding);
}

grafeex::window::controls::default_split_button::~default_split_button(){
	destroy();
}

void grafeex::window::controls::default_split_button::reset_persistent_styles_(){
	button::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, BS_DEFSPLITBUTTON);
}
