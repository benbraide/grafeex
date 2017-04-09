#include "d2d_hwnd_render_target.h"

grafeex::d2d::hwnd_render_target::hwnd_render_target(){}

grafeex::d2d::hwnd_render_target::hwnd_render_target(factory_type &factory, hwnd_value_type target){
	create(factory, target);
}

grafeex::d2d::hwnd_render_target::hwnd_render_target(factory_type &factory, hwnd_value_type target, const size_type &size){
	create(factory, target, size);
}

grafeex::d2d::hwnd_render_target::~hwnd_render_target(){}

bool grafeex::d2d::hwnd_render_target::create(factory_type &factory, hwnd_value_type target){
	return create(factory, target, hwnd_type(target).get_client_rect().size());
}

bool grafeex::d2d::hwnd_render_target::create(factory_type &factory, hwnd_value_type target, const size_type &size){
	auto result = factory.CreateHwndRenderTarget(
		::D2D1::RenderTargetProperties(),
		::D2D1::HwndRenderTargetProperties(target, ::D2D1::SizeU(size.width(), size.height())),
		&ptr_
	);

	if (FAILED(result)){
		ptr_ = nullptr;
		return false;
	}

	return true;
}
