#include "scope_message_event.h"

grafeex::messaging::scope_event::scope_event(object &value)
	: message_event(value){}

grafeex::messaging::scope_event::~scope_event(){}

grafeex::messaging::message_event &grafeex::messaging::scope_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_scope(*this);
	return *this;
}
