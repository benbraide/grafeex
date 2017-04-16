#pragma once

#ifndef GRAFEEX_GDI_BRUSH_H
#define GRAFEEX_GDI_BRUSH_H

#include "../wrappers/pointer_wrapper.h"
#include "../structures/color_structure.h"

#include "gdi_object.h"

namespace grafeex{
	namespace gdi{
		enum class brush_style : ::UINT{
			nil				= BS_NULL,
			solid			= BS_SOLID,
			hatched			= BS_HATCHED,
			pattern			= BS_PATTERN,
			dib_pattern		= BS_DIBPATTERN,
		};

		enum class brush_hatch : ::ULONG_PTR{
			horizontal				= HS_HORIZONTAL,
			vertical				= HS_VERTICAL,
			cross					= HS_CROSS,
			diagonal_cross			= HS_DIAGCROSS,
			forward_diagonal		= HS_FDIAGONAL,
			backward_diagonal		= HS_BDIAGONAL,
		};

		class brush_common : public wrappers::pointer<::HBRUSH, brush_common>, public object{
		public:
			typedef ::LOGBRUSH info_type;
			typedef ::UINT uint_type;
			typedef ::ULONG_PTR ulong_ptr_type;

			typedef object::value_type value_type;
			typedef object::object_type object_type;

			typedef wrappers::pointer<::HBRUSH, brush_common> base_type;
			typedef structures::color color_type;

			brush_common();

			explicit brush_common(const info_type &info);

			brush_common(const brush_common &target);

			virtual ~brush_common();

			brush_common &operator =(const brush_common &target);

			virtual operator value_type() const override;

			virtual operator wrapper_type() const override;

			virtual object_type type() const override;

			virtual bool create();

			virtual bool create(const info_type &info);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual brush_common &style(brush_style value);

			virtual brush_style style() const;

			virtual brush_common &hatch(brush_hatch value);

			virtual brush_hatch hatch() const;

			virtual brush_common &color(const color_type &value);

			virtual const color_type &color() const;

			virtual const info_type &info() const;

		protected:
			virtual void recreate_();

			virtual void retrieve_info_();

			info_type info_{};
			color_type color_;
		};

		template <brush_style style>
		class basic_brush : public brush_common{
		public:
			basic_brush(){}

			explicit basic_brush(const color_type &color){
				create(color);
			}

			basic_brush(const basic_brush &target)
				: brush_common(target){}

			virtual ~basic_brush() = default;

			basic_brush &operator =(const basic_brush &target){
				brush_common::operator=(target);
				return *this;
			}

			virtual bool create(const color_type &color){
				if (is_created())
					return false;

				info_.lbColor = (color_ = color).rgb();
				info_.lbStyle = static_cast<uint_type>(style);

				return brush_common::create();
			}

			static const brush_style style = style;
		};

		template <>
		class basic_brush<brush_style::hatched> : public brush_common{
		public:
			basic_brush(){}

			basic_brush(brush_hatch hatch, const color_type &color){
				create(hatch, color);
			}

			basic_brush(const basic_brush &target)
				: brush_common(target){}

			virtual ~basic_brush() = default;

			basic_brush &operator =(const basic_brush &target){
				brush_common::operator=(target);
				return *this;
			}

			virtual bool create(brush_hatch hatch, const color_type &color){
				if (is_created())
					return false;

				info_.lbColor = (color_ = color).rgb();
				info_.lbStyle = static_cast<uint_type>(style);
				info_.lbHatch = static_cast<ulong_ptr_type>(hatch);

				return brush_common::create();
			}

			static const brush_style style = brush_style::hatched;
		};

		template <>
		class basic_brush<brush_style::pattern> : public brush_common{
		public:
			typedef ::HBITMAP bitmap_type;

			basic_brush(){}

			explicit basic_brush(bitmap_type bitmap){
				create(bitmap);
			}

			basic_brush(const basic_brush &target)
				: brush_common(target){}

			virtual ~basic_brush() = default;

			basic_brush &operator =(const basic_brush &target){
				brush_common::operator=(target);
				return *this;
			}

			virtual bool create(bitmap_type bitmap){
				if (is_created())
					return false;

				info_.lbStyle = static_cast<uint_type>(style);
				info_.lbHatch = reinterpret_cast<ulong_ptr_type>(bitmap);

				return brush_common::create();
			}

			virtual basic_brush &bitmap(bitmap_type value){
				info_.lbHatch = reinterpret_cast<ulong_ptr_type>(value);
				if (is_created())//Update
					recreate_();

				return *this;
			}

			virtual bitmap_type bitmap() const{
				return reinterpret_cast<bitmap_type>(info_.lbHatch);
			}

			static const brush_style style = brush_style::pattern;
		};

		typedef basic_brush<brush_style::nil> null_brush;
		typedef basic_brush<brush_style::solid> solid_brush;
		typedef basic_brush<brush_style::hatched> hatched_brush;
		typedef basic_brush<brush_style::pattern> pattern_brush;
		typedef basic_brush<brush_style::dib_pattern> dib_pattern_brush;
	}
}

#endif /* !GRAFEEX_GDI_BRUSH_H */
