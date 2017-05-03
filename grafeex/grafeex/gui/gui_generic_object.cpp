#include "gui_generic_object.h"

grafeex::gui::generic_object::event_tunnel::~event_tunnel() = default;

void grafeex::gui::generic_object::event_tunnel::unbind(const entry_type &entry){
	auto item = event_list_.find(entry.group());
	if (item != event_list_.end())
		item->second->remove(entry);
}

grafeex::gui::generic_object::~generic_object() = default;

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

grafeex::gui::object::rect_type grafeex::gui::generic_object::relative_dimensions() const{
	auto value = dimensions(false);
	return (parent_ == nullptr) ? value : parent_->convert_from_screen(value);
}

grafeex::gui::object &grafeex::gui::generic_object::size(const size_type &value, bool inner){
	return dimensions(rect_type{ relative_dimensions().top_left(), value }, inner);
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
	return (parent_->dimensions(true).top_left() + (compute_alignment_delta(parent_->size(true), size(), value) + delta));
}

grafeex::gui::object::hit_target_type grafeex::gui::generic_object::test(const point_type &value) const{
	if (convert_to_screen(dimensions(true)).contains(value))
		return hit_target_type::client;

	return dimensions(false).contains(value) ? hit_target_type::border : hit_target_type::nil;
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

grafeex::gui::generic_object::event_tunnel &grafeex::gui::generic_object::events(){
	return *get_events_();
}

void grafeex::gui::generic_object::remove_parent_(){
	parent_ = nullptr;
}

grafeex::gui::generic_object::events_type grafeex::gui::generic_object::get_events_(){
	return create_events_<event_tunnel>();
}

void grafeex::gui::generic_object::init_events_(){
	events_->owner_ = this;
}
