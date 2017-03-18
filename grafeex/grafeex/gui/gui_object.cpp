#include "gui_object.h"

grafeex::gui::object::size_type grafeex::gui::object::compute_alignment_delta(const size_type &parent_size,
	const size_type &target_size, alignment_type value){
	size_type delta;
	if (GRAFEEX_IS(value, alignment_type::right))
		delta.width(parent_size.width() - target_size.width());
	else if (GRAFEEX_IS(value, alignment_type::center))
		delta.width((parent_size.width() - target_size.width()) / 2);
	else//left
		delta.width(0);

	if (GRAFEEX_IS(value, alignment_type::bottom))
		delta.height(parent_size.height() - target_size.height());
	else if (GRAFEEX_IS(value, alignment_type::vertical_center))
		delta.height((parent_size.height() - target_size.height()) / 2);
	else//top
		delta.height(0);

	return delta;
}

grafeex::gui::object::point_type grafeex::gui::operator+(const object::point_type &point, const object::size_type &size){
	return object::point_type{ point.x() + size.width(), point.y() + size.height() };
}
