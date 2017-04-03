#include "basic_menu_tree.h"
#include "menu_item.h"

grafeex::menu::basic_tree::~basic_tree(){}

grafeex::menu::tree &grafeex::menu::basic_tree::traverse_children_absolute(traverser_type traverser){
	guard_type guard(lock_);

	tree_type *tree_child;
	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree_type *>(child)) == nullptr)
			traverser(*child);//Pass to traverser
		else//Traverse tree
			tree_child->traverse_children(traverser);
	}

	return *this;
}

const grafeex::menu::tree &grafeex::menu::basic_tree::traverse_children_absolute(const_traverser_type traverser) const{
	guard_type guard(lock_);

	const tree_type *tree_child;
	for (auto child : children_){
		if ((tree_child = dynamic_cast<const tree_type *>(child)) == nullptr)
			traverser(*child);//Pass to traverser
		else//Traverse tree
			tree_child->traverse_children(traverser);
	}

	return *this;
}

grafeex::menu::basic_tree::child_type *grafeex::menu::basic_tree::get_child_absolute(index_type index) const{
	guard_type guard(lock_);

	tree_type *tree_child;
	child_type *child;

	index_type child_index = 0;
	for (auto item : children_){
		if ((tree_child = dynamic_cast<tree_type *>(item)) != nullptr){
			if ((child = get_child_absolute_(*tree_child, child_index, index)) != nullptr)
				return child;//Found
		}
		else if (child_index != index)//Increment index
			++child_index;
		else//Match found
			return item;
	}

	return nullptr;
}

grafeex::menu::basic_tree::index_type grafeex::menu::basic_tree::get_child_index_absolute(const child_type &child) const{
	guard_type guard(lock_);

	tree *tree_child;
	index_type index = 0;

	for (auto item : children_){
		if (item == &child)
			return index;

		if ((tree_child = dynamic_cast<tree *>(item)) == nullptr)
			++index;
		else
			index += tree_child->get_children_count_absolute();
	}

	return static_cast<index_type>(-1);
}

grafeex::menu::basic_tree::index_type grafeex::menu::basic_tree::get_child_menu_index(const child_type &child) const{
	return get_child_index_absolute(child);
}

grafeex::menu::basic_tree::index_type grafeex::menu::basic_tree::get_children_count_absolute() const{
	guard_type guard(lock_);

	tree *tree_child;
	index_type count = 0;

	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree *>(child)) == nullptr)
			++count;
		else
			count += tree_child->get_children_count_absolute();
	}

	return count;
}

grafeex::menu::basic_tree::child_type *grafeex::menu::basic_tree::find_child(id_type id) const{
	guard_type guard(lock_);

	tree *tree_child;
	child_type *found;

	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree *>(child)) == nullptr){
			if (dynamic_cast<item *>(child)->id() == id)//Matching ids
				return child;
		}
		else if ((found = tree_child->find_child(id)) != nullptr)//Search tree
			return found;
	}

	return nullptr;
}

grafeex::menu::basic_tree::child_type *grafeex::menu::basic_tree::get_child_absolute_(tree_type &tree_child, index_type &child_index, index_type index) const{
	child_type *found_child = nullptr;
	tree_child.traverse_children([&](child_type &child) -> bool{
		auto tree_child = dynamic_cast<tree_type *>(&child);
		if (tree_child != nullptr){
			if ((found_child = get_child_absolute_(*tree_child, child_index, index)) != nullptr)
				return false;//Found
		}
		else if (child_index == index){//Match found
			found_child = &child;
			return false;
		}
		else//Increment index
			++child_index;

		return true;
	});

	return found_child;
}
