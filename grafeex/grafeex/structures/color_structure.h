#pragma once

#ifndef GRAFEEX_COLOR_STRUCTURE_H
#define GRAFEEX_COLOR_STRUCTURE_H

#include "../common/preprocessor.h"
#include "../common/windows_headers.h"
#include "../wrappers/scalar_wrapper.h"

namespace grafeex{
	namespace structures{
		class color : public wrappers::scalar<::COLORREF, color>{
		public:
			typedef wrappers::scalar<::COLORREF, color> base_type;
			typedef ::BYTE field_type;

			enum class named_type : value_type{
				alice_blue					= RGB(0xf0, 0xf8, 0xff),
				antique_white				= RGB(0xfa, 0xeb, 0xd7),
				aqua						= RGB(0x00, 0xff, 0xff),
				aquamarine					= RGB(0x7f, 0xff, 0xd4),
				azure						= RGB(0xf0, 0xff, 0xff),
				beige						= RGB(0xf5, 0xf5, 0xdc),
				bisque						= RGB(0xff, 0xe4, 0xce),
				black						= RGB(0x00, 0x00, 0x00),
				blanched_almond				= RGB(0xff, 0xeb, 0xcd),
				blue						= RGB(0x00, 0x00, 0xff),
				blue_violet					= RGB(0x8a, 0x2b, 0xe2),
				brown						= RGB(0xa5, 0x2a, 0x2a),
				burly_wood					= RGB(0xde, 0xb8, 0x87),
				cadet_blue					= RGB(0x5f, 0x9e, 0xa0),
				chartreuse					= RGB(0x7f, 0xff, 0x00),
				chocolate					= RGB(0xd2, 0x69, 0x1e),
				coral						= RGB(0xff, 0x7f, 0x50),
				cornflower_blue				= RGB(0x64, 0x95, 0xed),
				cornsilk					= RGB(0xff, 0xf8, 0xdc),
				crimson						= RGB(0xdc, 0x14, 0x3c),
				cyan						= RGB(0x00, 0xff, 0xff),
				dark_blue					= RGB(0x00, 0x00, 0x8b),
				dark_cyan					= RGB(0x00, 0x8b, 0x8b),
				dark_goldenrod				= RGB(0xb8, 0x86, 0x0b),
				dark_gray					= RGB(0xa9, 0xa9, 0xa9),
				dark_green					= RGB(0x00, 0x64, 0x00),
				dark_grey					= RGB(0xa9, 0xa9, 0xa9),
				dark_khaki					= RGB(0xbd, 0xb7, 0x6b),
				dark_magenta				= RGB(0x8b, 0x00, 0x8b),
				dark_olive_green			= RGB(0x55, 0x6b, 0x2f),
				dark_orange					= RGB(0xff, 0x8c, 0x00),
				dark_orchid					= RGB(0x99, 0x32, 0xcc),
				dark_red					= RGB(0x8b, 0x00, 0x00),
				dark_salmon					= RGB(0xe9, 0x97, 0x6a),
				dark_sea_green				= RGB(0x8f, 0xbc, 0x8f),
				dark_slate_blue				= RGB(0x48, 0x3d, 0x8b),
				dark_slate_gray				= RGB(0x2f, 0x4f, 0x4f),
				dark_slate_grey				= RGB(0x2f, 0x4f, 0x4f),
				dark_turquoise				= RGB(0x00, 0xce, 0xd1),
				dark_violet					= RGB(0x94, 0x00, 0xd3),
				deep_pink					= RGB(0xff, 0x14, 0x93),
				deep_sky_blue				= RGB(0x00, 0xbf, 0xff),
				dim_gray					= RGB(0x69, 0x69, 0x69),
				dim_grey					= RGB(0x69, 0x69, 0x69),
				dodger_blue					= RGB(0x1e, 0x90, 0xff),
				firebrick					= RGB(0xb2, 0x22, 0x22),
				floral_white				= RGB(0xff, 0xfa, 0xf0),
				forest_green				= RGB(0x22, 0x8b, 0x22),
				fuchsia						= RGB(0xff, 0x00, 0xff),
				gainsboro					= RGB(0xdc, 0xdc, 0xdc),
				ghost_white					= RGB(0xf8, 0xf8, 0xff),
				gold						= RGB(0xff, 0xd7, 0x00),
				goldenrod					= RGB(0xda, 0xa5, 0x20),
				gray						= RGB(0x80, 0x80, 0x80),
				green						= RGB(0x00, 0x80, 0x00),
				green_yellow				= RGB(0xad, 0xff, 0x2f),
				grey						= RGB(0x80, 0x80, 0x80),
				honeydew					= RGB(0xf0, 0xff, 0xf0),
				hot_pink					= RGB(0xff, 0x69, 0xb4),
				indian_red					= RGB(0xcd, 0x5c, 0x5c),
				indigo						= RGB(0x4b, 0x00, 0x82),
				ivory						= RGB(0xff, 0xff, 0xf0),
				khaki						= RGB(0xf0, 0xe6, 0x8c),
				lavendar					= RGB(0xe6, 0xe6, 0xfa),
				lavender_blush				= RGB(0xff, 0xf0, 0xf5),
				lawn_green					= RGB(0x7c, 0xfc, 0x00),
				lemon_chiffon				= RGB(0xff, 0xfa, 0xcd),
				light_blue					= RGB(0xad, 0xd8, 0xe6),
				light_coral					= RGB(0xf0, 0x80, 0x80),
				light_cyan					= RGB(0xe0, 0xff, 0xff),
				light_goldenrod_yellow		= RGB(0xfa, 0xfa, 0xd2),
				light_gray					= RGB(0xd3, 0xd3, 0xd3),
				light_green					= RGB(0x90, 0xee, 0x90),
				light_grey					= RGB(0xd3, 0xd3, 0xd3),
				light_pink					= RGB(0xff, 0xb6, 0xc1),
				light_salmon				= RGB(0xff, 0xa0, 0x7a),
				light_sea_green				= RGB(0x20, 0xb2, 0xaa),
				light_sky_blue				= RGB(0x87, 0xce, 0xfa),
				light_slate_gray			= RGB(0x77, 0x88, 0x99),
				light_slate_grey			= RGB(0x77, 0x88, 0x99),
				light_steel_blue			= RGB(0xb0, 0xc4, 0xde),
				light_yellow				= RGB(0xff, 0xff, 0xe0),
				lime						= RGB(0x00, 0xff, 0x00),
				lime_green					= RGB(0x32, 0xcd, 0x32),
				linen						= RGB(0xfa, 0xf0, 0xe6),
				magenta						= RGB(0xff, 0x00, 0xff),
				maroon						= RGB(0x80, 0x00, 0x00),
				medium_aquamarine			= RGB(0x66, 0xcd, 0xaa),
				medium_blue					= RGB(0x00, 0x00, 0xcd),
				medium_orchid				= RGB(0xba, 0x55, 0xd3),
				medium_purple				= RGB(0x93, 0x70, 0xdb),
				medium_sea_green			= RGB(0x3c, 0xb3, 0x71),
				medium_slate_blue			= RGB(0x7b, 0x68, 0xee),
				medium_spring_green			= RGB(0x00, 0xfa, 0x9a),
				medium_turquoise			= RGB(0x48, 0xd1, 0xcc),
				medium_violet_red			= RGB(0xc7, 0x15, 0x85),
				midnight_blue				= RGB(0x19, 0x19, 0x70),
				mint_cream					= RGB(0xf5, 0xff, 0xfa),
				misty_rose					= RGB(0xff, 0xe4, 0xe1),
				moccasin					= RGB(0xff, 0xe4, 0xb5),
				navajo_white				= RGB(0xff, 0xde, 0xad),
				navy						= RGB(0x00, 0x00, 0x80),
				old_lace					= RGB(0xfd, 0xf5, 0xe6),
				olive						= RGB(0x80, 0x80, 0x00),
				olive_drab					= RGB(0x6b, 0x8e, 0x23),
				orange						= RGB(0xff, 0xa5, 0x00),
				orange_red					= RGB(0xff, 0x45, 0x00),
				orchid						= RGB(0xda, 0x70, 0xd6),
				pale_goldenrod				= RGB(0xee, 0xe8, 0xaa),
				pale_green					= RGB(0x98, 0xfb, 0x98),
				pale_turquoise				= RGB(0xaf, 0xee, 0xee),
				pale_violet_red				= RGB(0xdb, 0x70, 0x93),
				papaya_whip					= RGB(0xff, 0xef, 0xd5),
				peach_puff					= RGB(0xff, 0xda, 0xb9),
				peru						= RGB(0xcd, 0x85, 0x3f),
				pink						= RGB(0xff, 0xc0, 0xcb),
				plum						= RGB(0xdd, 0xa0, 0xdd),
				powder_blue					= RGB(0xb0, 0xe0, 0xe6),
				purple						= RGB(0x80, 0x00, 0x80),
				red							= RGB(0xff, 0x00, 0x00),
				rosy_brown					= RGB(0xbc, 0x8f, 0x8f),
				royal_blue					= RGB(0x41, 0x69, 0xe1),
				saddle_brown				= RGB(0x8b, 0x45, 0x13),
				salmon						= RGB(0xfa, 0x80, 0x72),
				sandy_brown					= RGB(0xf4, 0xa4, 0x60),
				sea_green					= RGB(0x2e, 0x8b, 0x57),
				sea_shell					= RGB(0xff, 0xf5, 0xee),
				sienna						= RGB(0xa0, 0x52, 0x2d),
				silver						= RGB(0xc0, 0xc0, 0xc0),
				sky_blue					= RGB(0x87, 0xce, 0xeb),
				slate_blue					= RGB(0x6a, 0x5a, 0xcd),
				slate_gray					= RGB(0x70, 0x80, 0x90),
				slate_grey					= RGB(0x70, 0x80, 0x90),
				snow						= RGB(0xff, 0xfa, 0xfa),
				spring_green				= RGB(0x00, 0xff, 0x7f),
				steel_blue					= RGB(0x46, 0x82, 0xb4),
				tan							= RGB(0xd2, 0xb4, 0x8c),
				teal						= RGB(0x00, 0x80, 0x80),
				thistle						= RGB(0xd8, 0xbf, 0xd8),
				tomato						= RGB(0xff, 0x63, 0x47),
				turquoise					= RGB(0x40, 0xe0, 0xd0),
				violet						= RGB(0xee, 0x82, 0xee),
				wheat						= RGB(0xf5, 0xde, 0xb3),
				white						= RGB(0xff, 0xff, 0xff),
				white_smoke					= RGB(0xf5, 0xf5, 0xf5),
				yellow						= RGB(0xff, 0xff, 0x00),
				yellow_green				= RGB(0x9a, 0xcd, 0x32),
				button_face_shadow_start	= RGB(0xf5, 0xf4, 0xf2),
				button_face_shadow_end		= RGB(0xd5, 0xd2, 0xca),
				button_face					= RGB(0xd4, 0xd0, 0xc8),
				dark_border					= RGB(0x40, 0x40, 0x40),
				gray_border					= RGB(0x80, 0x80, 0x80),
				highlight					= RGB(0x1c, 0xc4, 0xf7),
			};

			enum class alpha_type : field_type{
				opaque				= 0xff,
				translucent			= 0x7a,
				transparent			= 0x00,
			};

			color();

			color(value_type value);

			color(value_type rgb, field_type alpha);

			color(value_type rgb, alpha_type alpha);

			color(field_type red, field_type green, field_type blue, field_type alpha = 255);

			color(field_type red, field_type green, field_type blue, alpha_type alpha);

			color(float red, float green, float blue, float alpha);

			color(float red, float green, float blue, alpha_type alpha);

			color(named_type name, field_type alpha = 255);

			color(named_type name, alpha_type alpha);

			bool operator ==(named_type rhs) const;

			bool operator !=(named_type rhs) const;

			friend bool operator ==(named_type lhs, const color &rhs);

			friend bool operator !=(named_type lhs, const color &rhs);

			color &red(field_type value);

			color &red(float value);

			field_type red() const;

			float relative_red() const;

			color &green(field_type value);

			color &green(float value);

			field_type green() const;

			float relative_green() const;

			color &blue(field_type value);

			color &blue(float value);

			field_type blue() const;

			float relative_blue() const;

			color &alpha(field_type value, bool multiply = false);

			color &alpha(float value, bool multiply = false);

			color &alpha(alpha_type value, bool multiply = false);

			field_type alpha() const;

			float relative_alpha() const;

			color &name(named_type value);

			named_type name() const;

			color &rgb(value_type value);

			color &rgb(field_type red, field_type green, field_type blue);

			value_type rgb() const;

			value_type bgr() const;

			color &rgba(value_type value);

			color &rgba(field_type red, field_type green, field_type blue, field_type alpha);

			color &rgba(field_type red, field_type green, field_type blue, alpha_type alpha);

			value_type rgba() const;

			bool is_transparent() const;

			bool is_opaque() const;

			bool is_named_alpha() const;

			color &make_different(const color &target);

			color &make_different(const color &first, const color &second);

			color get_different(const color &target) const;

			color get_different(const color &first, const color &second) const;

		private:
			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_COLOR_STRUCTURE_H */
