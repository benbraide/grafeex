#include "gdi_object.h"
#include "../application/application_object.h"

grafeex::gdi::object::~object() = default;

void grafeex::gdi::object::init_(){
	if (application::object::instance->gdi_manager_is_enabled()){
		gdi::manager::guard_type guard(gdi::manager::lock_);
		gdi::manager::owner_cache_[operator value_type()] = this;
	}
}

void grafeex::gdi::object::uninit_(){
	if (application::object::instance->gdi_manager_is_enabled()){
		gdi::manager::guard_type guard(gdi::manager::lock_);
		gdi::manager::owner_cache_.erase(operator value_type());
	}
}
