#include "top_level_window.h"

grafeex::window::top_level::top_level(){
	persistent_styles_.basic = WS_OVERLAPPEDWINDOW;
}

grafeex::window::top_level::top_level(const std::wstring &caption, const point_type &offset, const size_type &size){
	persistent_styles_.basic = WS_OVERLAPPEDWINDOW;
	create(caption, offset, size);
}

grafeex::window::top_level::~top_level(){}

bool grafeex::window::top_level::is_top_level() const{
	return true;
}

bool grafeex::window::top_level::create(const std::wstring &caption, const point_type &offset, const size_type &size){
	return create_(caption, offset, size);
}
