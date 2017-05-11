#include "thread_modal_loop.h"
#include "../window/modal_dialog_window.h"

grafeex::threading::modal_loop::modal_loop()
	: modal_dialog_(nullptr), previous_pump_(nullptr){}

grafeex::threading::modal_loop::modal_loop(modal_dialog_type &modal_dialog)
	: modal_dialog_(nullptr), previous_pump_(nullptr){
	run(modal_dialog);
}

grafeex::threading::modal_loop::~modal_loop(){
	application::object::pump = previous_pump_;
	previous_pump_ = nullptr;
	queue_.wake_wait();//Release message loop
}

int grafeex::threading::modal_loop::run(modal_dialog_type &modal_dialog){
	modal_dialog_ = &modal_dialog;
	previous_pump_ = application::object::pump;

	if (id_ != application::object::instance->id_){
		application::object::instance->execute<void>([this]{
			id_ = application::object::instance->id_;//Use app thread id
			application::object::pump = this;
			object::run();
		});
	}
	else{//Same thread as app
		application::object::pump = this;
		object::run();
	}

	return status_.return_value;
}

bool grafeex::threading::modal_loop::is_filtered_message_() const{
	return application::object::instance->is_filtered_message_();
}

void grafeex::threading::modal_loop::translate_() const{
	application::object::instance->translate_();
}

void grafeex::threading::modal_loop::dispatch_(){
	if (!application::object::instance->window_manager_.modal_consume(cache_, *modal_dialog_)){
		if (!application::object::instance->is_dialog_message_())
			object::dispatch_();
	}
}

bool grafeex::threading::modal_loop::on_idle_(int index){
	return application::object::instance->on_idle_(index);
}

bool grafeex::threading::modal_loop::is_stopped_() const{
	return (previous_pump_ == nullptr);
}
