#include "painting_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::erase_background_event::erase_background_event(object &value)
	: message_event(value){}

grafeex::messaging::erase_background_event::~erase_background_event() = default;

grafeex::messaging::message_event &grafeex::messaging::erase_background_event::dispatch(){
	if (object_->target()->renderer_ != nullptr)
		object_->target()->renderer_->reset();

	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_erase_background(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->erase_background_event_.fire(e);
	}

	return *this;
}

grafeex::messaging::erase_background_event::device_type grafeex::messaging::erase_background_event::device() const{
	return object_->info().wparam<device_type>();
}

grafeex::messaging::paint_event::paint_event(object &value)
	: message_event(value){}

grafeex::messaging::paint_event::~paint_event() = default;

grafeex::messaging::message_event &grafeex::messaging::paint_event::dispatch(){
	if (object_->target()->renderer_ != nullptr)
		object_->target()->renderer_->reset();

	if (message_event::dispatch().is_propagating())
		object_->target()->on_paint(*this);

	return *this;
}

grafeex::messaging::nc_paint_event::nc_paint_event(object &value)
	: paint_event(value){}

grafeex::messaging::nc_paint_event::~nc_paint_event() = default;

grafeex::messaging::message_event &grafeex::messaging::nc_paint_event::dispatch(){
	if (paint_event::dispatch().is_propagating())
		object_->target()->on_nc_paint(*this);
	return *this;
}

grafeex::messaging::paint_event::device_type grafeex::messaging::nc_paint_event::device() const{
	return nullptr;
}

bool grafeex::messaging::nc_paint_event::is_client() const{
	return false;
}

grafeex::messaging::client_paint_event::client_paint_event(object &value)
	: paint_event(value){}

grafeex::messaging::client_paint_event::~client_paint_event(){
	end();
}

grafeex::messaging::message_event &grafeex::messaging::client_paint_event::dispatch(){
	if (paint_event::dispatch().is_propagating())
		object_->target()->on_paint_client(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->paint_event_.fire(e);
	}

	return *this;
}

grafeex::messaging::paint_event::device_type grafeex::messaging::client_paint_event::device() const{
	return (info_ == nullptr) ? nullptr : info_->hdc;
}

bool grafeex::messaging::client_paint_event::is_client() const{
	return true;
}

bool grafeex::messaging::client_paint_event::begin(){
	if (info_ != nullptr)
		return false;

	info_ = std::make_shared<info_type>();
	if (::BeginPaint(*object_->target(), info_.get()) == nullptr){
		info_ = nullptr;
		return false;
	}

	skip();
	return true;
}

bool grafeex::messaging::client_paint_event::end(){
	if (info_ == nullptr || ::EndPaint(*object_->target(), info_.get()) == FALSE)
		return false;

	info_ = nullptr;
	return true;
}

bool grafeex::messaging::client_paint_event::has_begun() const{
	return (info_ != nullptr);
}

bool grafeex::messaging::client_paint_event::erase_background() const{
	return (info_ == nullptr) ? false : (info_->fErase != FALSE);
}

grafeex::messaging::client_paint_event::rect_type grafeex::messaging::client_paint_event::update_rect() const{
	return (info_ == nullptr) ? rect_type{} : info_->rcPaint;
}

grafeex::messaging::print_client_event::print_client_event(object &value)
	: message_event(value){}

grafeex::messaging::print_client_event::~print_client_event() = default;

grafeex::messaging::message_event &grafeex::messaging::print_client_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_print_client(*this);
	return *this;
}

grafeex::messaging::print_client_event::device_type grafeex::messaging::print_client_event::device() const{
	return object_->info().wparam<device_type>();
}

grafeex::messaging::print_client_event::option grafeex::messaging::print_client_event::options() const{
	return static_cast<option>(object_->info().lparam<unsigned int>());
}

grafeex::messaging::print_event::print_event(object &value)
	: message_event(value){}

grafeex::messaging::print_event::~print_event() = default;

grafeex::messaging::message_event &grafeex::messaging::print_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_print(*this);
	return *this;
}

grafeex::messaging::print_event::device_type grafeex::messaging::print_event::device() const{
	return object_->info().wparam<device_type>();
}

grafeex::messaging::print_event::option grafeex::messaging::print_event::options() const{
	return static_cast<option>(object_->info().lparam<unsigned int>());
}
