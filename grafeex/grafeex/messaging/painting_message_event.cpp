#include "painting_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::erase_background_event::erase_background_event(object &value)
	: message_event(value){}

grafeex::messaging::erase_background_event::~erase_background_event(){
	end_drawing();
}

grafeex::messaging::message_event &grafeex::messaging::erase_background_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_erase_background(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->erase_background_event_.fire(e);
	}

	return *this;
}

grafeex::messaging::erase_background_event::hdc_type grafeex::messaging::erase_background_event::device(){
	return object_->info().wparam<hdc_type>();
}

grafeex::messaging::erase_background_event::rect_type grafeex::messaging::erase_background_event::clip_rect(){
	return wrappers::hdc(device()).clip_rect();
}

void grafeex::messaging::erase_background_event::create_render_holder_(){
	if (render_holder_ == nullptr){
		render_holder_ = std::make_shared<render_holder_type>(object_->target()->hdc_render_manager());
		render_holder_->renderer()->BindDC(device(), clip_rect());
	}
}

void grafeex::messaging::erase_background_event::on_error_(hresult_type err){
	object_->target()->on_drawing_error(err, true);
	if (err == D2DERR_RECREATE_TARGET)
		object_->target()->on_recreate_drawing_resources(true);
}

grafeex::messaging::paint_event::paint_event(object &value)
	: message_event(value){}

grafeex::messaging::paint_event::~paint_event(){
	end_drawing();
}

grafeex::messaging::message_event &grafeex::messaging::paint_event::dispatch(){
	if (object_->target()->renderer_ != nullptr)
		object_->target()->renderer_->reset();

	if (message_event::dispatch().is_propagating())
		object_->target()->on_paint(*this);

	return *this;
}

void grafeex::messaging::paint_event::create_render_holder_(){
	if (render_holder_ == nullptr){
		render_holder_ = std::make_shared<render_holder_type>(object_->target()->hdc_render_manager());
		render_holder_->renderer()->BindDC(device(), clip_rect());
	}
}

void grafeex::messaging::paint_event::on_error_(hresult_type err){
	object_->target()->on_drawing_error(err, true);
	if (err == D2DERR_RECREATE_TARGET)
		object_->target()->on_recreate_drawing_resources(true);
}

grafeex::messaging::nc_paint_event::nc_paint_event(object &value)
	: paint_event(value){}

grafeex::messaging::nc_paint_event::~nc_paint_event() = default;

grafeex::messaging::message_event &grafeex::messaging::nc_paint_event::dispatch(){
	if (paint_event::dispatch().is_propagating())
		object_->target()->on_nc_paint(*this);
	return *this;
}

grafeex::messaging::paint_event::hdc_type grafeex::messaging::nc_paint_event::device(){
	return nullptr;
}

bool grafeex::messaging::nc_paint_event::is_client() const{
	return false;
}

grafeex::messaging::paint_event::rect_type grafeex::messaging::nc_paint_event::clip_rect(){
	return wrappers::hdc(device()).clip_rect();
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

grafeex::messaging::paint_event::hdc_type grafeex::messaging::client_paint_event::device(){
	begin();
	return info_->hdc;
}

bool grafeex::messaging::client_paint_event::is_client() const{
	return true;
}

grafeex::messaging::client_paint_event::rect_type grafeex::messaging::client_paint_event::clip_rect(){
	begin();
	return info_->rcPaint;
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

bool grafeex::messaging::client_paint_event::erase_background(){
	begin();
	return (info_->fErase != FALSE);
}

grafeex::messaging::print_client_event::print_client_event(object &value)
	: message_event(value){}

grafeex::messaging::print_client_event::~print_client_event(){
	end_drawing();
}

grafeex::messaging::message_event &grafeex::messaging::print_client_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_print_client(*this);
	return *this;
}

grafeex::messaging::print_client_event::hdc_type grafeex::messaging::print_client_event::device(){
	return object_->info().wparam<hdc_type>();
}

grafeex::messaging::print_client_event::rect_type grafeex::messaging::print_client_event::clip_rect(){
	return wrappers::hdc(device()).clip_rect();
}

grafeex::messaging::print_client_event::option grafeex::messaging::print_client_event::options() const{
	return static_cast<option>(object_->info().lparam<unsigned int>());
}

bool grafeex::messaging::print_client_event::erase_background() const{
	return GRAFEEX_IS(options(), option::erase_background);
}

void grafeex::messaging::print_client_event::create_render_holder_(){
	if (render_holder_ == nullptr){
		render_holder_ = std::make_shared<render_holder_type>(object_->target()->hdc_render_manager());
		render_holder_->renderer()->BindDC(device(), clip_rect());
	}
}

void grafeex::messaging::print_client_event::on_error_(hresult_type err){
	object_->target()->on_drawing_error(err, true);
	if (err == D2DERR_RECREATE_TARGET)
		object_->target()->on_recreate_drawing_resources(true);
}

grafeex::messaging::print_event::print_event(object &value)
	: message_event(value){}

grafeex::messaging::print_event::~print_event(){
	end_drawing();
}

grafeex::messaging::message_event &grafeex::messaging::print_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_print(*this);
	return *this;
}

grafeex::messaging::print_event::hdc_type grafeex::messaging::print_event::device(){
	return object_->info().wparam<hdc_type>();
}

grafeex::messaging::print_event::rect_type grafeex::messaging::print_event::clip_rect(){
	return wrappers::hdc(device()).clip_rect();
}

grafeex::messaging::print_event::option grafeex::messaging::print_event::options() const{
	return static_cast<option>(object_->info().lparam<unsigned int>());
}

bool grafeex::messaging::print_event::erase_background() const{
	return GRAFEEX_IS(options(), option::erase_background);
}

void grafeex::messaging::print_event::create_render_holder_(){
	if (render_holder_ == nullptr){
		render_holder_ = std::make_shared<render_holder_type>(object_->target()->hdc_render_manager());
		render_holder_->renderer()->BindDC(device(), clip_rect());
	}
}

void grafeex::messaging::print_event::on_error_(hresult_type err){
	object_->target()->on_drawing_error(err, true);
	if (err == D2DERR_RECREATE_TARGET)
		object_->target()->on_recreate_drawing_resources(true);
}
