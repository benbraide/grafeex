#include "non_window_object.h"

grafeex::non_window::object::object()
	: states_(state::nil){}

grafeex::non_window::object::object(gui_object_type &parent, const rect_type &dimensions, const rect_type &padding)
	: states_(state::nil){
	create(parent, dimensions, padding);
}

grafeex::non_window::object::object(const sibling_type &sibling, const rect_type &dimensions, const rect_type &padding)
	: states_(state::nil){
	create(sibling, dimensions, padding);
}

grafeex::non_window::object::~object(){
	destroy();
}

grafeex::non_window::object &grafeex::non_window::object::dimensions(const rect_type &value, bool inner){
	base_type::dimensions(value, inner);
	sized_();
	return *this;
}

grafeex::non_window::object &grafeex::non_window::object::padding(const rect_type &value){
	base_type::padding(value);
	sized_();
	return *this;
}

grafeex::non_window::object &grafeex::non_window::object::paint(){
	return paint(dimensions_);
}

grafeex::non_window::object &grafeex::non_window::object::paint(const rect_type &bounding_rect){
	GRAFEEX_SET(states_, state::dirty);
	paint_(bounding_rect);
	return *this;
}

bool grafeex::non_window::object::create(gui_object_type &parent, const rect_type &dimensions, const rect_type &padding){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(dimensions, padding);
}

bool grafeex::non_window::object::create(const sibling_type &sibling, const rect_type &dimensions, const rect_type &padding){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(dimensions, padding);
}

bool grafeex::non_window::object::destroy(){
	if (!is_created())
		return true;

	auto parent = parent_;
	parent_ = nullptr;

	dynamic_cast<tree_type *>(parent)->remove(*this);
	return true;
}

bool grafeex::non_window::object::is_created() const{
	return (parent_ != nullptr);
}

void grafeex::non_window::object::sized_(){
	base_type::sized_();
	paint();
}

bool grafeex::non_window::object::create_(const rect_type &dimensions, const rect_type &padding){
	dimensions_ = dimensions;
	padding_ = padding;
	return true;
}

void grafeex::non_window::object::paint_(const rect_type &bounding_rect){
	guard_type guard(lock_);
	if (!GRAFEEX_IS(states_, state::dirty | state::visible))
		return;//Nothing to paint

	auto intersection = dimensions_.get_intersection(bounding_rect);
	if (intersection.is_empty()){
		GRAFEEX_REMOVE(states_, state::dirty);
		return;//Nothing to paint
	}

	//TODO: Implement non-client paint

	intersection = intersection.get_intersection(dimensions_.get_deflated(padding_));//Confine to inner bounds
	if (intersection.is_empty()){//No client paint
		GRAFEEX_REMOVE(states_, state::dirty);
		return;
	}

	//TODO: Implement client paint
	intersection.move_to(point_type{});//Move to [0, 0]

	object *non_window_object;
	for (auto child : children_){
		if ((non_window_object = dynamic_cast<object *>(child)) != nullptr)
			non_window_object->paint(intersection);
	}

	GRAFEEX_REMOVE(states_, state::dirty);
}

void grafeex::non_window::object::clear_(){
	if (GRAFEEX_IS(states_, state::visible))
		return;//Nothing to clear
}
