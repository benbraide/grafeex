#include "frame_window.h"

grafeex::window::frame::frame(){}

grafeex::window::frame::frame(const std::wstring &caption, const point_type &offset, const size_type &size){
	create(caption, offset, size);
}

grafeex::window::frame::frame(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size){
	create(parent, caption, offset, size);
}

grafeex::window::frame::frame(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size){
	create(sibling, caption, offset, size);
}

grafeex::window::frame::~frame(){}

grafeex::window::object::dword_type grafeex::window::frame::black_listed_styles(bool is_extended) const{
	return (object::black_listed_styles(is_extended) | (is_extended ? 0L : (WS_CAPTION | WS_BORDER | WS_SYSMENU)));
}

bool grafeex::window::frame::create(const std::wstring &caption, const point_type &offset, const size_type &size){
	return create_(caption, offset, size, WS_OVERLAPPEDWINDOW);
}

bool grafeex::window::frame::create(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size){
	insert_into_parent_(parent);
	return create_(caption, offset, size, WS_OVERLAPPEDWINDOW);
}

bool grafeex::window::frame::create(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size){
	insert_into_parent_(sibling);
	return create_(caption, offset, size, WS_OVERLAPPEDWINDOW);
}
