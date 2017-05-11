#include "timer_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::timer_event::timer_event(object &value)
	: message_event(value){}

grafeex::messaging::timer_event::~timer_event() = default;

grafeex::messaging::message_event &grafeex::messaging::timer_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_timer(*this);
	return *this;
}

grafeex::messaging::timer_event::timer_type *grafeex::messaging::timer_event::timer() const{
	return application::object::instance->find_timer(id());
}

grafeex::messaging::timer_event::uint_ptr_type grafeex::messaging::timer_event::id() const{
	return object_->info().wparam<uint_ptr_type>();
}
