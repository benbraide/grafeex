#pragma once

#ifndef GRAFEEX_HDC_WRAPPER_H
#define GRAFEEX_HDC_WRAPPER_H

#include <string>
#include <memory>

#include "../structures/enumerations.h"
#include "../structures/ref_rect_structure.h"
#include "../structures/color_structure.h"

namespace grafeex{
	namespace wrappers{
		class hdc : public wrappers::pointer<::HDC, hdc>{
		public:
			typedef ::HGDIOBJ gdi_object_type;
			typedef ::TEXTMETRICW text_metric_type;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::rect rect_type;
			typedef structures::color color_type;

			typedef wrappers::pointer<::HDC, hdc> base_type;

			hdc(value_type value = nullptr);

			hdc(const hdc &) = default;

			hdc &operator =(const hdc &) = default;

			std::wstring font_face() const;

			bool text_metrics(text_metric_type &info);

			gdi_object_type select(gdi_object_type object);

			rect_type clip_rect() const;
		};
	}
}

#endif /* !GRAFEEX_HDC_WRAPPER_H */
