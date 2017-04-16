#include "visibility_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::visibility_event::visibility_event(object &value)
	: message_event(value){}

grafeex::messaging::visibility_event::~visibility_event() = default;

grafeex::messaging::message_event &grafeex::messaging::visibility_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_visibility_change(*this);

	if (is_propagating()){
		if (is_hidden())
			object_->target()->on_hide(*this);
		else//Show
			object_->target()->on_show(*this);
	}

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		if (is_hidden())
			dynamic_cast<window::object::event_tunnel *>(get_event_())->hide_event_.fire(e);
		else//Show
			dynamic_cast<window::object::event_tunnel *>(get_event_())->show_event_.fire(e);
	}

	return *this;
}

bool grafeex::messaging::visibility_event::is_hidden() const{
	return (object_->info().wparam<bool_type>() == FALSE);
}

grafeex::messaging::visibility_event::reason_type grafeex::messaging::visibility_event::reason() const{
	return static_cast<reason_type>(object_->info().lparam<int>());
}

bool grafeex::messaging::visibility_event::parent_is_minimized() const{
	return (reason() == reason_type::parent_minimized);
}

bool grafeex::messaging::visibility_event::parent_is_restored() const{
	return (reason() == reason_type::parent_restored);
}

bool grafeex::messaging::visibility_event::other_window_is_maximized() const{
	return (reason() == reason_type::other_window_maximized);
}

bool grafeex::messaging::visibility_event::other_window_is_restored() const{
	return (reason() == reason_type::other_window_restored);
}
