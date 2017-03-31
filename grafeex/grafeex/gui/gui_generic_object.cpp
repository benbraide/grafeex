#include "gui_generic_object.h"

grafeex::gui::generic_object::~generic_object(){}

grafeex::gui::object *grafeex::gui::generic_object::non_sibling(){
	return this;
}

grafeex::gui::object *grafeex::gui::generic_object::parent() const{
	return parent_;
}

grafeex::gui::object &grafeex::gui::generic_object::traverse_siblings(sibling_traverser_type traverser){
	auto tree_parent = dynamic_cast<tree_type *>(parent_);
	if (tree_parent != nullptr){
		auto sibling_type = object_sibling::sibling_value_type::previous;
		tree_parent->traverse_children([this, traverser, &sibling_type](object &child){
			if (child.non_sibling() == this){
				sibling_type = object_sibling::sibling_value_type::next;
				return true;
			}

			return traverser(object_sibling(child, sibling_type));
		});
	}

	return *this;
}

const grafeex::gui::object &grafeex::gui::generic_object::traverse_siblings(const_sibling_traverser_type traverser) const{
	auto tree_parent = dynamic_cast<tree_type *>(parent_);
	if (tree_parent != nullptr){
		auto sibling_type = object_sibling::sibling_value_type::previous;
		tree_parent->traverse_children([this, traverser, &sibling_type](object &child){
			if (child.non_sibling() == this){
				sibling_type = object_sibling::sibling_value_type::next;
				return true;
			}

			return traverser(object_sibling(child, sibling_type));
		});
	}

	return *this;
}

grafeex::gui::object &grafeex::gui::generic_object::dimensions(const rect_type &value, bool inner){
	return *this;
}

grafeex::gui::object::rect_type grafeex::gui::generic_object::dimensions(bool inner) const{
	return rect_type{};
}

grafeex::gui::object &grafeex::gui::generic_object::size(const size_type &value, bool inner){
	return dimensions(rect_type{ offset(), value }, inner);
}

grafeex::gui::generic_object::size_type grafeex::gui::generic_object::size(bool inner) const{
	return dimensions(inner).size();
}

grafeex::gui::object &grafeex::gui::generic_object::offset(const size_type &value){
	return dimensions(rect_type{ offset() + value, size() }, false);
}

grafeex::gui::object::point_type grafeex::gui::generic_object::offset() const{
	return dimensions(false).top_left();
}

grafeex::gui::object &grafeex::gui::generic_object::move(const point_type &value){
	return dimensions(rect_type{ value, size() }, false);
}

grafeex::gui::object &grafeex::gui::generic_object::drag(const size_type &value){
	return *this;
}

grafeex::gui::object &grafeex::gui::generic_object::align(alignment_type value, const size_type &delta){
	return move(compute_alignment(value, delta));
}

grafeex::gui::object::point_type grafeex::gui::generic_object::compute_alignment(alignment_type value, const size_type &delta) const{
	if (parent_ == nullptr)
		return point_type{};

	return (offset() + (compute_alignment_delta(parent_->size(), size(), value) + delta));
}

grafeex::gui::object::hit_target_type grafeex::gui::generic_object::test(const point_type &value) const{
	if (dimensions(true).contains(value))
		return hit_target_type::client;

	return dimensions().contains(value) ? hit_target_type::border : hit_target_type::nil;
}

grafeex::gui::object::point_type grafeex::gui::generic_object::convert_to_screen(const point_type &value) const{
	return point_type{};
}

grafeex::gui::object::rect_type grafeex::gui::generic_object::convert_to_screen(const rect_type &value) const{
	return rect_type{};
}

grafeex::gui::object::point_type grafeex::gui::generic_object::convert_from_screen(const point_type &value) const{
	return point_type{};
}

grafeex::gui::object::rect_type grafeex::gui::generic_object::convert_from_screen(const rect_type &value) const{
	return rect_type{};
}

grafeex::gui::object::object_type grafeex::gui::generic_object::type() const{
	return object_type::unspecified;
}
