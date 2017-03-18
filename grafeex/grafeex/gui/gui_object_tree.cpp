#include "gui_object_tree.h"

grafeex::gui::object_tree::~object_tree(){}

grafeex::gui::object *grafeex::gui::object_tree::non_sibling(){
	return this;
}

const grafeex::gui::object *grafeex::gui::object_tree::parent() const{
	return parent_;
}

grafeex::gui::object *grafeex::gui::object_tree::parent(){
	return parent_;
}

grafeex::gui::object &grafeex::gui::object_tree::traverse_siblings(sibling_traverser_type traverser){
	auto tree_parent = dynamic_cast<tree_type *>(parent_);
	if (tree_parent != nullptr){
		auto sibling_type = object_sibling::sibling_type::previous;
		tree_parent->traverse_children([this, traverser, &sibling_type](object &child){
			if (child.non_sibling() == this){
				sibling_type = object_sibling::sibling_type::next;
				return true;
			}

			return traverser(object_sibling(child, sibling_type));
		});
	}

	return *this;
}

const grafeex::gui::object &grafeex::gui::object_tree::traverse_siblings(const_sibling_traverser_type traverser) const{
	auto tree_parent = dynamic_cast<tree_type *>(parent_);
	if (tree_parent != nullptr){
		auto sibling_type = object_sibling::sibling_type::previous;
		tree_parent->traverse_children([this, traverser, &sibling_type](object &child){
			if (child.non_sibling() == this){
				sibling_type = object_sibling::sibling_type::next;
				return true;
			}

			return traverser(object_sibling(child, sibling_type));
		});
	}

	return *this;
}

grafeex::gui::object &grafeex::gui::object_tree::size(const size_type &value, bool inner){
	return dimensions(rect_type{ offset(), value }, inner);
}

grafeex::gui::object::size_type grafeex::gui::object_tree::size(bool inner) const{
	return dimensions(inner).size();
}

grafeex::gui::object &grafeex::gui::object_tree::offset(const size_type &value){
	return dimensions(rect_type{ offset() + value, size() }, false);
}

grafeex::gui::object &grafeex::gui::object_tree::move(const point_type &value){
	return dimensions(rect_type{ value, size() }, false);
}

grafeex::gui::object::point_type grafeex::gui::object_tree::offset() const{
	return dimensions(false).top_left();
}

grafeex::gui::object &grafeex::gui::object_tree::align(alignment_type value, const size_type &delta){
	return move(compute_alignment(value, delta));
}

grafeex::gui::object::hit_target_type grafeex::gui::object_tree::test(const point_type &value) const{
	if (dimensions(true).contains(value))
		return hit_target_type::client;

	return dimensions().contains(value) ? hit_target_type::border : hit_target_type::nil;
}

const grafeex::gui::object *grafeex::gui::object_tree::get_hit_target(const point_type &value) const{
	return const_cast<object_tree *>(this)->get_hit_target(value);
}

grafeex::gui::object *grafeex::gui::object_tree::get_hit_target(const point_type &value){
	guard_type guard(lock_);
	for (auto child : children_){
		if (child->test(value) != hit_target_type::nil)
			return child;
	}

	return nullptr;
}

const grafeex::gui::object *grafeex::gui::object_tree::get_deepest_hit_target(const point_type &value) const{
	return const_cast<object_tree *>(this)->get_deepest_hit_target(value);
}

grafeex::gui::object *grafeex::gui::object_tree::get_deepest_hit_target(const point_type &value){
	guard_type guard(lock_);

	object *target;
	object_tree *tree_child;

	for (auto child : children_){
		if (child->test(value) != hit_target_type::nil)
			return child;

		if ((tree_child = dynamic_cast<object_tree *>(child)) != nullptr && (target = tree_child->get_deepest_hit_target(value)) != nullptr)
			return target;//Offspring matched
	}

	return nullptr;
}
