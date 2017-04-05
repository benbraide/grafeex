#pragma once

#ifndef GRAFEEX_GDI_WRAPPER_H
#define GRAFEEX_GDI_WRAPPER_H

#include "../common/windows_headers.h"
#include "pointer_wrapper.h"

namespace grafeex{
	namespace gdi{
		class object;
	}

	namespace wrappers{
		class gdi : public wrappers::pointer<::HGDIOBJ, gdi>{
		public:
			typedef ::UINT uint_type;

			typedef grafeex::gdi::object gdi_object_type;
			typedef wrappers::pointer<::HGDIOBJ, gdi> base_type;

			enum class object_type : uint_type{
				nil					= 0,
				pen					= OBJ_PEN,
				brush				= OBJ_BRUSH,
				font				= OBJ_FONT,
				bitmap				= OBJ_BITMAP,
				rgn					= OBJ_REGION,
				palette				= OBJ_PAL,
				dc					= OBJ_DC,
				mem_dc				= OBJ_MEMDC,
				meta_dc				= OBJ_METADC,
				meta_file			= OBJ_METAFILE,
				ext_pen				= OBJ_EXTPEN,
				enhanced_meta_dc	= OBJ_ENHMETADC,
				enhanced_meta_file	= OBJ_ENHMETAFILE,
				color_space			= OBJ_COLORSPACE,
			};

			gdi(value_type value = nullptr);

			gdi(const gdi &) = default;

			gdi &operator =(const gdi &) = default;

			virtual object_type type() const;

			virtual gdi_object_type *owner() const;
		};
	}
}

#endif /* !GRAFEEX_GDI_WRAPPER_H */
