#include "message_object.h"

grafeex::messaging::object::object(const msg &info, bool is_sent, procedure_type default_callback)
	: msg_(info), states_(is_sent ? state::sent : state::nil), default_callback_(default_callback), value_(0){
	if (thread_queue::is_sent())
		GRAFEEX_SET(states_, state::sent | state::cross);

	if (default_callback_ == nullptr)
		GRAFEEX_SET(states_, state::skipped);
}

grafeex::messaging::object::~object(){}

grafeex::messaging::object &grafeex::messaging::object::modify(const msg &value){
	GRAFEEX_SET(states_, state::modified);
	msg_ = value;
	return *this;
}

grafeex::messaging::object &grafeex::messaging::object::handle(handle_type type){
	if (!GRAFEEX_IS_ANY(states_, state::done | state::skipped)){
		GRAFEEX_SET(states_, state::done);
		if (default_callback_ != nullptr){
			if (GRAFEEX_IS(type, handle_type::overwrite) || (GRAFEEX_IS(type, handle_type::write) && !GRAFEEX_IS(states_, state::has_value))){
				GRAFEEX_SET(states_, state::has_value);
				value_ = ::CallWindowProcW(default_callback_, msg_.owner(), msg_.code(), msg_.wparam(), msg_.lparam());
			}
			else//Ignore return
				::CallWindowProcW(default_callback_, msg_.owner(), msg_.code(), msg_.wparam(), msg_.lparam());
		}
	}

	return *this;
}

grafeex::messaging::object &grafeex::messaging::object::skip(){
	if (!GRAFEEX_IS_ANY(states_, state::done | state::skipped))
		GRAFEEX_SET(states_, state::skipped);
	return *this;
}

grafeex::messaging::object &grafeex::messaging::object::reply(bool value){
	return reply(value ? TRUE : FALSE);
}

grafeex::messaging::object &grafeex::messaging::object::reply(){
	return GRAFEEX_IS(states_, state::has_value) ? reply(value_) : *this;
}

grafeex::messaging::object &grafeex::messaging::object::operator =(bool value){
	return operator =(value ? TRUE : FALSE);
}

grafeex::messaging::object &grafeex::messaging::object::operator <<(bool value){
	return operator <<(value ? TRUE : FALSE);
}

bool grafeex::messaging::object::is_sent() const{
	return GRAFEEX_IS(states_, state::sent);
}

bool grafeex::messaging::object::is_cross_thread() const{
	return GRAFEEX_IS(states_, state::cross);
}

bool grafeex::messaging::object::is_replied() const{
	return GRAFEEX_IS(states_, state::replied);
}

bool grafeex::messaging::object::has_value() const{
	return GRAFEEX_IS(states_, state::has_value);
}

bool grafeex::messaging::object::is_default() const{
	return GRAFEEX_IS(states_, state::done);
}

bool grafeex::messaging::object::is_skipped() const{
	return GRAFEEX_IS(states_, state::skipped);
}

bool grafeex::messaging::object::is_handled() const{
	return GRAFEEX_IS_ANY(states_, state::skipped | state::done | state::replied | state::has_value);
}

bool grafeex::messaging::object::is_modified() const{
	return GRAFEEX_IS(states_, state::modified);
}

const grafeex::messaging::msg &grafeex::messaging::object::info() const{
	return msg_;
}

grafeex::messaging::object::result_type grafeex::messaging::object::value() const{
	return value_;
}
