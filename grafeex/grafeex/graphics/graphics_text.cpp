#include "graphics_text.h"
#include "../application/application_object.h"

grafeex::graphics::text::size_type grafeex::graphics::text::size(const wchar_t *value, uint32_type size,
	d2d_font_type::InterfaceType &font, float font_size, const wchar_t *locale){
	static wchar_t font_family[LF_FACESIZE];

	font_family_type family;
	if (FAILED(font.GetFontFamily(family.GetAddressOf())))
		return size_type{};

	if (!get_font_family_name(*family.Get(), font_family, locale))
		return size_type{};

	return text::size(value, size, font_family, font, font_size, locale);
}

grafeex::graphics::text::size_type grafeex::graphics::text::size(const wchar_t *value, uint32_type size, const wchar_t *font_family,
	d2d_font_type::InterfaceType &font, float font_size, const wchar_t *locale){
	static wchar_t locale_buffer[LOCALE_NAME_MAX_LENGTH];

	const wchar_t *target_locale;
	if (locale == nullptr){//Use default locale
		auto locale_size = ::GetUserDefaultLocaleName(locale_buffer, LOCALE_NAME_MAX_LENGTH);
		if (locale_size > 0)
			target_locale = locale_buffer;
		else//Use US-English
			target_locale = L"en-us";
	}
	else//Use locale
		target_locale = locale;

	format_type format;
	if (FAILED(application::object::d2d_write_factory->CreateTextFormat(
		font_family,
		nullptr,
		font.GetWeight(),
		font.GetStyle(),
		font.GetStretch(),
		font_size,
		target_locale,
		format.GetAddressOf()
	))){
		return size_type{};
	}

	layout_type layout;
	if (FAILED(application::object::d2d_write_factory->CreateTextLayout(
		value,
		size,
		format.Get(),
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max(),
		layout.GetAddressOf()
	))){
		return size_type{};
	}

	text_metrics_type metrics;
	if (FAILED(layout->GetMetrics(&metrics)))
		return size_type{};

	return size_type{ metrics.width, metrics.height };
}

grafeex::graphics::text::font_collection_type grafeex::graphics::text::get_system_font_collection(bool check_for_update){
	font_collection_type collection;
	if (FAILED(application::object::d2d_write_factory->GetSystemFontCollection(collection.GetAddressOf(), check_for_update ? TRUE : FALSE)))
		return nullptr;

	return collection;
}

grafeex::graphics::text::font_family_type grafeex::graphics::text::find_font_family(const wchar_t *family, bool use_default){
	if (system_font_collection == nullptr){
		auto font_collection = get_system_font_collection();
		if (font_collection != nullptr)
			return find_font_family(*font_collection.Get(), family, use_default);
		return nullptr;
	}

	return find_font_family(*system_font_collection.Get(), family, use_default);
}

grafeex::graphics::text::font_family_type grafeex::graphics::text::find_font_family(font_collection_type::InterfaceType &collection,
	const wchar_t *family, bool use_default){
	uint32_type index = 0;
	bool_type exists = FALSE;

	if (FAILED(collection.FindFamilyName(family, &index, &exists)))
		return nullptr;

	if (exists == FALSE){//Use default, if applicable
		if (!use_default)
			return nullptr;

		index = 0u;
	}

	font_family_type font_family;
	if (FAILED(collection.GetFontFamily(index, font_family.GetAddressOf())))
		return nullptr;

	return font_family;
}

grafeex::graphics::text::d2d_font_type grafeex::graphics::text::find_first_font(font_family_type::InterfaceType &family, font_weigth_type weight,
	font_style_type style, font_stretch_type stretch){
	d2d_font_type font;
	if (FAILED(family.GetFirstMatchingFont(weight, stretch, style, font.GetAddressOf())))
		return nullptr;
	return font;
}

grafeex::graphics::text::d2d_font_type grafeex::graphics::text::get_default_font(const wchar_t *family, bool use_default){
	auto font_family = find_font_family(family, use_default);
	return (font_family == nullptr) ? nullptr : find_first_font(*font_family.Get());
}

grafeex::graphics::text::font_collection_type grafeex::graphics::text::system_font_collection = get_system_font_collection();

bool grafeex::graphics::text::font_to_font_info(d2d_font_type::InterfaceType &font, font_info_type &info, bool *is_system){
	gdi_interop_type interop;
	if (FAILED(application::object::d2d_write_factory->GetGdiInterop(interop.GetAddressOf())))
		return false;

	bool_type is_system_font = FALSE;
	if (FAILED(interop->ConvertFontToLOGFONT(&font, &info, &is_system_font)))
		return false;

	if (is_system != nullptr)//Update
		*is_system = (is_system_font != FALSE);

	return true;
}

grafeex::graphics::text::d2d_font_type grafeex::graphics::text::font_info_to_font(const font_info_type &info){
	gdi_interop_type interop;
	if (FAILED(application::object::d2d_write_factory->GetGdiInterop(interop.GetAddressOf())))
		return nullptr;

	d2d_font_type font;
	if (FAILED(interop->CreateFontFromLOGFONT(&info, font.GetAddressOf())))
		return false;

	return font;
}

bool grafeex::graphics::text::get_font_family_name(font_family_type::InterfaceType &family, wchar_t *buffer, const wchar_t *locale){
	localized_strings_type font_family_names;
	if (FAILED(family.GetFamilyNames(font_family_names.GetAddressOf())))
		return false;

	uint32_type index = 0;
	bool_type exists = FALSE;

	if (locale == nullptr){//Use default locale
		auto locale_buffer = std::make_unique<wchar_t[]>(LOCALE_NAME_MAX_LENGTH);
		auto locale_size = ::GetUserDefaultLocaleName(locale_buffer.get(), LOCALE_NAME_MAX_LENGTH);
		if (locale_size > 0)
			font_family_names->FindLocaleName(locale_buffer.get(), &index, &exists);
		else//Use US-English
			font_family_names->FindLocaleName(L"en-us", &index, &exists);
	}
	else//Use locale
		font_family_names->FindLocaleName(locale, &index, &exists);

	uint32_type font_family_name_size = 0;
	if (FAILED(font_family_names->GetStringLength(exists ? index : 0u, &font_family_name_size)))
		return false;

	if (FAILED(font_family_names->GetString(exists ? index : 0u, buffer, font_family_name_size + 1)))
		return false;

	return true;
}
