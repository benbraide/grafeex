#include "drawing_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::draw_event::draw_event(object &value)
	: message_event(value), info_(value.info().lparam<info_type *>()){}

grafeex::messaging::draw_event::~draw_event(){}

grafeex::messaging::message_event &grafeex::messaging::draw_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		;
	return *this;
}
