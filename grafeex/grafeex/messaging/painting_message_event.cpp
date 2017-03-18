#include "painting_message_event.h"
#include "../window/window_object.h"

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

grafeex::messaging::nc_paint_event::nc_paint_event(object &value)
	: paint_event(value){}

grafeex::messaging::nc_paint_event::~nc_paint_event(){}

grafeex::messaging::message_event &grafeex::messaging::nc_paint_event::dispatch(){
	if (paint_event::dispatch().is_propagating())
		object_->target()->on_nc_paint(*this);
	return *this;
}

grafeex::messaging::paint_event::device_type grafeex::messaging::nc_paint_event::device(){
	return nullptr;
}

bool grafeex::messaging::nc_paint_event::is_client() const{
	return false;
}

grafeex::messaging::client_paint_event::client_paint_event(object &value)
	: paint_event(value){}

grafeex::messaging::client_paint_event::~client_paint_event(){}

grafeex::messaging::message_event &grafeex::messaging::client_paint_event::dispatch(){
	if (paint_event::dispatch().is_propagating())
		object_->target()->on_paint_client(*this);
	return *this;
}

grafeex::messaging::paint_event::device_type grafeex::messaging::client_paint_event::device(){
	return nullptr;
}

bool grafeex::messaging::client_paint_event::is_client() const{
	return true;
}
