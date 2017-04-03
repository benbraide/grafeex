#include "menu_wrapper.h"

grafeex::wrappers::menu::menu(value_type value)
	: base_type(value){}

bool grafeex::wrappers::menu::destroy(){
	if (::DestroyMenu(value_) != FALSE){
		value_ = nullptr;
		return true;
	}

	return false;
}

bool grafeex::wrappers::menu::set(const info_type &info){
	return (::SetMenuInfo(value_, &info) != FALSE);
}

bool grafeex::wrappers::menu::styles(dword_type value, bool apply_to_submenus){
	return set(info_type{
		sizeof(info_type),
		MIM_STYLE | (apply_to_submenus ? MIM_APPLYTOSUBMENUS : 0),
		value
	});
}

grafeex::wrappers::menu::dword_type grafeex::wrappers::menu::styles() const{
	info_type info;
	get_(info, MIM_STYLE);
	return info.dwStyle;
}

bool grafeex::wrappers::menu::max_height(uint_type value, bool apply_to_submenus){
	return set(info_type{
		sizeof(info_type),
		MIM_MAXHEIGHT | (apply_to_submenus ? MIM_APPLYTOSUBMENUS : 0),
		0,
		value
	});
}

grafeex::wrappers::menu::uint_type grafeex::wrappers::menu::max_height() const{
	info_type info;
	get_(info, MIM_MAXHEIGHT);
	return info.cyMax;
}

bool grafeex::wrappers::menu::background_brush(brush_type value, bool apply_to_submenus){
	return set(info_type{
		sizeof(info_type),
		MIM_BACKGROUND | (apply_to_submenus ? MIM_APPLYTOSUBMENUS : 0),
		0,
		0,
		value
	});
}

grafeex::wrappers::menu::brush_type grafeex::wrappers::menu::background_brush() const{
	info_type info;
	get_(info, MIM_BACKGROUND);
	return info.hbrBack;
}

bool grafeex::wrappers::menu::context_help_id(dword_type value){
	return set(info_type{
		sizeof(info_type),
		MIM_HELPID,
		0,
		0,
		nullptr,
		value
	});
}

grafeex::wrappers::menu::dword_type grafeex::wrappers::menu::context_help_id() const{
	info_type info;
	get_(info, MIM_HELPID);
	return info.dwContextHelpID;
}

bool grafeex::wrappers::menu::data(ulong_ptr_type value){
	return set(info_type{
		sizeof(info_type),
		MIM_MENUDATA,
		0,
		0,
		nullptr,
		0,
		value
	});
}

int grafeex::wrappers::menu::count() const{
	return ::GetMenuItemCount(value_);
}

void grafeex::wrappers::menu::get_(info_type &info, dword_type masks) const{
	info = info_type{ sizeof(info_type), masks };
	::GetMenuInfo(value_, &info);
}
