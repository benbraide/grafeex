#include "notify_message_event.h"
#include "message_event_forwarder.h"

#include "../window/window_object.h"

grafeex::messaging::notify_event::notify_event(object &value)
	: message_event(value){}

grafeex::messaging::notify_event::~notify_event(){}

grafeex::messaging::message_event &grafeex::messaging::notify_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_notify(*this);

	if (!is_propagating())
		return *this;

	auto target = control();
	if (target == nullptr)//Unknown target
		return *this;

	target->on_event(*this);
	if (!is_propagating())
		return *this;

	target->on_notify(*this);
	if (!is_propagating())
		return *this;

	auto cmd_list = target->notify_forwarder_list_ref_;
	if (cmd_list != nullptr){
		auto message_dispatcher = cmd_list->find(code());
		if (message_dispatcher != cmd_list->end())
			message_dispatcher->second->dispatch(*this);
	}

	return *this;
}

grafeex::messaging::message_event::window_type *grafeex::messaging::notify_event::control() const{
	return wrappers::hwnd(info().hwndFrom).get_data<window_type *>();
}

grafeex::messaging::notify_event::uint_ptr_type grafeex::messaging::notify_event::id() const{
	return info().idFrom;
}

grafeex::messaging::notify_event::uint_type grafeex::messaging::notify_event::code() const{
	return info().code;
}

grafeex::messaging::notify_event::info_type &grafeex::messaging::notify_event::info() const{
	return *object_->info().lparam<info_type *>();
}
