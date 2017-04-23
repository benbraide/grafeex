#include "control_styles.h"
#include "../window/window_object.h"

grafeex::window::controls::button_style::button_style(object_type &object)
	: base_type(object){}

grafeex::window::controls::button_style::~button_style() = default;

grafeex::window::controls::button_style &grafeex::window::controls::button_style::flat(bool enabled){
	update_(BS_FLAT, enabled, false);
	return *this;
}

bool grafeex::window::controls::button_style::flat() const{
	return has_(BS_FLAT, false);
}

grafeex::window::controls::button_style &grafeex::window::controls::button_style::multi_line(bool enabled){
	update_(BS_MULTILINE, enabled, false);
	return *this;
}

bool grafeex::window::controls::button_style::multi_line() const{
	return has_(BS_MULTILINE, false);
}

grafeex::window::controls::button_style &grafeex::window::controls::button_style::text_alignment(alignment_type value){
	auto active = update_info_.active;
	if (!active)
		begin();

	update_(BS_CENTER | BS_VCENTER, false, false);
	update_(static_cast<dword_type>(value), true, false);

	if (!active)
		end();

	return *this;
}

grafeex::window::controls::button_style::alignment_type grafeex::window::controls::button_style::text_alignment() const{
	auto styles = basic();
	auto value = alignment_type::nil;

	if (GRAFEEX_IS(styles, BS_CENTER))
		GRAFEEX_SET(value, alignment_type::center);
	else if (GRAFEEX_IS(styles, BS_RIGHT))
		GRAFEEX_SET(value, alignment_type::right);
	else
		GRAFEEX_SET(value, alignment_type::left);

	if (GRAFEEX_IS(styles, BS_VCENTER))
		GRAFEEX_SET(value, alignment_type::vcenter);
	else if (GRAFEEX_IS(styles, BS_BOTTOM))
		GRAFEEX_SET(value, alignment_type::bottom);
	else
		GRAFEEX_SET(value, alignment_type::top);

	return value;
}
