#pragma once

#ifndef GRAFEEX_SIZE_STRUCTURE_H
#define GRAFEEX_SIZE_STRUCTURE_H

#include "../common/windows_headers.h"
#include "../wrappers/value_wrapper.h"

namespace grafeex{
	namespace structures{
		template <class value_type>
		struct size_native_value{
			value_type cx;
			value_type cy;
		};

		template <class value_type, class field_type>
		class basic_size : public wrappers::value<value_type, basic_size<value_type, field_type> >{
		public:
			typedef field_type field_type;
			typedef wrappers::value<value_type, basic_size<value_type, field_type> > base_type;

			basic_size()
				: base_type(value_type{}){}

			basic_size(field_type x, field_type y)
				: base_type(value_type{ x, y }){}

			explicit basic_size(field_type xy)
				: base_type(value_type{ xy, xy }){}

			basic_size(const value_type &value)
				: base_type(value){}

			basic_size(const basic_size &value)
				: base_type(value.value_){}

			basic_size(basic_size &&value)
				: base_type(value.value_){
				value.value_ = {};
			}

			basic_size &operator =(const value_type &value){
				base_type::value_ = value;
				return *this;
			}

			basic_size &operator =(const basic_size &value){
				base_type::value_ = value.value_;
				return *this;
			}

			basic_size &operator =(basic_size &&value){
				base_type::value_ = value.value_;
				value.value_ = {};
				return *this;
			}

			basic_size operator +() const{
				return *this;
			}

			basic_size operator -() const{
				return basic_size{ -base_type::value_.cx, -base_type::value_.cy };
			}

			basic_size operator +(const basic_size &rhs) const{
				return basic_size{ base_type::value_.cx + rhs.value_.cx, base_type::value_.cy + rhs.value_.cy };
			}

			basic_size operator -(const basic_size &rhs) const{
				return basic_size{ base_type::value_.cx - rhs.value_.cx, base_type::value_.cy - rhs.value_.cy };
			}

			basic_size operator *(field_type multiplier) const{
				return basic_size{ base_type::value_.cx * multiplier, base_type::value_.cy * multiplier };
			}

			basic_size &operator +=(const basic_size &rhs){
				return (*this = *this + rhs);
			}

			basic_size &operator -=(const basic_size &rhs){
				return (*this = *this - rhs);
			}

			basic_size &operator *=(field_type multiplier){
				return (*this = *this * multiplier);
			}

			basic_size &set(field_type xy){
				base_type::value_.cx = base_type::value_.cy = xy;
				return *this;
			}

			basic_size &set(field_type x, field_type y){
				base_type::value_.cx = x;
				base_type::value_.cy = y;
				return *this;
			}

			basic_size &width(field_type value){
				base_type::value_.cx = value;
				return *this;
			}

			basic_size &height(field_type value){
				base_type::value_.cy = value;
				return *this;
			}

			const value_type &get() const{
				return base_type::value_;
			}

			field_type width() const{
				return base_type::value_.cx;
			}

			field_type height() const{
				return base_type::value_.cy;
			}

			static int compare(const value_type &lhs, const value_type &rhs){
				return (lhs.cx == rhs.cx && lhs.cy == rhs.cy) ? 0 : -1;
			}
		};

		typedef basic_size<::SIZE, ::LONG> size;
		typedef basic_size<size_native_value<short>, short> short_size;
		typedef basic_size<size_native_value<float>, float> float_size;
	}
}

#endif /* !GRAFEEX_SIZE_STRUCTURE_H */
