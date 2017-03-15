#include "system_color_structure.h"

grafeex::structures::color grafeex::structures::system_color::get(int index, color::field_type alpha){
	return color(::GetSysColor(index), alpha);
}

grafeex::structures::color grafeex::structures::system_color::get(index_type index, color::field_type alpha){
	return color(::GetSysColor(static_cast<int>(index)), alpha);
}
