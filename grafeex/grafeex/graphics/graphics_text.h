#pragma once

#ifndef GRAFEEX_GRAPHICS_TEXT_H
#define GRAFEEX_GRAPHICS_TEXT_H

#include <string>
#include <climits>
#include <memory>

#include "../structures/rect_structure.h"
#include "../d2d/d2d_write_factory.h"

namespace grafeex{
	namespace graphics{
		class text{
		public:
			typedef ::BOOL bool_type;
			typedef ::UINT32 uint32_type;
			typedef ::HFONT font_type;
			typedef ::LOGFONTW font_info_type;

			typedef ::DWRITE_TEXT_METRICS text_metrics_type;
			typedef ::DWRITE_FONT_METRICS font_metrics_type;

			typedef ::DWRITE_FONT_WEIGHT font_weigth_type;
			typedef ::DWRITE_FONT_STYLE font_style_type;
			typedef ::DWRITE_FONT_STRETCH font_stretch_type;

			typedef ::Microsoft::WRL::ComPtr<::IDWriteTextFormat> format_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteTextLayout> layout_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteGdiInterop> gdi_interop_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteFont> d2d_font_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteFontFamily> font_family_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteFontCollection> font_collection_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteLocalizedStrings> localized_strings_type;

			typedef structures::float_size size_type;
			typedef size_type::field_type size_field_type;

			static size_type size(const wchar_t *value, uint32_type size, d2d_font_type::InterfaceType &font, float font_size, const wchar_t *locale = nullptr);

			static size_type size(const wchar_t *value, uint32_type size, const wchar_t *font_family, d2d_font_type::InterfaceType &font,
				float font_size, const wchar_t *locale = nullptr);

			static font_collection_type get_system_font_collection(bool check_for_update = false);

			static font_family_type find_font_family(const wchar_t *family, bool use_default = false);

			static font_family_type find_font_family(font_collection_type::InterfaceType &collection, const wchar_t *family,
				bool use_default = false);

			static d2d_font_type find_first_font(font_family_type::InterfaceType &family, font_weigth_type weight = font_weigth_type::DWRITE_FONT_WEIGHT_NORMAL,
				font_style_type style = font_style_type::DWRITE_FONT_STYLE_NORMAL, font_stretch_type stretch = font_stretch_type::DWRITE_FONT_STRETCH_NORMAL);

			static d2d_font_type get_default_font(const wchar_t *family, bool use_default = false);

			static bool font_to_font_info(d2d_font_type::InterfaceType &font, font_info_type &info, bool *is_system = nullptr);

			static d2d_font_type font_info_to_font(const font_info_type &info);

			static bool get_font_family_name(font_family_type::InterfaceType &family, wchar_t *buffer, const wchar_t *locale = nullptr);

			static font_collection_type system_font_collection;
		};
	}
}

#endif /* !GRAFEEX_GRAPHICS_TEXT_H */
