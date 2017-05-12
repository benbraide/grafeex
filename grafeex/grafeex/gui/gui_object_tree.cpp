#include "gui_object_tree.h"

grafeex::gui::object_tree::~object_tree() = default;

grafeex::gui::object *grafeex::gui::object_tree::get_hit_target(const point_type &value) const{
	guard_type guard(lock_);
	for (auto child : children_){
		if (child->test(value) != hit_target_type::nil)
			return child;
	}

	return nullptr;
}

grafeex::gui::object *grafeex::gui::object_tree::get_deepest_hit_target(const point_type &value) const{
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

grafeex::gui::object_tree::attributes_type &grafeex::gui::object_tree::attributes(){
	return *get_attributes_();
}

void grafeex::gui::object_tree::attribute_set_(attributes_state_value_type state){
	if (state == attributes_state_type::fill_content){
		guard_type guard(lock_);
		object_tree *tree_child = nullptr;
		for (auto child : children_){
			if ((tree_child = dynamic_cast<object_tree *>(child)) != nullptr)//Add to child cache
				tree_child->set_attribute_cache_(state, *this);
		}
	}
	else if (state != attributes_state_type::nil){
		auto tree_parent = dynamic_cast<object_tree *>(parent_);
		if (tree_parent != nullptr)//Add to parent cache
			tree_parent->set_attribute_cache_(state, *this);
	}
}

void grafeex::gui::object_tree::attribute_removed_(attributes_state_value_type state){
	if (state == attributes_state_type::fill_content){
		guard_type guard(lock_);
		object_tree *tree_child = nullptr;
		for (auto child : children_){
			if ((tree_child = dynamic_cast<object_tree *>(child)) != nullptr)//Remove from child cache
				tree_child->remove_attribute_cache_(state, *this);
		}
	}
	else if (state != attributes_state_type::nil){
		auto tree_parent = dynamic_cast<object_tree *>(parent_);
		if (tree_parent != nullptr)//Remove from parent cache
			tree_parent->remove_attribute_cache_(state, *this);
	}
}

void grafeex::gui::object_tree::set_attribute_cache_(attributes_state_value_type state, object_tree &target){
	guard_type guard(lock_);
	attributes_cache_[state].push_back(&target);
}

void grafeex::gui::object_tree::remove_attribute_cache_(attributes_state_value_type state, object_tree &target){
	guard_type guard(lock_);
	
	auto entry = attributes_cache_.find(state);
	if (entry != attributes_cache_.end()){
		auto target_entry = std::find(entry->second.begin(), entry->second.end(), &target);
		if (target_entry != entry->second.end()){
			entry->second.erase(target_entry);
			if (entry->second.empty())
				attributes_cache_.erase(entry);
		}
	}
}

void grafeex::gui::object_tree::sized_(){
	guard_type guard(lock_);

	auto entry = attributes_cache_.find(attributes_state_type::fill_parent);
	if (entry != attributes_cache_.end()){//Trigger children watching for size change
		for (auto target : entry->second){
			if (target->attributes_ != nullptr)
				target->attributes_->trigger_(attributes_state_type::fill_parent);
		}
	}

	entry = attributes_cache_.find(attributes_state_type::align);
	if (entry != attributes_cache_.end()){//Trigger children watching for size change
		for (auto target : entry->second){
			if (target->attributes_ != nullptr)
				target->attributes_->trigger_(attributes_state_type::align);
		}
	}

	entry = attributes_cache_.find(attributes_state_type::fill_content);
	if (entry != attributes_cache_.end()){//Trigger parent watching for size change
		for (auto target : entry->second){
			if (target->attributes_ != nullptr)
				target->attributes_->trigger_(attributes_state_type::fill_content);
		}
	}
}

void grafeex::gui::object_tree::moved_(){
	guard_type guard(lock_);

	auto entry = attributes_cache_.find(attributes_state_type::fill_content);
	if (entry != attributes_cache_.end()){//Trigger parent watching for offset change
		for (auto target : entry->second){
			if (target->attributes_ != nullptr)
				target->attributes_->trigger_(attributes_state_type::fill_content);
		}
	}
}

grafeex::gui::object_tree::attributes_ptr_type grafeex::gui::object_tree::get_attributes_(){
	return create_attributes_<attributes_type>();
}
