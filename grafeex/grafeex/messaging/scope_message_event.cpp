#include "scope_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::scope_event::scope_event(object &value)
	: message_event(value){}

grafeex::messaging::scope_event::~scope_event(){}

grafeex::messaging::message_event &grafeex::messaging::scope_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_scope(*this);
	return *this;
}

grafeex::messaging::nc_create_event::nc_create_event(object &value)
	: scope_event(value){}

grafeex::messaging::nc_create_event::~nc_create_event(){}

grafeex::messaging::message_event &grafeex::messaging::nc_create_event::dispatch(){
	object_->target()->initialize_();
	if (scope_event::dispatch().is_propagating())
		*this << object_->target()->on_nc_create(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		*this << dynamic_cast<window::object::event_tunnel *>(get_event_())->create_event_.fire(e, object_->value() != FALSE);
	}

	return *this;
}

bool grafeex::messaging::nc_create_event::is_create() const{
	return true;
}

bool grafeex::messaging::nc_create_event::is_client() const{
	return false;
}

grafeex::messaging::create_event::create_event(object &value)
	: scope_event(value){}

grafeex::messaging::create_event::~create_event(){}

grafeex::messaging::message_event &grafeex::messaging::create_event::dispatch(){
	if (object_->target()->is_top_level()){//Add to top level list
		application::object::instance->lock_.lock();
		application::object::instance->top_level_windows_.push_back(object_->info().owner());
		application::object::instance->lock_.unlock();
	}

	if (scope_event::dispatch().is_propagating())
		*this << object_->target()->on_create(*this);

	return *this;
}

bool grafeex::messaging::create_event::is_create() const{
	return true;
}

bool grafeex::messaging::create_event::is_client() const{
	return true;
}

grafeex::messaging::message_event::result_type grafeex::messaging::create_event::value_from_bool_(bool value){
	return (value ? 0 : -1);
}

grafeex::messaging::nc_destroy_event::nc_destroy_event(object &value)
	: scope_event(value){}

grafeex::messaging::nc_destroy_event::~nc_destroy_event(){}

grafeex::messaging::message_event &grafeex::messaging::nc_destroy_event::dispatch(){
	if (scope_event::dispatch().is_propagating())
		object_->target()->on_nc_destroy(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->destroy_event_.fire(e);
	}

	object_->target()->uninitialize_();
	if (object_->target()->is_top_level()){
		application::object::instance->lock_.lock();

		auto &list = application::object::instance->top_level_windows_;
		auto entry = std::find(list.begin(), list.end(), object_->info().owner());
		if (entry != list.end())//Remove from top level list
			list.erase(entry);

		application::object::instance->lock_.unlock();
	}
	
	return *this;
}

bool grafeex::messaging::nc_destroy_event::is_create() const{
	return false;
}

bool grafeex::messaging::nc_destroy_event::is_client() const{
	return false;
}

grafeex::messaging::destroy_event::destroy_event(object &value)
	: scope_event(value){}

grafeex::messaging::destroy_event::~destroy_event(){}

grafeex::messaging::message_event &grafeex::messaging::destroy_event::dispatch(){
	if (scope_event::dispatch().is_propagating())
		object_->target()->on_destroy(*this);
	return *this;
}

bool grafeex::messaging::destroy_event::is_create() const{
	return false;
}

bool grafeex::messaging::destroy_event::is_client() const{
	return true;
}
