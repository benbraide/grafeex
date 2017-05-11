#include "gui_grid.h"

grafeex::gui::grid::grid(){}

grafeex::gui::grid::grid(gui_object_type &parent){
	create(parent);
}

grafeex::gui::grid::grid(const sibling_type &sibling){
	create(sibling);
}

grafeex::gui::grid::~grid(){
	destroy();
}

grafeex::gui::grid &grafeex::gui::grid::dimensions(const rect_type &value, bool inner){
	base_type::dimensions(value, inner);
	sized_();
	return *this;
}

grafeex::gui::grid &grafeex::gui::grid::padding(const rect_type &value){
	base_type::padding(value);
	sized_();
	return *this;
}

void grafeex::gui::grid::refresh(){
	refresh_();
}

bool grafeex::gui::grid::create(gui_object_type &parent){
	return create_<gui_object_type &>(parent);
}

bool grafeex::gui::grid::create(const sibling_type &sibling){
	return create_<const sibling_type &>(sibling);
}

bool grafeex::gui::grid::destroy(){
	if (!is_created())
		return true;

	auto parent = parent_;
	parent_ = nullptr;

	dynamic_cast<tree_type *>(parent)->remove(*this);
	return true;
}

bool grafeex::gui::grid::is_created() const{
	return (parent_ != nullptr);
}

bool grafeex::gui::grid::is_fixed() const{
	return false;
}

void grafeex::gui::grid::sized_(){
	refresh();
	base_type::sized_();
}

void grafeex::gui::grid::refresh_(){
	guard_type guard(lock_);

	auto dimensions = this->dimensions(true);
	auto offset = dimensions.top_left();

	auto size = dimensions.size();
	auto width = size.width(), height = size.height(), fixed_height = 0l, shared_count = 0l, index = 0l, child_width = 0l;

	cache_type cache(children_.size());
	for (auto child : children_){//Compute fixed height and shared count
		cache[index].object = dynamic_cast<row *>(child);
		if (!(cache[index].is_fixed = cache[index].object->is_fixed()))
			++shared_count;//Non-fixed row

		fixed_height += (cache[index].height = cache[index].object->compute_fixed_height(height));
		if (width < (child_width = cache[index].object->compute_fixed_width(width)))
			width = child_width;//Use max width

		++index;
	}

	index = 0l;
	auto shared_height = (fixed_height < height) ? (height - fixed_height) : 0;

	for (auto child : children_){
		if (cache[index].object->is_fixed())
			cache[index].object->dimensions_(rect_type(offset, size_type(width, cache[index].height)));
		else//Use shared height
			cache[index].object->dimensions_(rect_type(offset, size_type(width, cache[index].height = (shared_height / shared_count))));

		offset.y(offset.y() + cache[index].height);//Advance offset
		++index;
	}
}
