#include "d2d_factory.h"

grafeex::d2d::factory::factory(bool multi_threaded){
	if (FAILED(::D2D1CreateFactory(multi_threaded ? ::D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED :
		::D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &interface_))){
		interface_ = nullptr;
	}
}

grafeex::d2d::factory::~factory(){}
