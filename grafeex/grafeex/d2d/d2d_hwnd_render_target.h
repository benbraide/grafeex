#pragma once

#ifndef GRAFEEX_D2D_HWND_RENDER_TARGET_H
#define GRAFEEX_D2D_HWND_RENDER_TARGET_H

#include "../wrappers/hwnd_wrapper.h"
#include "../structures/color_structure.h"

#include "d2d_factory.h"

namespace grafeex{
	namespace d2d{
		class hwnd_render_target : public ::Microsoft::WRL::ComPtr<::ID2D1HwndRenderTarget>{
		public:
			typedef factory::interface_type factory_type;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type hwnd_value_type;
			typedef wrappers::hwnd::size_type size_type;

			typedef ::D2D1_SIZE_F relative_size_type;
			typedef ::D2D1_COLOR_F color_type;

			typedef structures::color gdi_color_type;

			typedef ::Microsoft::WRL::ComPtr<::ID2D1SolidColorBrush> solid_brush_type;
			typedef ::Microsoft::WRL::ComPtr<::ID2D1HwndRenderTarget> base_type;

			typedef solid_brush_type::InterfaceType brush_interface_type;
			typedef base_type::InterfaceType interface_type;

			hwnd_render_target();

			hwnd_render_target(factory_type &factory, hwnd_value_type target, bool is_relative = false);

			hwnd_render_target(factory_type &factory, hwnd_value_type target, const relative_size_type &size);

			hwnd_render_target(factory_type &factory, hwnd_value_type target, const size_type &size);

			~hwnd_render_target();

			hwnd_render_target *self();

			bool create(factory_type &factory, hwnd_value_type target, bool is_relative = false);

			bool create(factory_type &factory, hwnd_value_type target, const relative_size_type &size);

			bool create(factory_type &factory, hwnd_value_type target, const size_type &size);

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

#endif /* !GRAFEEX_D2D_HWND_RENDER_TARGET_H */
