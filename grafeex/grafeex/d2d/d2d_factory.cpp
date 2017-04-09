#include "d2d_factory.h"

grafeex::d2d::factory::factory(bool multi_threaded){
	if (FAILED(::D2D1CreateFactory(multi_threaded ? ::D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED :
		::D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &ptr_))){
		ptr_ = nullptr;
	}
}

grafeex::d2d::factory::~factory(){}

grafeex::d2d::factory::operator interface_type &() const{
	return *ptr_;
}
