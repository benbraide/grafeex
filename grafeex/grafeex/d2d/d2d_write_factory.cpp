#include "d2d_write_factory.h"

grafeex::d2d::write_factory::write_factory(bool multi_threaded){
	if (FAILED(::DWriteCreateFactory(multi_threaded ? ::DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED :
		::DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(interface_type), reinterpret_cast<unknown_type **>(&ptr_)))){
		ptr_ = nullptr;
	}
}

grafeex::d2d::write_factory::~write_factory() = default;

grafeex::d2d::write_factory::operator interface_type &() const{
	return *ptr_;
}
