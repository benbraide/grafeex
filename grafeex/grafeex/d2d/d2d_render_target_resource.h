#pragma once

#ifndef GRAFEEX_D2D_RENDER_TARGET_RESOURCE_H
#define GRAFEEX_D2D_RENDER_TARGET_RESOURCE_H

#include "../structures/color_structure.h"
#include "d2d_factory.h"

namespace grafeex{
	namespace d2d{
		template <class target_interface_type>
		class render_target_resource{
		public:
			typedef target_interface_type target_interface_type;

			typedef ::D2D1_COLOR_F color_type;
			typedef structures::color gdi_color_type;

			typedef ::Microsoft::WRL::ComPtr<::ID2D1SolidColorBrush> solid_brush_type;
			typedef ::Microsoft::WRL::ComPtr<::ID2D1LinearGradientBrush> linear_gradient_brush_type;
			typedef ::Microsoft::WRL::ComPtr<::ID2D1RadialGradientBrush> radial_gradient_brush_type;

			explicit render_target_resource(target_interface_type *&target_interface)
				: target_interface_(target_interface){}

			~render_target_resource(){}

			solid_brush_type::InterfaceType &solid_brush(const color_type &color){
				if (!solid_brush_.valid())
					target_interface_->CreateSolidColorBrush(color, solid_brush_.GetAddressOf());
				else//Update color
					solid_brush_->SetColor(color);

				return *solid_brush_.Get();
			}

			solid_brush_type::InterfaceType &solid_brush(const gdi_color_type &color){
				return solid_brush(::D2D1::ColorF(color.relative_red(), color.relative_green(), color.relative_blue(), color.relative_alpha()));
			}

			solid_brush_type::InterfaceType &solid_brush(){
				if (!solid_brush_.valid())
					target_interface_->CreateSolidColorBrush(::D2D1::ColorF(0.0f, 0.0f, 0.0f), solid_brush_.GetAddressOf());
				return *solid_brush_.Get();
			}

			linear_gradient_brush_type::InterfaceType &linear_gradient_brush(){
				return *linear_gradient_brush_.Get();
			}

			radial_gradient_brush_type::InterfaceType &radial_gradient_brush(){
				return *radial_brush_brush_.Get();
			}

		private:
			target_interface_type *&target_interface_;
			solid_brush_type solid_brush_;
			linear_gradient_brush_type linear_gradient_brush_;
			radial_gradient_brush_type radial_brush_brush_;
		};
	}
}

#endif /* !GRAFEEX_D2D_RENDER_TARGET_RESOURCE_H */
