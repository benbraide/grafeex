#include "thread_object.h"

grafeex::threading::object::object()
	: id_(get_current_id()), status_(status_info{}), modal_(nullptr){
	status_.is_posted = false;
}

grafeex::threading::object::~object(){}

int grafeex::threading::object::run(){
	if (get_current_id() != id_)
		return -1;//Different threads - reject

	auto idle_index = 0;
	while (!is_stopped_()){
		scheduler_.execute_all();//Execute pending tasks
		if (queue_.peek(cache_, message_queue::peek_type::remove)){//Not idle
			if (!cache_.is_quit()){//Forward message
				status_.is_posted = true;
				if (cache_.owner() == nullptr)//Thread message
					dispatch_thread_message_();
				else if (!is_filtered_message_())
					dispatch_();

				idle_index = 0;//Reset idle index
			}
			else{//Quit received
				status_.return_value = cache_.wparam<int>();
				break;
			}
		}
		else if (!on_idle_(idle_index++))//No more idle tasks -- wait for event
			queue_.wait();
	}

	return status_.return_value;
}

bool grafeex::threading::object::wake_wait(){
	return (modal_ == nullptr) ? queue_.wake_wait() : modal_->queue_.wake_wait();
}

const grafeex::threading::id &grafeex::threading::object::get_id() const{
	return id_;
}

bool grafeex::threading::object::is_sent_() const{
	return (modal_ == nullptr) ? !status_.is_posted : !modal_->status_.is_posted;
}

bool grafeex::threading::object::is_filtered_message_() const{
	return false;
}

void grafeex::threading::object::translate_() const{
	if (modal_ == nullptr)
		cache_.translate();
	else
		modal_->cache_.translate();
}

void grafeex::threading::object::dispatch_(){
	translate_();
	if (modal_ == nullptr)
		cache_.dispatch();
	else
		modal_->cache_.dispatch();
}

void grafeex::threading::object::dispatch_thread_message_(){
	translate_();
	if (modal_ == nullptr)
		cache_.dispatch();
	else
		modal_->cache_.dispatch();
}

bool grafeex::threading::object::on_idle_(int index){
	return false;
}

bool grafeex::threading::object::is_stopped_() const{
	return false;
}
