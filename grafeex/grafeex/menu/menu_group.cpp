#include "menu_group.h"

grafeex::menu::group::group(){}

grafeex::menu::group::group(gui_object_type &parent){
	create(parent);
}

grafeex::menu::group::group(const sibling_type &sibling){
	create(sibling);
}

grafeex::menu::group::~group(){
	destroy_(true);
}

grafeex::menu::group &grafeex::menu::group::dimensions(const rect_type &value, bool inner){
	return *this;
}

grafeex::gui::object::rect_type grafeex::menu::group::dimensions(bool inner) const{
	return rect_type{};
}

grafeex::menu::group &grafeex::menu::group::drag(const size_type &value){
	return *this;
}

grafeex::gui::object::point_type grafeex::menu::group::compute_alignment(alignment_type value, const size_type &delta) const{
	return point_type{};
}

grafeex::gui::object::point_type grafeex::menu::group::convert_to_screen(const point_type &value) const{
	return point_type{};
}

grafeex::gui::object::rect_type grafeex::menu::group::convert_to_screen(const rect_type &value) const{
	return rect_type{};
}

grafeex::gui::object::point_type grafeex::menu::group::convert_from_screen(const point_type &value) const{
	return point_type{};
}

grafeex::gui::object::rect_type grafeex::menu::group::convert_from_screen(const rect_type &value) const{
	return rect_type{};
}

grafeex::gui::object::object_type grafeex::menu::group::type() const{
	return object_type::menu;
}

grafeex::menu::tree::native_type grafeex::menu::group::native_value() const{
	return dynamic_cast<tree *>(parent_)->native_value();
}

grafeex::menu::group::index_type grafeex::menu::group::get_child_menu_index(const child_type &child) const{
	return (get_item_index_in_parent() + get_child_index_absolute(child));
}

grafeex::menu::tree::id_type grafeex::menu::group::generate_id(){
	return dynamic_cast<tree *>(parent_)->generate_id();
}

bool grafeex::menu::group::create(gui_object_type &parent){
	if (!is_created()){
		insert_into_parent_(parent);
		return true;
	}

	return false;
}

bool grafeex::menu::group::create(const sibling_type &sibling){
	if (!is_created()){
		insert_into_parent_(sibling);
		return true;
	}

	return false;
}

bool grafeex::menu::group::destroy(){
	return destroy_(false);
}

bool grafeex::menu::group::is_created() const{
	return (parent_ != nullptr);
}

grafeex::menu::group::index_type grafeex::menu::group::get_item_index_in_parent() const{
	return dynamic_cast<tree *>(parent_)->get_child_menu_index(*this);
}

void grafeex::menu::group::remove_parent_(){
	guard_type guard(lock_);
	base_type::remove_parent_();
	empty_children_();
}

void grafeex::menu::group::insert_into_parent_(gui_object_type &parent){
	dynamic_cast<tree_type *>(parent_ = &parent)->add(*this);
}

bool grafeex::menu::group::destroy_(bool force){
	if (!is_created())
		return true;

	group *group_child;
	while (!children_.empty()){
		if ((group_child = dynamic_cast<group *>(*children_.begin())) == nullptr){
			if (!dynamic_cast<item *>(*children_.begin())->destroy() && !force)
				return false;
		}
		else if (!group_child->destroy() && !force)//Destroy group
			return false;
	}

	dynamic_cast<tree_type *>(parent_)->remove(*this);
	parent_ = nullptr;

	return true;
}

void grafeex::menu::group::insert_into_parent_(const sibling_type &sibling){
	dynamic_cast<tree_type *>(parent_ = sibling.parent())->add(*this, sibling);
}
