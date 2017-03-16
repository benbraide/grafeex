#include "thread_id.h"

grafeex::threading::id::id()
	: value_(0){}

grafeex::threading::id::id(value_type value)
	: value_(value){}

grafeex::threading::id::operator value_type() const{
	return value_;
}

bool grafeex::threading::id::operator <(const id &rhs) const{
	return (value_ < rhs.value_);
}

bool grafeex::threading::id::operator <=(const id &rhs) const{
	return (value_ <= rhs.value_);
}

bool grafeex::threading::id::operator ==(const id &rhs) const{
	return (value_ == rhs.value_);
}

bool grafeex::threading::id::operator !=(const id &rhs) const{
	return (value_ != rhs.value_);
}

bool grafeex::threading::id::operator >=(const id &rhs) const{
	return (value_ >= rhs.value_);
}

bool grafeex::threading::id::operator >(const id &rhs) const{
	return (value_ > rhs.value_);
}

grafeex::threading::id grafeex::threading::get_current_id(){
	return id(::GetCurrentThreadId());
}
