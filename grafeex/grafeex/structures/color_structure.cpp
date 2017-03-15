#include "color_structure.h"

grafeex::structures::color::color()
	: base_type(RGBA(0, 0, 0, 255)){}

grafeex::structures::color::color(value_type value)
	: base_type(value){}

grafeex::structures::color::color(value_type rgb, field_type alpha)
	: base_type(RGBA(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb), alpha)){}

grafeex::structures::color::color(value_type rgb, alpha_type alpha)
	: base_type(RGBA(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb), static_cast<field_type>(alpha))){}

grafeex::structures::color::color(field_type red, field_type green, field_type blue, field_type alpha)
	: base_type(RGBA(red, green, blue, alpha)){}

grafeex::structures::color::color(field_type red, field_type green, field_type blue, alpha_type alpha)
	: base_type(RGBA(red, green, blue, static_cast<field_type>(alpha))){}

grafeex::structures::color::color(float red, float green, float blue, float alpha)
	: base_type(RGBA(static_cast<field_type>(red * 255), static_cast<field_type>(green * 255),
		static_cast<field_type>(blue * 255), static_cast<field_type>(alpha * 255))){}

grafeex::structures::color::color(float red, float green, float blue, alpha_type alpha)
	: base_type(base_type(RGBA(static_cast<field_type>(red * 255), static_cast<field_type>(green * 255),
		static_cast<field_type>(blue * 255), static_cast<field_type>(alpha)))){}

grafeex::structures::color::color(named_type name, field_type alpha)
	: color(static_cast<value_type>(name), alpha){}

grafeex::structures::color::color(named_type name, alpha_type alpha)
	: color(static_cast<value_type>(name), static_cast<field_type>(alpha)){}

bool grafeex::structures::color::operator ==(named_type rhs) const{
	return (RGB(GetRValue(value_), GetGValue(value_), GetBValue(value_)) == static_cast<value_type>(rhs));
}

bool grafeex::structures::color::operator !=(named_type rhs) const{
	return !(*this == rhs);
}

bool grafeex::structures::operator ==(grafeex::structures::color::named_type lhs, const grafeex::structures::color &rhs){
	return (rhs == lhs);
}

bool grafeex::structures::operator !=(grafeex::structures::color::named_type lhs, const grafeex::structures::color &rhs){
	return (rhs != lhs);
}

grafeex::structures::color &grafeex::structures::color::red(field_type value){
	value_ = RGBA(value, GetGValue(value_), GetBValue(value_), GetAValue(value_));
	return *this;
}

grafeex::structures::color &grafeex::structures::color::red(float value){
	value_ = RGBA(static_cast<field_type>(value * 255), GetGValue(value_), GetBValue(value_), GetAValue(value_));
	return *this;
}

grafeex::structures::color::field_type grafeex::structures::color::red() const{
	return GetRValue(value_);
}

float grafeex::structures::color::relative_red() const{
	return (GetRValue(value_) / 255.0f);
}

grafeex::structures::color &grafeex::structures::color::green(field_type value){
	value_ = RGBA(GetRValue(value_), value, GetBValue(value_), GetAValue(value_));
	return *this;
}

grafeex::structures::color &grafeex::structures::color::green(float value){
	value_ = RGBA(GetRValue(value_), static_cast<field_type>(value * 255), GetBValue(value_), GetAValue(value_));
	return *this;
}

grafeex::structures::color::field_type grafeex::structures::color::green() const{
	return GetGValue(value_);
}

float grafeex::structures::color::relative_green() const{
	return (GetGValue(value_) / 255.0f);
}

grafeex::structures::color &grafeex::structures::color::blue(field_type value){
	value_ = RGBA(GetRValue(value_), GetGValue(value_), value, GetAValue(value_));
	return *this;
}

grafeex::structures::color &grafeex::structures::color::blue(float value){
	value_ = RGBA(GetRValue(value_), GetGValue(value_), static_cast<field_type>(value * 255), GetAValue(value_));
	return *this;
}

grafeex::structures::color::field_type grafeex::structures::color::blue() const{
	return GetBValue(value_);
}

float grafeex::structures::color::relative_blue() const{
	return (GetBValue(value_) / 255.0f);
}

grafeex::structures::color &grafeex::structures::color::alpha(field_type value, bool multiply){
	if (multiply){
		auto rgba = reinterpret_cast<value_type *>(&value_);

		rgba[0] = rgba[0] * value / static_cast<field_type>(0xFF);
		rgba[1] = rgba[1] * value / static_cast<field_type>(0xFF);
		rgba[2] = rgba[2] * value / static_cast<field_type>(0xFF);
		rgba[3] = value;
	}
	else//Set alpha channel
		value_ = RGBA(GetRValue(value_), GetGValue(value_), GetBValue(value_), value);

	return *this;
}

grafeex::structures::color &grafeex::structures::color::alpha(float value, bool multiply){
	if (multiply)
		return alpha(static_cast<field_type>(value * 255), true);
	
	value_ = RGBA(GetRValue(value_), GetGValue(value_), GetBValue(value_), static_cast<field_type>(value * 255));
	return *this;
}

grafeex::structures::color &grafeex::structures::color::alpha(alpha_type value, bool multiply){
	if (multiply)
		return alpha(static_cast<field_type>(value), true);

	value_ = RGBA(GetRValue(value_), GetGValue(value_), GetBValue(value_), static_cast<field_type>(value));
	return *this;
}

grafeex::structures::color::field_type grafeex::structures::color::alpha() const{
	return GetAValue(value_);
}

float grafeex::structures::color::relative_alpha() const{
	return (GetAValue(value_) / 255.0f);
}

grafeex::structures::color &grafeex::structures::color::name(named_type value){
	return rgb(static_cast<value_type>(value));
}

grafeex::structures::color::named_type grafeex::structures::color::name() const{
	return static_cast<named_type>(rgb());
}

grafeex::structures::color &grafeex::structures::color::rgb(value_type value){
	value_ = RGBA(GetRValue(value), GetGValue(value), GetBValue(value), alpha());
	return *this;
}

grafeex::structures::color &grafeex::structures::color::rgb(field_type red, field_type green, field_type blue){
	value_ = RGBA(red, green, blue, alpha());
	return *this;
}

grafeex::structures::color::value_type grafeex::structures::color::rgb() const{
	return  RGB(GetRValue(value_), GetGValue(value_), GetBValue(value_));
}

grafeex::structures::color::value_type grafeex::structures::color::bgr() const{
	return  RGB(GetBValue(value_), GetGValue(value_), GetRValue(value_));
}

grafeex::structures::color &grafeex::structures::color::rgba(value_type value){
	value_ = value;
	return *this;
}

grafeex::structures::color &grafeex::structures::color::rgba(field_type red, field_type green, field_type blue, field_type alpha){
	value_ = RGBA(red, green, blue, alpha);
	return *this;
}

grafeex::structures::color &grafeex::structures::color::rgba(field_type red, field_type green, field_type blue, alpha_type alpha){
	value_ = RGBA(red, green, blue, static_cast<field_type>(alpha));
	return *this;
}

grafeex::structures::color::value_type grafeex::structures::color::rgba() const{
	return value_;
}

bool grafeex::structures::color::is_transparent() const{
	return (GetAValue(value_) == static_cast<field_type>(0));
}

bool grafeex::structures::color::is_opaque() const{
	return (GetAValue(value_) == static_cast<field_type>(255));
}

bool grafeex::structures::color::is_named_alpha() const{
	return (is_opaque() || is_transparent());
}

grafeex::structures::color &grafeex::structures::color::make_different(const color &target){
	auto rgb = RGB(GetRValue(value_), GetGValue(value_), GetBValue(value_));
	if (rgb != RGB(GetRValue(target.value_), GetGValue(target.value_), GetBValue(target.value_)))
		return *this;//Different colors

	auto red = GetRValue(value_);
	if (red > 0)
		this->red(static_cast<field_type>(red - 1));
	else
		this->red(static_cast<field_type>(red + 1));

	return *this;
}

grafeex::structures::color &grafeex::structures::color::make_different(const color &first, const color &second){
	auto rgb = this->rgb(), first_rgb = first.rgb(), second_rgb = second.rgb();
	if (rgb != first_rgb && rgb != second_rgb)
		return *this;//Different colors

	auto red = this->red();
	if (rgb == first_rgb){
		if (red > static_cast<field_type>(2)){
			if (--red == second.red())
				--red;
		}
		else if (++red == second.red())
			++red;
	}
	else if (red > static_cast<field_type>(2)){
		if (--red == first.red())
			--red;
	}
	else if (++red == first.red())
		++red;

	this->red(red);
	return *this;
}

grafeex::structures::color grafeex::structures::color::get_different(const color &target) const{
	auto copy(*this);
	return copy.make_different(target);
}

grafeex::structures::color grafeex::structures::color::get_different(const color &first, const color &second) const{
	auto copy(*this);
	return copy.make_different(first, second);
}
