#include "check_control.h"

grafeex::window::controls::check::check(){
	reset_persistent_styles_();
}

grafeex::window::controls::check::check(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(parent, label, offset, padding);
}

grafeex::window::controls::check::check(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(sibling, label, offset, padding);
}

grafeex::window::controls::check::~check(){
	destroy();
}

void grafeex::window::controls::check::reset_persistent_styles_(){
	button::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, BS_AUTOCHECKBOX);
}

grafeex::window::object::size_type grafeex::window::controls::check::compute_size_(const std::wstring &label){
	return object::compute_size_(label);
}

grafeex::window::object::size_type grafeex::window::controls::check::compute_additional_size_(const std::wstring &label){
	auto theme = ::GetWindowTheme(value_);
	if (theme == nullptr)
		return size_type{ ::GetSystemMetrics(SM_CXMENUCHECK), ::GetSystemMetrics(SM_CYMENUCHECK) };

	::CHECKBOXSTATES states;
	auto wdc = ::GetDC(value_);

	if (Button_GetCheck(value_) == BST_UNCHECKED)
		states = ::CHECKBOXSTATES::CBS_UNCHECKEDNORMAL;
	else//Checked
		states = ::CHECKBOXSTATES::CBS_CHECKEDNORMAL;

	size_type size;
	auto h = ::GetThemePartSize(theme, wdc, ::BUTTONPARTS::BP_CHECKBOX, states, nullptr, ::THEMESIZE::TS_TRUE, size);
	::ReleaseDC(value_, wdc);

	return (size + (padding_ * 2));
}
