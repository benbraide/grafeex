#include "radio_control_group.h"
#include "radio_control.h"

grafeex::window::controls::radio_group::radio_group()
	: object(control_type::nil){}

grafeex::window::controls::radio_group::radio_group(gui_object_type &parent)
	: object(control_type::nil){
	create(parent);
}

grafeex::window::controls::radio_group::radio_group(const sibling_type &sibling)
	: object(control_type::nil){
	create(sibling);
}

grafeex::window::controls::radio_group::~radio_group(){
	destroy_(true);
}

grafeex::window::object::rect_type grafeex::window::controls::radio_group::dimensions(bool inner) const{
	return (parent_ == nullptr) ? rect_type{} : parent_->dimensions(inner);
}

grafeex::window::object::point_type grafeex::window::controls::radio_group::convert_to_screen(const point_type &value) const{
	return (parent_ == nullptr) ? point_type{} : parent_->convert_to_screen(value);
}

grafeex::window::object::rect_type grafeex::window::controls::radio_group::convert_to_screen(const rect_type &value) const{
	return (parent_ == nullptr) ? rect_type{} : parent_->convert_to_screen(value);
}

grafeex::window::object::point_type grafeex::window::controls::radio_group::convert_from_screen(const point_type &value) const{
	return (parent_ == nullptr) ? point_type{} : parent_->convert_from_screen(value);
}

grafeex::window::object::rect_type grafeex::window::controls::radio_group::convert_from_screen(const rect_type &value) const{
	return (parent_ == nullptr) ? rect_type{} : parent_->convert_from_screen(value);
}

bool grafeex::window::controls::radio_group::create(gui_object_type &parent){
	if (!is_created()){
		insert_into_parent_(parent);
		return true;
	}

	return false;
}

bool grafeex::window::controls::radio_group::create(const sibling_type &sibling){
	if (!is_created()){
		insert_into_parent_(sibling);
		return true;
	}

	return false;
}

bool grafeex::window::controls::radio_group::destroy(){
	return destroy_(false);
}

bool grafeex::window::controls::radio_group::is_created() const{
	return (parent_ != nullptr);
}

void grafeex::window::controls::radio_group::remove_parent_(){
	guard_type guard(lock_);
	object::remove_parent_();
	empty_children_();
}

void grafeex::window::controls::radio_group::add_(child_type &child){
	object::add_(child);
	if (children_.size() == 1u){//First child
		auto radio_child = dynamic_cast<radio *>(&child);
		if (radio_child != nullptr)
			GRAFEEX_SET(radio_child->persistent_styles_.basic, WS_GROUP);
	}
}

void grafeex::window::controls::radio_group::insert_into_parent_(gui_object_type &parent){
	dynamic_cast<tree_type *>(parent_ = &parent)->add(*this);
}

void grafeex::window::controls::radio_group::insert_into_parent_(const sibling_type &sibling){
	dynamic_cast<tree_type *>(parent_ = sibling.parent())->add(*this, sibling);
}

bool grafeex::window::controls::radio_group::destroy_(bool force){
	if (!is_created())
		return true;

	object *control_child;
	while (!children_.empty()){
		control_child = dynamic_cast<object *>(*children_.begin());
		if (control_child != nullptr && !control_child->destroy() && !force)
			return false;
	}

	if (parent_ != nullptr){
		dynamic_cast<tree_type *>(parent_)->remove(*this);
		parent_ = nullptr;
	}

	return true;
}
