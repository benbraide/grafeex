#include "gui_object_sibling.h"

grafeex::gui::object_sibling::object_sibling()
	: value_(nullptr), type_(sibling_type::previous){}

grafeex::gui::object_sibling::object_sibling(const object &value, sibling_type type)
	: object_sibling(const_cast<object &>(value), type){}

grafeex::gui::object_sibling::object_sibling(object &value, sibling_type type)
	: value_(&value), type_(type){}

grafeex::gui::object_sibling::~object_sibling(){}

grafeex::gui::object *grafeex::gui::object_sibling::non_sibling(){
	return value_->non_sibling();
}

const grafeex::gui::object *grafeex::gui::object_sibling::parent() const{
	return value_->parent();
}

grafeex::gui::object *grafeex::gui::object_sibling::parent(){
	return value_->parent();
}

grafeex::gui::object &grafeex::gui::object_sibling::traverse_siblings(sibling_traverser_type traverser){
	return value_->traverse_siblings(traverser);
}

const grafeex::gui::object &grafeex::gui::object_sibling::traverse_siblings(const_sibling_traverser_type traverser) const{
	return const_cast<const object *>(value_)->traverse_siblings(traverser);
}

grafeex::gui::object &grafeex::gui::object_sibling::dimensions(const rect_type &value, bool inner){
	return value_->dimensions(value, inner);
}

grafeex::gui::object::rect_type grafeex::gui::object_sibling::dimensions(bool inner) const{
	return value_->dimensions(inner);
}

grafeex::gui::object &grafeex::gui::object_sibling::size(const size_type &value, bool inner){
	return value_->size(value, inner);
}

grafeex::gui::object::size_type grafeex::gui::object_sibling::size(bool inner) const{
	return value_->size(inner);
}

grafeex::gui::object &grafeex::gui::object_sibling::offset(const size_type &value){
	return value_->offset(value);
}

grafeex::gui::object::point_type grafeex::gui::object_sibling::offset() const{
	return value_->offset();
}

grafeex::gui::object &grafeex::gui::object_sibling::drag(const size_type &value){
	return value_->drag(value);
}

grafeex::gui::object &grafeex::gui::object_sibling::move(const point_type &value){
	return value_->move(value);
}

grafeex::gui::object &grafeex::gui::object_sibling::align(alignment_type value, const size_type &delta){
	return value_->align(value, delta);
}

grafeex::gui::object::point_type grafeex::gui::object_sibling::compute_alignment(alignment_type value, const size_type &delta) const{
	return value_->compute_alignment(value, delta);
}

grafeex::gui::object::hit_target_type grafeex::gui::object_sibling::test(const point_type &value) const{
	return value_->test(value);
}

grafeex::gui::object::point_type grafeex::gui::object_sibling::convert_to_screen(const point_type &value) const{
	return value_->convert_to_screen(value);
}

grafeex::gui::object::rect_type grafeex::gui::object_sibling::convert_to_screen(const rect_type &value) const{
	return value_->convert_to_screen(value);
}

grafeex::gui::object::point_type grafeex::gui::object_sibling::convert_from_screen(const point_type &value) const{
	return value_->convert_from_screen(value);
}

grafeex::gui::object::rect_type grafeex::gui::object_sibling::convert_from_screen(const rect_type &value) const{
	return value_->convert_from_screen(value);
}

grafeex::gui::object::object_type grafeex::gui::object_sibling::type() const{
	return value_->type();
}

bool grafeex::gui::object_sibling::is_previous() const{
	return (type_ == sibling_type::previous);
}

grafeex::gui::object_sibling::index_type grafeex::gui::object_sibling::get_insert_index() const{
	auto tree_parent = dynamic_cast<const tree_type *>(parent());
	if (tree_parent == nullptr)
		return static_cast<index_type>(-1);

	auto index = tree_parent->get_child_index(*this);
	if (index == static_cast<index_type>(-1))
		return index;

	return (type_ == sibling_type::previous) ? (index + 1) : index;
}
