#include "system_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::theme_changed_event::theme_changed_event(object &value)
	: message_event(value){}

grafeex::messaging::theme_changed_event::~theme_changed_event() = default;

grafeex::messaging::message_event &grafeex::messaging::theme_changed_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_theme_changed(*this);
	return *this;
}

grafeex::messaging::user_changed_event::user_changed_event(object &value)
	: message_event(value){}

grafeex::messaging::user_changed_event::~user_changed_event() = default;

grafeex::messaging::message_event &grafeex::messaging::user_changed_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_user_changed(*this);
	return *this;
}

grafeex::messaging::input_language_changed_event::input_language_changed_event(object &value)
	: message_event(value){}

grafeex::messaging::input_language_changed_event::~input_language_changed_event() = default;

grafeex::messaging::message_event &grafeex::messaging::input_language_changed_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_input_language_changed(*this);
	return *this;
}

grafeex::messaging::input_language_changed_event::wparam_type grafeex::messaging::input_language_changed_event::character_set() const{
	return object_->info().wparam();
}

grafeex::messaging::input_language_changed_event::lparam_type grafeex::messaging::input_language_changed_event::locale_id() const{
	return object_->info().lparam();
}

grafeex::messaging::input_language_change_request_event::input_language_change_request_event(object &value)
	: message_event(value){}

grafeex::messaging::input_language_change_request_event::~input_language_change_request_event() = default;

grafeex::messaging::message_event &grafeex::messaging::input_language_change_request_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_input_language_change_request(*this);

	if (object_->value() == 0u)
		skip();//Rejected

	return *this;
}

grafeex::messaging::input_language_change_request_event::wparam_type grafeex::messaging::input_language_change_request_event::locale() const{
	return object_->info().wparam();
}

grafeex::messaging::input_language_change_request_event::lparam_type grafeex::messaging::input_language_change_request_event::locale_id() const{
	return object_->info().lparam();
}

grafeex::messaging::display_changed_event::display_changed_event(object &value)
	: message_event(value){}

grafeex::messaging::display_changed_event::~display_changed_event() = default;

grafeex::messaging::message_event &grafeex::messaging::display_changed_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_display_changed(*this);
	return *this;
}

grafeex::messaging::display_changed_event::wparam_type grafeex::messaging::display_changed_event::image_depth() const{
	return object_->info().wparam();
}

grafeex::messaging::display_changed_event::word_type grafeex::messaging::display_changed_event::horizontal_resolution() const{
	return object_->info().low_lparam();
}

grafeex::messaging::display_changed_event::word_type grafeex::messaging::display_changed_event::vertical_resolution() const{
	return object_->info().high_lparam();
}

grafeex::messaging::capture_changed_event::capture_changed_event(object &value)
	: message_event(value){}

grafeex::messaging::capture_changed_event::~capture_changed_event() = default;

grafeex::messaging::message_event &grafeex::messaging::capture_changed_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_capture_changed(*this);
	return *this;
}

grafeex::messaging::message_event::window_type *grafeex::messaging::capture_changed_event::window_with_capture() const{
	return wrappers::hwnd(object_->info().lparam<wrappers::hwnd::value_type>()).get_data<window_type *>();
}
