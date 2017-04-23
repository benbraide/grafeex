#include "value_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::set_font_event::set_font_event(object &value)
	: message_event(value){}

grafeex::messaging::set_font_event::~set_font_event() = default;

grafeex::messaging::message_event &grafeex::messaging::set_font_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_set_font(*this);
	return *this;
}

grafeex::messaging::get_font_event::get_font_event(object &value)
	: message_event(value){}

grafeex::messaging::get_font_event::~get_font_event() = default;

grafeex::messaging::message_event &grafeex::messaging::get_font_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_get_font(*this);
	return *this;
}

grafeex::messaging::set_text_event::set_text_event(object &value)
	: message_event(value){}

grafeex::messaging::set_text_event::~set_text_event() = default;

grafeex::messaging::message_event &grafeex::messaging::set_text_event::dispatch(){
	object_->target()->text_ = object_->info().lparam<const wchar_t *>();
	if (message_event::dispatch().is_propagating())
		object_->target()->on_set_text(*this);
	return *this;
}

grafeex::messaging::get_text_event::get_text_event(object &value)
	: message_event(value){}

grafeex::messaging::get_text_event::~get_text_event() = default;

grafeex::messaging::message_event &grafeex::messaging::get_text_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_get_text(*this);
	return *this;
}

grafeex::messaging::get_text_length_event::get_text_length_event(object &value)
	: message_event(value){}

grafeex::messaging::get_text_length_event::~get_text_length_event() = default;

grafeex::messaging::message_event &grafeex::messaging::get_text_length_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_get_text_length(*this);
	return *this;
}
