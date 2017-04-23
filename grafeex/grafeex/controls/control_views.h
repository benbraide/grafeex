#pragma once

#ifndef GRAFEEX_CONTROL_VIEWS_H
#define GRAFEEX_CONTROL_VIEWS_H

#include "../window/window_view.h"
#include "../wrappers/hwnd_wrapper.h"
#include "../gdi/stock_gdi_object.h"
#include "../gdi/gdi_client_dc.h"
#include "../d2d/d2d_write_factory.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class view : public window::view{
			public:
				typedef ::HFONT font_type;
				typedef ::LOGFONTW font_info_type;
				typedef ::TEXTMETRIC text_metric_type;

				typedef ::DWRITE_FONT_WEIGHT font_weigth_type;
				typedef ::DWRITE_FONT_STYLE font_style_type;
				typedef ::DWRITE_FONT_STRETCH font_stretch_type;

				typedef window::view base_type;
				typedef window::object object_type;

				typedef wrappers::hwnd hwnd_type;
				typedef gdi::client_dc dc_type;

				explicit view(object_type &object);

				virtual ~view();

				virtual view &font(const wchar_t *family, font_weigth_type weight = font_weigth_type::DWRITE_FONT_WEIGHT_NORMAL, long size = -12);

				virtual view &font(font_type value);

				virtual font_type font() const;
			};
		}
	}
}

#endif /* !GRAFEEX_CONTROL_VIEWS_H */
