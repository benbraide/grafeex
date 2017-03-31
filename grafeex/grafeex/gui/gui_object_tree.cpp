#include "gui_object_tree.h"

grafeex::gui::object_tree::~object_tree(){}

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
