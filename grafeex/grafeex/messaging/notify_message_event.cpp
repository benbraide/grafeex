#include "notify_message_event.h"
#include "message_event_forwarder.h"

#include "../controls/control_object.h"

grafeex::messaging::notify_event::notify_event(object &value)
	: message_event(value){}

grafeex::messaging::notify_event::~notify_event() = default;

grafeex::messaging::message_event &grafeex::messaging::notify_event::dispatch(){
	auto cmd_list = control()->notify_forwarder_list_ref_;
	if (cmd_list != nullptr){
		auto message_dispatcher = cmd_list->find(code());
		if (message_dispatcher != cmd_list->end()){
			message_dispatcher->second->dispatch(*object_);
			return *this;
		}
	}

	return dispatch_();
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

grafeex::messaging::message_event &grafeex::messaging::notify_event::dispatch_(){
	auto target = control();
	if (target == nullptr)//Unknown target
		return *this;

	target->on_event(*this);
	if (is_propagating())
		target->on_notify(*this);

	return *this;
}

grafeex::messaging::custom_draw_event::custom_draw_event(object &value)
	: notify_event(value){}

grafeex::messaging::custom_draw_event::~custom_draw_event(){
	end_drawing();
}

grafeex::messaging::message_event &grafeex::messaging::custom_draw_event::dispatch(){
	if (dispatch_().is_propagating())
		*this << dynamic_cast<window::controls::object *>(control())->on_control_draw(*this);
	return *this;
}

grafeex::messaging::custom_draw_event::hdc_type grafeex::messaging::custom_draw_event::device() const{
	return draw_info().hdc;
}

grafeex::messaging::custom_draw_event::rect_type grafeex::messaging::custom_draw_event::clip_rect() const{
	return draw_info().rc;
}

grafeex::messaging::custom_draw_event::dword_type grafeex::messaging::custom_draw_event::stage() const{
	return draw_info().dwDrawStage;
}

grafeex::messaging::custom_draw_event::dword_ptr_type grafeex::messaging::custom_draw_event::spec() const{
	return draw_info().dwItemSpec;
}

grafeex::messaging::notify_event::uint_type grafeex::messaging::custom_draw_event::state() const{
	return draw_info().uItemState;
}

grafeex::messaging::custom_draw_event::draw_info_type &grafeex::messaging::custom_draw_event::draw_info() const{
	return *object_->info().lparam<draw_info_type *>();
}

void grafeex::messaging::custom_draw_event::create_render_holder_(){
	if (render_holder_ == nullptr){
		render_holder_ = std::make_shared<render_holder_type>(object_->target()->hdc_render_manager());
		render_holder_->renderer()->BindDC(device(), clip_rect());
	}
}

void grafeex::messaging::custom_draw_event::on_error_(hresult_type err){
	object_->target()->on_drawing_error(err, true);
	if (err == D2DERR_RECREATE_TARGET)
		object_->target()->on_recreate_drawing_resources(true);
}
