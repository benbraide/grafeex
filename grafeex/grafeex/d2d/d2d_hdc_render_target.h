#pragma once

#ifndef GRAFEEX_D2D_HDC_RENDER_TARGET_H
#define GRAFEEX_D2D_HDC_RENDER_TARGET_H

#include "../wrappers/hdc_wrapper.h"
#include "../structures/color_structure.h"

#include "d2d_factory.h"

namespace grafeex{
	namespace d2d{
		class hdc_render_target : public ::Microsoft::WRL::ComPtr<::ID2D1DCRenderTarget>{
		public:
			typedef factory::interface_type factory_type;

			typedef wrappers::hdc hdc_type;
			typedef wrappers::hdc::value_type hdc_value_type;
			typedef wrappers::hdc::size_type size_type;

			typedef ::D2D1_SIZE_F relative_size_type;
			typedef ::D2D1_COLOR_F color_type;

			typedef structures::color gdi_color_type;

			typedef ::Microsoft::WRL::ComPtr<::ID2D1SolidColorBrush> solid_brush_type;
			typedef ::Microsoft::WRL::ComPtr<::ID2D1DCRenderTarget> base_type;

			typedef solid_brush_type::InterfaceType brush_interface_type;
			typedef base_type::InterfaceType interface_type;

			hdc_render_target();

			explicit hdc_render_target(factory_type &factory);

			~hdc_render_target();

			hdc_render_target *self();

			bool create(factory_type &factory);

			void set_background_color(const color_type &value);

			void set_background_color(const gdi_color_type &value);

			brush_interface_type &background_brush(const color_type &color);

			brush_interface_type &background_brush(const gdi_color_type &color);

			brush_interface_type &background_brush();

		protected:
			solid_brush_type background_brush_;
		};
	}
}

#endif /* !GRAFEEX_D2D_HDC_RENDER_TARGET_H */
