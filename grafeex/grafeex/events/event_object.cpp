#include "event_object.h"

grafeex::events::object::object(gui_object_type &target)
	: target_(&target), object_(nullptr){}

grafeex::events::object::object(gui_object_type &target, message_object_type &object)
	: target_(&target), object_(&object){}

grafeex::events::object &grafeex::events::object::prevent_default(){
	GRAFEEX_SET(states_, state::default_prevented);
	return *this;
}

grafeex::events::object &grafeex::events::object::do_default(){
	GRAFEEX_SET(states_, state::unhandled);
	return *this;
}

grafeex::events::object &grafeex::events::object::stop_propagation(){
	GRAFEEX_SET(states_, state::propagation_stopped);
	return *this;
}

bool grafeex::events::object::default_is_prevented() const{
	return GRAFEEX_IS(states_, state::default_prevented);
}

bool grafeex::events::object::is_default() const{
	return GRAFEEX_IS(states_, state::unhandled);
}

bool grafeex::events::object::is_propagating() const{
	return !GRAFEEX_IS(states_, state::propagation_stopped);
}

grafeex::events::object::gui_object_type &grafeex::events::object::target() const{
	return *target_;
}

grafeex::events::object::message_object_type *grafeex::events::object::message_object() const{
	return object_;
}
