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
	application::object::instance->lock_.lock();

	timer_type *value;
	auto &timer_cache = application::object::instance->timer_cache_;

	auto entry = timer_cache.find(id());
	if (entry == timer_cache.end())
		value = nullptr;
	else//Found in cache
		value = entry->second;

	application::object::instance->lock_.unlock();
	return value;
}

grafeex::messaging::timer_event::unit_ptr_type grafeex::messaging::timer_event::id() const{
	return object_->info().wparam<unit_ptr_type>();
}
