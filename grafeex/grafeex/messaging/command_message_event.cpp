#include "command_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::command_event::command_event(object &value)
	: message_event(value){}

grafeex::messaging::command_event::~command_event() = default;

grafeex::messaging::message_event &grafeex::messaging::command_event::dispatch(){
	if (!is_menu() && !is_accelerator()){//Forward to control
		auto target = control();
		if (target == nullptr)//Unknown target
			return *this;

		target->on_event(*this);
		if (!is_propagating())
			return *this;

		target->on_command(*this);
		if (!is_propagating())
			return *this;

		auto forwarder = application::object::instance->get_event_forwarder(control(), code());
		if (forwarder != nullptr)
			forwarder->forward(*this);
	}
	else if (is_menu())
		object_->target()->on_menu_command(*this);
	else//Accelerator
		object_->target()->on_accelerator(*this);

	return *this;
}

grafeex::messaging::message_event::window_type *grafeex::messaging::command_event::control() const{
	auto handle = object_->info().lparam<wrappers::hwnd::value_type>();
	return (handle == nullptr) ? nullptr : wrappers::hwnd(handle).get_data<window_type *>();
}

grafeex::messaging::command_event::word_ype grafeex::messaging::command_event::id() const{
	return object_->info().low_wparam();
}

grafeex::messaging::command_event::word_ype grafeex::messaging::command_event::code() const{
	return object_->info().high_wparam();
}

bool grafeex::messaging::command_event::is_menu() const{
	return (object_->info().lparam<int>() == 0 && object_->info().high_wparam<int>() == 0);
}

bool grafeex::messaging::command_event::is_accelerator() const{
	return (object_->info().lparam<int>() == 0 && object_->info().high_wparam<int>() != 0);
}
