#include "shared_gdi_object.h"

grafeex::gdi::shared_object::shared_object(value_type value)
	: value_(value){}

grafeex::gdi::shared_object::~shared_object() = default;

grafeex::gdi::shared_object &grafeex::gdi::shared_object::operator =(value_type value){
	value_ = value;
	return *this;
}

grafeex::gdi::shared_object::operator value_type() const{
	return value_;
}

grafeex::gdi::shared_object::operator wrapper_type() const{
	return value_;
}

bool grafeex::gdi::shared_object::operator==(std::nullptr_t rhs) const{
	return (value_ == rhs);
}

bool grafeex::gdi::shared_object::operator!=(std::nullptr_t rhs) const{
	return (value_ != rhs);
}

bool grafeex::gdi::operator==(std::nullptr_t lhs, const shared_object &rhs){
	return (rhs == lhs);
}

bool grafeex::gdi::operator!=(std::nullptr_t lhs, const shared_object &rhs){
	return (rhs != lhs);
}

grafeex::gdi::object::object_type grafeex::gdi::shared_object::type() const{
	return value_.type();
}

grafeex::gdi::object *grafeex::gdi::shared_object::owner() const{
	return value_.owner();
}
