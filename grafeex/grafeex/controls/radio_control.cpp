#include "radio_control.h"
#include "radio_control_group.h"

grafeex::window::controls::radio::radio(){
	reset_persistent_styles_();
}

grafeex::window::controls::radio::radio(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(parent, label, offset, padding);
}

grafeex::window::controls::radio::radio(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding){
	reset_persistent_styles_();
	create(sibling, label, offset, padding);
}

grafeex::window::controls::radio::~radio(){
	destroy();
}

bool grafeex::window::controls::radio::create(object_type &parent, const std::wstring &label,
	const point_type &offset, const size_type &padding){
	return button::create(parent, label, offset, padding);
}

bool grafeex::window::controls::radio::create(const sibling_type &sibling,
	const std::wstring &label, const point_type &offset, const size_type &padding){
	return button::create(sibling, label, offset, padding);
}

grafeex::window::object::hwnd_type grafeex::window::controls::radio::get_parent_handle_(){
	auto parent = parent_;
	if (parent == nullptr)
		return nullptr;

	if (dynamic_cast<radio_group *>(parent) != nullptr)
		parent = parent->parent();

	return (parent == nullptr) ? nullptr : dynamic_cast<window::object *>(parent)->operator HWND();
}

void grafeex::window::controls::radio::reset_persistent_styles_(){
	button::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, BS_AUTORADIOBUTTON);
}

grafeex::window::object::size_type grafeex::window::controls::radio::compute_size_(const std::wstring &label){
	return object::compute_size_(label);
}

grafeex::window::object::size_type grafeex::window::controls::radio::compute_additional_size_(const std::wstring &label){
	auto theme = ::GetWindowTheme(value_);
	if (theme == nullptr)
		return size_type{ ::GetSystemMetrics(SM_CXMENUCHECK), ::GetSystemMetrics(SM_CYMENUCHECK) };

	::RADIOBUTTONSTATES states;
	auto wdc = ::GetDC(value_);

	if (Button_GetCheck(value_) == BST_UNCHECKED)
		states = ::RADIOBUTTONSTATES::RBS_UNCHECKEDNORMAL;
	else//Checked
		states = ::RADIOBUTTONSTATES::RBS_CHECKEDNORMAL;

	size_type size;
	auto h = ::GetThemePartSize(theme, wdc, ::BUTTONPARTS::BP_RADIOBUTTON, states, nullptr, ::THEMESIZE::TS_TRUE, size);
	::ReleaseDC(value_, wdc);

	return (size + (padding_ * 2));
}
