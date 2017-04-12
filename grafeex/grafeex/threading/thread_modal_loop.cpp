#include "thread_modal_loop.h"
#include "../window/modal_dialog_window.h"

grafeex::threading::modal_loop::modal_loop(modal_dialog_type &modal_dialog)
	: modal_dialog_(&modal_dialog), previous_modal_(nullptr), running_(false){}

grafeex::threading::modal_loop::~modal_loop(){
	stop();
}

int grafeex::threading::modal_loop::run(){
	return application::object::instance->execute<int>([this]{
		id_ = application::object::instance->id_;
		previous_modal_ = application::object::instance->modal_;

		application::object::instance->modal_ = this;
		running_ = true;

		return object::run();
	});
}

void grafeex::threading::modal_loop::stop(){
	running_ = false;
	application::object::instance->modal_ = previous_modal_;
	previous_modal_ = nullptr;
}

bool grafeex::threading::modal_loop::consume(window_type &target, uint_type msg, wparam_type wparam, lparam_type lparam){
	if (modal_dialog_ == nullptr || &target == modal_dialog_ || target.is_ancestor(*modal_dialog_))
		return false;//Not consumed

	auto i = 0;
	switch (msg){
	case WM_NCLBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN://Flash dialog
		i += 0;
		break;
	case WM_ACTIVATE:
	case WM_SETFOCUS:
	case WM_KILLFOCUS:
	case WM_NCLBUTTONUP:
	case WM_NCMBUTTONUP:
	case WM_NCRBUTTONUP:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCMBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_NCMOUSEMOVE:
	case WM_MOUSEMOVE:
	case WM_NCMOUSELEAVE:
	case WM_MOUSELEAVE:
	case WM_NCMOUSEHOVER:
	case WM_MOUSEHOVER:
		break;
	default:
		return false;
	}

	return true;//Consumed
}

bool grafeex::threading::modal_loop::is_filtered_message_() const{
	return application::object::instance->is_filtered_message_();
}

void grafeex::threading::modal_loop::translate_() const{
	application::object::instance->translate_();
}

void grafeex::threading::modal_loop::dispatch_(){
	application::object::instance->dispatch_();
}

void grafeex::threading::modal_loop::dispatch_thread_message_(){
	application::object::instance->dispatch_thread_message_();
}

bool grafeex::threading::modal_loop::on_idle_(int index){
	return application::object::instance->on_idle_(index);
}

bool grafeex::threading::modal_loop::is_stopped_() const{
	return !running_;
}
