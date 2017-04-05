#pragma once

#ifndef GRAFEEX_D2D_HWND_RENDER_TARGET_H
#define GRAFEEX_D2D_HWND_RENDER_TARGET_H

#include "../wrappers/hwnd_wrapper.h"
#include "d2d_render_target_resource.h"

namespace grafeex{
	namespace d2d{
		class hwnd_render_target : public common::com_ptr<::ID2D1HwndRenderTarget>, public render_target_resource<::ID2D1HwndRenderTarget>{
		public:
			typedef factory::interface_type factory_type;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type hwnd_value_type;
			typedef wrappers::hwnd::size_type size_type;

			typedef common::com_ptr<::ID2D1HwndRenderTarget> base_type;
			typedef render_target_resource<::ID2D1HwndRenderTarget> resource_type;

			hwnd_render_target();

			hwnd_render_target(factory_type &factory, hwnd_value_type target);

			hwnd_render_target(factory_type &factory, hwnd_value_type target, const size_type &size);

			~hwnd_render_target();

			bool create(factory_type &factory, hwnd_value_type target);

			bool create(factory_type &factory, hwnd_value_type target, const size_type &size);
		};
	}
}

#endif /* !GRAFEEX_D2D_HWND_RENDER_TARGET_H */
