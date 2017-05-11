#include "gui_row.h"

grafeex::gui::row::row(){}

grafeex::gui::row::row(gui_object_type &parent){
	create(parent);
}

grafeex::gui::row::row(const sibling_type &sibling){
	create(sibling);
}

grafeex::gui::row::~row(){
	destroy();
}

grafeex::gui::row &grafeex::gui::row::dimensions(const rect_type &value, bool inner){
	base_type::dimensions(value, inner);
	sized_();
	return *this;
}

grafeex::gui::row &grafeex::gui::row::padding(const rect_type &value){
	base_type::padding(value);
	sized_();
	return *this;
}

void grafeex::gui::row::refresh(){
	if (parent_ != nullptr)
		dynamic_cast<grid_member *>(parent_)->refresh();
}

bool grafeex::gui::row::create(gui_object_type &parent){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	refresh();

	return true;
}

bool grafeex::gui::row::create(const sibling_type &sibling){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	refresh();

	return true;
}

bool grafeex::gui::row::destroy(){
	if (!is_created())
		return true;

	auto parent = parent_;
	parent_ = nullptr;

	dynamic_cast<tree_type *>(parent)->remove(*this);
	return true;
}

bool grafeex::gui::row::is_created() const{
	return (parent_ != nullptr);
}

int grafeex::gui::row::compute_fixed_width(int width) const{
	return 0;
}

int grafeex::gui::row::compute_fixed_height(int height) const{
	return 0;
}

bool grafeex::gui::row::is_fixed() const{
	return false;
}

void grafeex::gui::row::sized_(){
	refresh();
	base_type::sized_();
}

void grafeex::gui::row::dimensions_(const rect_type &value){
	base_type::dimensions_ = value;
}

void grafeex::gui::row::refresh_(){
	guard_type guard(lock_);

	auto dimensions = this->dimensions(true);
	auto offset = dimensions.top_left();

	auto size = dimensions.size();
	auto width = size.width(), height = size.height(), fixed_width = 0l, shared_count = 0l, index = 0l, child_height = 0l;

	cache_type cache(children_.size());
	for (auto child : children_){//Compute fixed width and shared count
		cache[index].object = dynamic_cast<column_interface *>(child);
		if (!(cache[index].is_fixed = cache[index].object->is_fixed()))
			++shared_count;//Non-fixed column

		fixed_width += (cache[index].width = cache[index].object->compute_fixed_width(width));
		if (height < (child_height = cache[index].object->compute_fixed_height(height)))
			height = child_height;//Use max height

		++index;
	}

	index = 0l;
	auto shared_width = (fixed_width < width) ? (width - fixed_width) : 0;

	for (auto child : children_){
		if (cache[index].object->is_fixed())
			cache[index].object->dimensions_(rect_type(offset, size_type(cache[index].width, height)));
		else//Use shared width
			cache[index].object->dimensions_(rect_type(offset, size_type(cache[index].width = (shared_width / shared_count), height)));

		offset.x(offset.x() + cache[index].width);//Advance offset
		++index;
	}
}
