#include "state_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::activate_event::activate_event(object &value)
	: message_event(value){}

grafeex::messaging::activate_event::~activate_event(){}

grafeex::messaging::message_event &grafeex::messaging::activate_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_active_change(*this);

	if (is_propagating()){
		if (is_active())
			object_->target()->on_activate(*this);
		else//Deactivate
			object_->target()->on_deactivate(*this);
	}

	return *this;
}

bool grafeex::messaging::activate_event::is_active() const{
	switch (object_->info().low_wparam()){
	case WA_ACTIVE:
	case WA_CLICKACTIVE:
		return true;
	default:
		break;
	}
	
	return false;
}

bool grafeex::messaging::activate_event::is_click() const{
	return (object_->info().low_wparam() == WA_CLICKACTIVE);
}

bool grafeex::messaging::activate_event::is_minimized() const{
	return (object_->info().high_wparam<bool_type>() != FALSE);
}

grafeex::messaging::enable_event::enable_event(object &value)
	: message_event(value){}

grafeex::messaging::message_event &grafeex::messaging::enable_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_enable_change(*this);

	if (is_propagating()){
		if (is_enabled())
			object_->target()->on_enable(*this);
		else//Disable
			object_->target()->on_disable(*this);
	}

	return *this;
}

grafeex::messaging::enable_event::~enable_event(){}

bool grafeex::messaging::enable_event::is_enabled() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}
