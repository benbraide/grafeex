#pragma once

#ifndef GRAFEEX_STOCK_GDI_OBJECT_H
#define GRAFEEX_STOCK_GDI_OBJECT_H

#include "shared_gdi_object.h"

namespace grafeex{
	namespace gdi{
		class stock_object{
		public:
			enum class index{
				black_brush				= BLACK_BRUSH,
				dark_gray_brush			= DKGRAY_BRUSH,
				dark_grey_brush			= DKGRAY_BRUSH,
				dc_brush				= DC_BRUSH,
				gray_brush				= GRAY_BRUSH,
				grey_brush				= GRAY_BRUSH,
				hollow_brush			= HOLLOW_BRUSH,
				light_gray_brush		= LTGRAY_BRUSH,
				light_grey_brush		= LTGRAY_BRUSH,
				null_brush				= NULL_BRUSH,
				white_brush				= WHITE_BRUSH,
				black_pen				= BLACK_PEN,
				dc_pen					= DC_PEN,
				null_pen				= NULL_PEN,
				white_pen				= WHITE_PEN,
				ansi_fixed_font			= ANSI_FIXED_FONT,
				ansi_variable_font		= ANSI_VAR_FONT,
				device_default_font		= DEVICE_DEFAULT_FONT,
				default_gui_font		= DEFAULT_GUI_FONT,
				oem_fixed_font			= OEM_FIXED_FONT,
				system_font				= SYSTEM_FONT,
				system_fixed_font		= SYSTEM_FIXED_FONT,
			};

			static shared_object get(int index);

			static shared_object get(index index);
		};
	}
}

#endif /* !GRAFEEX_STOCK_GDI_OBJECT_H */
