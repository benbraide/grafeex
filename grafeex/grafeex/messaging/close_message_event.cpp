#include "close_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::close_event::close_event(object &value)
	: message_event(value){}

grafeex::messaging::close_event::~close_event(){}

grafeex::messaging::message_event &grafeex::messaging::close_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_close(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		*this << dynamic_cast<window::object::event_tunnel *>(get_event_())->close_event_.fire(e, true);
	}

	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::close_event::write_bool_(bool value){
	if (!value)//Close rejected
		object_->skip();

	return message_event::write_(static_cast<result_type>(0));
}
