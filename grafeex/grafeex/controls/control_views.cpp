#include "control_views.h"
#include "../controls/control_object.h"

grafeex::window::controls::view::view(object_type &object)
	: base_type(object){}

grafeex::window::controls::view::~view() = default;

grafeex::window::controls::view &grafeex::window::controls::view::font(const wchar_t *family, font_weigth_type weight, long size){
	auto control_object = dynamic_cast<window::controls::object *>(object_);
	font_info_type info{ sizeof(font_info_type) };

	info.lfHeight = size;
	info.lfWeight = static_cast<long>(weight);
	info.lfCharSet = DEFAULT_CHARSET;

	auto max_index = (LF_FACESIZE - 1), i = 0;
	for (; i < max_index && family[i] != L'\0'; ++i)
		info.lfFaceName[i] = family[i];

	info.lfFaceName[i] = L'\0';
	control_object->font_ = ::CreateFontIndirectW(&info);

	return this->font(control_object->font_);
}

grafeex::window::controls::view &grafeex::window::controls::view::font(font_type value){
	dynamic_cast<window::controls::object *>(object_)->value_.send_message(WM_SETFONT, value, MAKEWORD(TRUE, 0));
	return *this;
}

grafeex::window::controls::view::font_type grafeex::window::controls::view::font() const{
	auto value = dynamic_cast<window::controls::object *>(object_)->value_.send_message<font_type>(WM_GETFONT);
	if (value != nullptr)
		return value;

	auto system = gdi::stock_object::get(gdi::stock_object::index::system_font);
	return static_cast<font_type>(system.operator void *());
}
