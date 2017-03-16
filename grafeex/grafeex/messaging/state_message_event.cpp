#include "state_message_event.h"

grafeex::messaging::activate_event::activate_event(object &value)
	: message_event(value){}

grafeex::messaging::activate_event::~activate_event(){}

grafeex::messaging::message_event &grafeex::messaging::activate_event::dispatch(){
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
	return *this;
}

grafeex::messaging::enable_event::~enable_event(){}

bool grafeex::messaging::enable_event::is_enabled() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}
