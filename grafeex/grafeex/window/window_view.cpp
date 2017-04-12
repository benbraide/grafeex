#include "window_view.h"
#include "window_object.h"

grafeex::window::view::view(object &object)
	: object_(&object){}

grafeex::window::view::~view(){}

grafeex::window::view &grafeex::window::view::enable(){
	object_->value_.enable(true);
	return *this;
}

grafeex::window::view &grafeex::window::view::disable(){
	object_->value_.enable(false);
	return *this;
}

bool grafeex::window::view::enabled() const{
	return object_->value_.is_enabled();
}

grafeex::window::view &grafeex::window::view::show(show_mode mode){
	object_->value_.show(mode);
	return *this;
}

grafeex::window::view &grafeex::window::view::hide(){
	object_->value_.show(show_mode::hide);
	return *this;
}

bool grafeex::window::view::visisble() const{
	return object_->value_.is_visible();
}

grafeex::window::view &grafeex::window::view::maximize(){
	object_->value_.show(show_mode::maximize);
	return *this;
}

bool grafeex::window::view::maximized() const{
	return object_->value_.is_maximized();
}

grafeex::window::view &grafeex::window::view::minimize(){
	object_->value_.show(show_mode::minimize);
	return *this;
}

bool grafeex::window::view::minimized() const{
	return object_->value_.is_minimized();
}

grafeex::window::view &grafeex::window::view::restore(){
	object_->value_.show(show_mode::restore);
	return *this;
}

grafeex::window::view &grafeex::window::view::caption(const std::wstring &value){
	object_->value_.set_text(value);
	return *this;
}

const std::wstring &grafeex::window::view::caption() const{
	return object_->text_;
}

grafeex::window::view &grafeex::window::view::background_color(const color_type &value){
	return background_color(::D2D1::ColorF(value.relative_red(), value.relative_green(), value.relative_blue(), value.relative_alpha()));
}

grafeex::window::view &grafeex::window::view::background_color(const d2d_color_type &value){
	background_color_ = std::make_shared<d2d_color_type>(value);
	object_->value_.invalidate();
	return *this;
}

grafeex::window::view::d2d_color_type grafeex::window::view::background_color() const{
	return (background_color_ == nullptr) ? d2d_color_type{} : *background_color_;
}

bool grafeex::window::view::has_background_color() const{
	return (background_color_ != nullptr);
}
