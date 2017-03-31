#include "window_view.h"
#include "window_object.h"

grafeex::window::view::view(object &object)
	: object_(object){}

grafeex::window::view::~view(){}

grafeex::window::view &grafeex::window::view::show(show_mode mode){
	object_.value_.show(mode);
	return *this;
}

grafeex::window::view &grafeex::window::view::hide(){
	object_.value_.show(show_mode::hide);
	return *this;
}

grafeex::window::view &grafeex::window::view::maximize(){
	object_.value_.show(show_mode::maximize);
	return *this;
}

grafeex::window::view &grafeex::window::view::minimize(){
	object_.value_.show(show_mode::minimize);
	return *this;
}

grafeex::window::view &grafeex::window::view::restore(){
	object_.value_.show(show_mode::restore);
	return *this;
}

grafeex::window::view &grafeex::window::view::caption(const std::wstring &value){
	object_.value_.set_text(value);
	return *this;
}

const std::wstring &grafeex::window::view::caption() const{
	return object_.text_;
}
