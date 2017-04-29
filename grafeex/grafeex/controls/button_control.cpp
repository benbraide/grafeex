#include "button_control.h"

grafeex::window::controls::button::button()
	: object(control_type::button, &command_forwarder_list_, &notify_forwarder_list_){
	reset_persistent_styles_();
}

grafeex::window::controls::button::button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding)
	: object(control_type::button, &command_forwarder_list_, &notify_forwarder_list_){
	reset_persistent_styles_();
	create(parent, label, offset, padding);
}

grafeex::window::controls::button::button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding)
	: object(control_type::button, &command_forwarder_list_, &notify_forwarder_list_){
	reset_persistent_styles_();
	create(sibling, label, offset, padding);
}

grafeex::window::controls::button::~button(){
	destroy();
}

grafeex::window::object::dword_type grafeex::window::controls::button::white_listed_styles(bool is_extended) const{
	return (base_type::white_listed_styles(is_extended) | (is_extended ? 0ul : general_styles));
}

grafeex::window::controls::button::style_type &grafeex::window::controls::button::style(){
	return *dynamic_cast<style_type *>(get_style_().get());
}

bool grafeex::window::controls::button::create(object_type &parent, const std::wstring &label, const point_type &offset,
	const size_type &padding){
	insert_into_parent_(parent);
	return create_(label, offset, padding);
}

bool grafeex::window::controls::button::create(const sibling_type &sibling, const std::wstring &label, const point_type &offset,
	const size_type &padding){
	insert_into_parent_(sibling);
	return create_(label, offset, padding);
}

grafeex::window::controls::button &grafeex::window::controls::button::label(const std::wstring &value){
	view().caption(value);
	return *this;
}

const std::wstring &grafeex::window::controls::button::label(){
	return view().caption();
}

grafeex::window::controls::button &grafeex::window::controls::button::padding(const size_type &value){
	padding_ = value;
	update_size_();
	return *this;
}

const grafeex::window::object::size_type &grafeex::window::controls::button::padding(){
	return padding_;
}

void grafeex::window::controls::button::on_set_font(messaging::set_font_event &e){
	object::on_set_font(e);
	e.handle();
	update_size_();
}

void grafeex::window::controls::button::on_set_text(messaging::set_text_event &e){
	object::on_set_text(e);
	e.handle();
	update_size_();
}

void grafeex::window::controls::button::reset_persistent_styles_(){
	object::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, BS_FLAT | BS_CENTER | BS_VCENTER);
}

grafeex::window::object::style_ptr_type grafeex::window::controls::button::get_style_(){
	return create_style_<style_type>();
}

bool grafeex::window::controls::button::create_(const std::wstring &label, const point_type &offset,
	const size_type &padding){
	padding_ = padding;
	return object::create_(label, offset, size_type{});
}

grafeex::window::object::size_type grafeex::window::controls::button::compute_size_(const std::wstring &label){
	size_type size;
	Button_GetIdealSize(value_, size.operator SIZE *());
	return (size + (padding_ * 2));
}
