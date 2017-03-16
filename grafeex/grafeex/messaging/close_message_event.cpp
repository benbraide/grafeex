#include "close_message_event.h"

grafeex::messaging::close_event::close_event(object &value)
	: message_event(value){}

grafeex::messaging::close_event::~close_event(){}

grafeex::messaging::message_event &grafeex::messaging::close_event::dispatch(){
	return *this;
}

grafeex::messaging::message_event &grafeex::messaging::close_event::write_bool_(bool value){
	if (!value)//Close rejected
		object_->skip();

	return message_event::write_(static_cast<result_type>(0));
}
