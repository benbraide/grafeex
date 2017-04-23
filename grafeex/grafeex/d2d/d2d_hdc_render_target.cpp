#include "d2d_hdc_render_target.h"
#include "../window/window_object.h"

grafeex::d2d::hdc_render_target::hdc_render_target(){}

grafeex::d2d::hdc_render_target::hdc_render_target(factory_type &factory){
	create(factory);
}

grafeex::d2d::hdc_render_target::~hdc_render_target() = default;

grafeex::d2d::hdc_render_target *grafeex::d2d::hdc_render_target::self(){
	return this;
}

bool grafeex::d2d::hdc_render_target::create(factory_type &factory){
	auto props = ::D2D1::RenderTargetProperties(
		::D2D1_RENDER_TARGET_TYPE::D2D1_RENDER_TARGET_TYPE_DEFAULT,
		::D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		)
	);

	auto result = factory.CreateDCRenderTarget(&props, &ptr_);
	if (FAILED(result))
		ptr_ = nullptr;

	return (ptr_ != nullptr);
}

void grafeex::d2d::hdc_render_target::set_background_color(const color_type &value){
	if (background_brush_ == nullptr)
		ptr_->CreateSolidColorBrush(value, background_brush_.GetAddressOf());
	else//Update color
		background_brush_->SetColor(value);
}

void grafeex::d2d::hdc_render_target::set_background_color(const gdi_color_type &value){
	set_background_color(::D2D1::ColorF(value.relative_red(), value.relative_green(), value.relative_blue(), value.relative_alpha()));
}

grafeex::d2d::hdc_render_target::brush_interface_type &grafeex::d2d::hdc_render_target::background_brush(const color_type &color){
	set_background_color(color);
	return *background_brush_.Get();
}

grafeex::d2d::hdc_render_target::brush_interface_type &grafeex::d2d::hdc_render_target::background_brush(const gdi_color_type &color){
	return background_brush(::D2D1::ColorF(color.relative_red(), color.relative_green(), color.relative_blue(), color.relative_alpha()));
}

grafeex::d2d::hdc_render_target::brush_interface_type &grafeex::d2d::hdc_render_target::background_brush(){
	return (background_brush_ == nullptr) ? background_brush(::D2D1::ColorF(0.0f, 0.0f, 0.0f)) : *background_brush_.Get();
}
