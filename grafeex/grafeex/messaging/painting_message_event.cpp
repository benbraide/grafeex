#include "painting_message_event.h"

grafeex::messaging::erase_background_event::erase_background_event(object &value)
	: message_event(value){}

grafeex::messaging::erase_background_event::~erase_background_event(){}

grafeex::messaging::message_event &grafeex::messaging::erase_background_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_erase_background(*this);
	return *this;
}

grafeex::messaging::erase_background_event::device_type grafeex::messaging::erase_background_event::device(){
	return object_->info().wparam<device_type>();
}

grafeex::messaging::paint_event::paint_event(object &value)
	: message_event(value){}

grafeex::messaging::paint_event::~paint_event(){}

grafeex::messaging::message_event &grafeex::messaging::paint_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_paint(*this);
	return *this;
}
