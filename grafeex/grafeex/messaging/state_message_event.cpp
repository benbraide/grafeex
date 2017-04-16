#include "state_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::activate_app_event::activate_app_event(object &value)
	: message_event(value){}

grafeex::messaging::activate_app_event::~activate_app_event() = default;

grafeex::messaging::message_event &grafeex::messaging::activate_app_event::dispatch(){
	application::object::instance->app_activate_(*this);
	return *this;
}

grafeex::messaging::activate_app_event::dword_type grafeex::messaging::activate_app_event::other() const{
	return object_->info().lparam<dword_type>();
}

bool grafeex::messaging::activate_app_event::is_active() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}

grafeex::messaging::nc_activate_event::nc_activate_event(object &value)
	: message_event(value){}

grafeex::messaging::nc_activate_event::~nc_activate_event() = default;

grafeex::messaging::message_event &grafeex::messaging::nc_activate_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_nc_active_change(*this);

	if (is_propagating()){
		if (is_active())
			object_->target()->on_nc_activate(*this);
		else//Deactivate
			*this << object_->target()->on_nc_deactivate(*this);
	}

	return *this;
}

bool grafeex::messaging::nc_activate_event::is_active() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}

grafeex::messaging::activate_event::activate_event(object &value)
	: message_event(value){}

grafeex::messaging::activate_event::~activate_event() = default;

grafeex::messaging::message_event &grafeex::messaging::activate_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_active_change(*this);

	if (is_propagating()){
		if (is_active())
			object_->target()->on_activate(*this);
		else//Deactivate
			object_->target()->on_deactivate(*this);
	}

	if (is_active()){//Set active dialog if applicable
		if (object_->target()->is_dialog() && !is_minimized())
			application::object::instance->active_dialog_ = object_->target();
	}
	else if (application::object::instance->active_dialog_ == object_->target())
		application::object::instance->active_dialog_ = nullptr;

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

grafeex::messaging::child_activate_event::child_activate_event(object &value)
	: message_event(value){}

grafeex::messaging::child_activate_event::~child_activate_event() = default;

grafeex::messaging::message_event &grafeex::messaging::child_activate_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_child_activate(*this);
	return *this;
}

grafeex::messaging::cancel_mode_event::cancel_mode_event(object &value)
	: message_event(value){}

grafeex::messaging::cancel_mode_event::~cancel_mode_event() = default;

grafeex::messaging::message_event &grafeex::messaging::cancel_mode_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_cancel_mode(*this);
	return *this;
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

grafeex::messaging::enable_event::~enable_event() = default;

bool grafeex::messaging::enable_event::is_enabled() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}
