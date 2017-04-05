#include "gdi_brush.h"

grafeex::gdi::brush_common::brush_common()
	: base_type(nullptr){}

grafeex::gdi::brush_common::brush_common(const info_type &info)
	: base_type(nullptr){
	create(info);
}

grafeex::gdi::brush_common::brush_common(const brush_common &target)
	: brush_common(target.info_){}

grafeex::gdi::brush_common::~brush_common(){
	destroy();
}

grafeex::gdi::brush_common &grafeex::gdi::brush_common::operator=(const brush_common &target){
	if (!is_created() || destroy())
		create(target.info_);
	return *this;
}

grafeex::gdi::brush_common::operator value_type() const{
	return value_;
}

grafeex::gdi::brush_common::operator wrapper_type() const{
	return static_cast<value_type>(value_);
}

grafeex::gdi::brush_common::object_type grafeex::gdi::brush_common::type() const{
	return object_type::brush;
}

bool grafeex::gdi::brush_common::create(){
	if (is_created() || (value_ = ::CreateBrushIndirect(&info_)) == nullptr)
		return false;

	init_();
	return true;
}

bool grafeex::gdi::brush_common::create(const info_type &info){
	if (is_created())
		return false;

	info_ = info;
	color_ = info_.lbColor;

	return create();
}

bool grafeex::gdi::brush_common::destroy(){
	if (!is_created() || ::DeleteObject(value_) == FALSE)
		return false;

	uninit_();
	value_ = nullptr;

	return true;
}

bool grafeex::gdi::brush_common::is_created() const{
	return (value_ != nullptr);
}

grafeex::gdi::brush_common &grafeex::gdi::brush_common::style(brush_style value){
	info_.lbStyle = static_cast<uint_type>(value);
	if (is_created())//Update
		recreate_();

	return *this;
}

grafeex::gdi::brush_style grafeex::gdi::brush_common::style() const{
	return static_cast<brush_style>(info_.lbHatch);
}

grafeex::gdi::brush_common &grafeex::gdi::brush_common::hatch(brush_hatch value){
	info_.lbHatch = static_cast<ulong_ptr_type>(value);
	if (is_created())//Update
		recreate_();

	return *this;
}

grafeex::gdi::brush_hatch grafeex::gdi::brush_common::hatch() const{
	return static_cast<brush_hatch>(info_.lbHatch);
}

grafeex::gdi::brush_common &grafeex::gdi::brush_common::color(const color_type &value){
	info_.lbColor = (color_ = value).rgb();
	if (is_created())//Update
		recreate_();

	return *this;
}

const grafeex::gdi::brush_common::color_type & grafeex::gdi::brush_common::color() const{
	return color_;
}

const grafeex::gdi::brush_common::info_type & grafeex::gdi::brush_common::info() const{
	return info_;
}

void grafeex::gdi::brush_common::recreate_(){
	destroy();
	create();
}

void grafeex::gdi::brush_common::retrieve_info_(){
	::GetObjectW(value_, sizeof(info_type), &info_);
}
