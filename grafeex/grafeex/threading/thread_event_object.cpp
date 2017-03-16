#include "thread_event_object.h"

grafeex::threading::event_object::event_object()
	: base_type(nullptr){}

grafeex::threading::event_object::event_object(const std::wstring &name)
	: base_type(nullptr){
	create_(name, false);
}

grafeex::threading::event_object::event_object(event_object &&target)
	: base_type(target.value_){
	target.value_ = nullptr;
}

grafeex::threading::event_object::~event_object(){
	destroy();
}

grafeex::threading::event_object &grafeex::threading::event_object::operator =(event_object &&target){
	value_ = target.value_;
	target.value_ = nullptr;
	return *this;
}

bool grafeex::threading::event_object::create(const std::wstring &name){
	return create_(name, false);
}

bool grafeex::threading::event_object::destroy(){
	if (value_ != nullptr && ::CloseHandle(value_) != FALSE)
		value_ = nullptr;

	return (value_ == nullptr);
}

bool grafeex::threading::event_object::reset(){
	return (value_ != nullptr && ::ResetEvent(value_) != FALSE);
}

bool grafeex::threading::event_object::set(){
	return (value_ != nullptr && ::SetEvent(value_) != FALSE);
}

bool grafeex::threading::event_object::is_created() const{
	return (value_ != nullptr);
}

const grafeex::threading::event_object::value_type &grafeex::threading::event_object::get_value_ref() const{
	return value_;
}

bool grafeex::threading::event_object::create_(const std::wstring &name, bool manual){
	if (value_ != nullptr)
		return false;

	return ((value_ = ::CreateEventW(nullptr, FALSE, FALSE, name.c_str())) != nullptr);
}

grafeex::threading::manual_event_object::manual_event_object(){}

grafeex::threading::manual_event_object::manual_event_object(const std::wstring &name){
	create_(name, true);
}

grafeex::threading::manual_event_object::~manual_event_object(){}

bool grafeex::threading::manual_event_object::create(const std::wstring &name){
	return create_(name, true);
}
