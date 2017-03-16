#include "message_event.h"

grafeex::messaging::message_event::message_event()
	: object_(nullptr), states_(state::nil){}

grafeex::messaging::message_event::message_event(object &value)
	: object_(&value), states_(state::nil){}

grafeex::messaging::message_event::~message_event(){}

grafeex::messaging::message_event &grafeex::messaging::message_event::handle(handle_type type){
	object_->handle(type);
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::skip(){
	object_->skip();
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::reply(bool value){
	object_->reply(value_from_bool_(value));
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::reply(){
	object_->reply();
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::operator=(result_type value){
	return object_->has_value() ? *this : write_(value);
}

grafeex::messaging::message_event &grafeex::messaging::message_event::operator =(bool value){
	return object_->has_value() ? *this : write_bool_(value);
}

grafeex::messaging::message_event &grafeex::messaging::message_event::operator<<(result_type value){
	return write_(value);
}

grafeex::messaging::message_event &grafeex::messaging::message_event::operator <<(bool value){
	return write_bool_(value);
}

bool grafeex::messaging::message_event::is_sent() const{
	return object_->is_sent();
}

bool grafeex::messaging::message_event::is_cross_thread() const{
	return object_->is_cross_thread();
}

bool grafeex::messaging::message_event::is_replied() const{
	return object_->is_replied();
}

bool grafeex::messaging::message_event::has_value() const{
	return object_->has_value();
}

bool grafeex::messaging::message_event::is_default() const{
	return object_->is_default();
}

bool grafeex::messaging::message_event::is_skipped() const{
	return object_->is_skipped();
}

bool grafeex::messaging::message_event::is_handled() const{
	return object_->is_handled();
}

grafeex::messaging::message_event &grafeex::messaging::message_event::disable_event(){
	GRAFEEX_SET(states_, state::event_disabled);
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::stop_propagation(){
	GRAFEEX_SET(states_, state::propagation_stopped);
	return *this;
}

bool grafeex::messaging::message_event::event_is_disabled() const{
	return GRAFEEX_IS(states_, state::event_disabled);
}

bool grafeex::messaging::message_event::is_propagating() const{
	return !GRAFEEX_IS(states_, state::propagation_stopped);
}

const grafeex::messaging::object &grafeex::messaging::message_event::get_object() const{
	return *object_;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::write_(result_type value){
	object_->operator<<(value);
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::message_event::write_bool_(bool value){
	return write_(value_from_bool_(value));
}

grafeex::messaging::message_event::result_type grafeex::messaging::message_event::value_from_bool_(bool value){
	return (value ? TRUE : FALSE);
}
