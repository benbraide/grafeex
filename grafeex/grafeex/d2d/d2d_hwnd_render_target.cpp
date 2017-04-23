#include "d2d_hwnd_render_target.h"
#include "../window/window_object.h"

grafeex::d2d::hwnd_render_target::hwnd_render_target(){}

grafeex::d2d::hwnd_render_target::hwnd_render_target(factory_type &factory, hwnd_value_type target, bool is_relative){
	create(factory, target, is_relative);
}

grafeex::d2d::hwnd_render_target::hwnd_render_target(factory_type &factory, hwnd_value_type target, const relative_size_type &size){
	create(factory, target, size);
}

grafeex::d2d::hwnd_render_target::hwnd_render_target(factory_type &factory, hwnd_value_type target, const size_type &size){
	create(factory, target, size);
}

grafeex::d2d::hwnd_render_target::~hwnd_render_target() = default;

grafeex::d2d::hwnd_render_target *grafeex::d2d::hwnd_render_target::self(){
	return this;
}

bool grafeex::d2d::hwnd_render_target::create(factory_type &factory, hwnd_value_type target, bool is_relative){
	auto size = hwnd_type(target).get_client_rect().size();
	if (is_relative)
		return create(factory, target, relative_size_type{ static_cast<float>(size.width()),static_cast<float>(size.height()) });
	return create(factory, target, size);
}

bool grafeex::d2d::hwnd_render_target::create(factory_type &factory, hwnd_value_type target, const relative_size_type &size){
	typedef ::UINT32 uint_type;
	auto result = factory.CreateHwndRenderTarget(
		::D2D1::RenderTargetProperties(),
		::D2D1::HwndRenderTargetProperties(target, ::D2D1::SizeU()),
		&ptr_
	);

	if (SUCCEEDED(result)){
		ptr_->SetDpi(96.0f, 96.0f);
		if (FAILED(ptr_->Resize(::D2D1::SizeU(static_cast<uint_type>(size.width), static_cast<uint_type>(size.height))))){
			ptr_->Release();
			ptr_ = nullptr;
		}
	}
	else//Failed
		ptr_ = nullptr;

	return (ptr_ != nullptr);
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

void grafeex::d2d::hwnd_render_target::set_background_color(const color_type &value){
	if (background_brush_ == nullptr)
		ptr_->CreateSolidColorBrush(value, background_brush_.GetAddressOf());
	else//Update color
		background_brush_->SetColor(value);
}

void grafeex::d2d::hwnd_render_target::set_background_color(const gdi_color_type &value){
	set_background_color(::D2D1::ColorF(value.relative_red(), value.relative_green(), value.relative_blue(), value.relative_alpha()));
}

grafeex::d2d::hwnd_render_target::brush_interface_type &grafeex::d2d::hwnd_render_target::background_brush(const color_type &color){
	set_background_color(color);
	return *background_brush_.Get();
}

grafeex::d2d::hwnd_render_target::brush_interface_type &grafeex::d2d::hwnd_render_target::background_brush(const gdi_color_type &color){
	return background_brush(::D2D1::ColorF(color.relative_red(), color.relative_green(), color.relative_blue(), color.relative_alpha()));
}

grafeex::d2d::hwnd_render_target::brush_interface_type &grafeex::d2d::hwnd_render_target::background_brush(){
	return (background_brush_ == nullptr) ? background_brush(::D2D1::ColorF(0.0f, 0.0f, 0.0f)) : *background_brush_.Get();
}
