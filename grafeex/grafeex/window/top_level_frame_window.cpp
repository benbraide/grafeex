#include "top_level_frame_window.h"

grafeex::window::top_level_frame::top_level_frame(){}

grafeex::window::top_level_frame::top_level_frame(const std::wstring &caption, const point_type &offset, const size_type &size){
	create(caption, offset, size);
}

grafeex::window::top_level_frame::~top_level_frame(){}

grafeex::window::object::dword_type grafeex::window::top_level_frame::black_listed_styles(bool is_extended) const{
	return (object::black_listed_styles(is_extended) | (is_extended ? 0L : (WS_CAPTION | WS_BORDER | WS_SYSMENU)));
}

bool grafeex::window::top_level_frame::create(const std::wstring &caption, const point_type &offset, const size_type &size){
	return create_(caption, offset, size, WS_OVERLAPPEDWINDOW);
}
