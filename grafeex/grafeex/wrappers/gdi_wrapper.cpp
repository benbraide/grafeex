#include "gdi_wrapper.h"
#include "../gdi/gdi_manager.h"

grafeex::wrappers::gdi::gdi(value_type value)
	: base_type(value){}

grafeex::wrappers::gdi::object_type grafeex::wrappers::gdi::type() const{
	return static_cast<object_type>(::GetObjectType(value_));
}

grafeex::wrappers::gdi::gdi_object_type *grafeex::wrappers::gdi::owner() const{
	return grafeex::gdi::manager::owner(value_);
}
