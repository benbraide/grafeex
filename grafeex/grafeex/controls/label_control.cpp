#include "label_control.h"

grafeex::window::controls::label::label()
	: object(control_type::static_){
	reset_persistent_styles_();
}

grafeex::window::controls::label::label(object_type &parent, const std::wstring &label, const point_type &offset)
	: object(control_type::static_){
	reset_persistent_styles_();
	create(parent, label, offset);
}

grafeex::window::controls::label::label(const sibling_type &sibling, const std::wstring &label, const point_type &offset)
	: object(control_type::static_){
	reset_persistent_styles_();
	create(sibling, label, offset);
}

grafeex::window::controls::label::~label(){
	destroy();
}

bool grafeex::window::controls::label::create(object_type &parent, const std::wstring &label, const point_type &offset){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(label, offset, size_type{});
}

bool grafeex::window::controls::label::create(const sibling_type &sibling, const std::wstring &label, const point_type &offset){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(label, offset, size_type{});
}

grafeex::window::controls::label &grafeex::window::controls::label::text(const std::wstring &value){
	view().caption(value);
	return *this;
}

const std::wstring &grafeex::window::controls::label::text(){
	return view().caption();
}

void grafeex::window::controls::label::on_set_font(messaging::set_font_event &e){
	object::on_set_font(e);
	e.handle();
	update_size_();
}

void grafeex::window::controls::label::on_set_text(messaging::set_text_event &e){
	object::on_set_text(e);
	e.handle();
	update_size_();
}

void grafeex::window::controls::label::reset_persistent_styles_(){
	object::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, SS_SIMPLE);
}

grafeex::window::object::size_type grafeex::window::controls::label::compute_additional_size_(const std::wstring &label){
	return size_type{ 5, 5 };
}
