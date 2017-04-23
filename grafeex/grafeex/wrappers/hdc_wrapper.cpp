#include "hdc_wrapper.h"

grafeex::wrappers::hdc::hdc(value_type value)
	: base_type(value){}

std::wstring grafeex::wrappers::hdc::font_face() const{
	auto face_size = ::GetTextFaceW(value_, 0, nullptr);
	if (face_size <= 0)
		return L"";

	auto face = std::make_unique<wchar_t[]>(face_size);
	::GetTextFaceW(value_, face_size, face.get());

	return std::wstring(face.get());
}

bool grafeex::wrappers::hdc::text_metrics(text_metric_type &info){
	return (::GetTextMetricsW(value_, &info) != FALSE);
}

grafeex::wrappers::hdc::gdi_object_type grafeex::wrappers::hdc::select(gdi_object_type object){
	return ::SelectObject(value_, object);
}

grafeex::wrappers::hdc::rect_type grafeex::wrappers::hdc::clip_rect() const{
	rect_type value;
	::GetClipBox(value_, value);
	return value;
}
