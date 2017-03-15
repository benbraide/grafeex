#pragma once

#ifndef GRAFEEX_POINT_STRUCTURE_H
#define GRAFEEX_POINT_STRUCTURE_H

#include "../common/windows_headers.h"
#include "../wrappers/value_wrapper.h"

namespace grafeex{
	namespace structures{
		template <class value_type>
		struct point_native_value{
			value_type x;
			value_type y;
		};

		template <class value_type, class field_type>
		class basic_point : public wrappers::value<value_type, basic_point<value_type, field_type> >{
		public:
			typedef field_type field_type;
			typedef wrappers::value<value_type, basic_point<value_type, field_type> > base_type;

			basic_point()
				: base_type(value_type{}){}

			basic_point(field_type x, field_type y)
				: base_type(value_type{ x, y }){}

			explicit basic_point(field_type xy)
				: base_type(value_type{ xy, xy }){}

			basic_point(const value_type &value)
				: base_type(value){}

			basic_point(const basic_point &value)
				: base_type(value.value_){}

			basic_point(basic_point &&value)
				: base_type(value.value_){
				value.value_ = {};
			}

			basic_point &operator =(const value_type &value){
				base_type::value_ = value;
				return *this;
			}

			basic_point &operator =(const basic_point &value){
				base_type::value_ = value.value_;
				return *this;
			}

			basic_point &operator =(basic_point &&value){
				base_type::value_ = value.value_;
				value.value_ = {};
				return *this;
			}

			basic_point operator +() const{
				return *this;
			}

			basic_point operator -() const{
				return basic_point{ -base_type::value_.x, -base_type::value_.y };
			}

			basic_point operator +(const basic_point &rhs) const{
				return basic_point{ base_type::value_.x + rhs.value_.x, base_type::value_.y + rhs.value_.y };
			}

			basic_point operator -(const basic_point &rhs) const{
				return basic_point{ base_type::value_.x - rhs.value_.x, base_type::value_.y - rhs.value_.y };
			}

			basic_point &operator +=(const basic_point &rhs){
				return (*this = *this + rhs);
			}

			basic_point &operator -=(const basic_point &rhs){
				return (*this = *this - rhs);
			}

			basic_point &set(field_type xy){
				base_type::value_.x = base_type::value_.y = xy;
				return *this;
			}

			basic_point &set(field_type x, field_type y){
				base_type::value_.x = x;
				base_type::value_.y = y;
				return *this;
			}

			basic_point &set_x(field_type value){
				base_type::value_.x = value;
				return *this;
			}

			basic_point &set_y(field_type value){
				base_type::value_.y = value;
				return *this;
			}

			const value_type &get() const{
				return base_type::value_;
			}

			field_type get_x() const{
				return base_type::value_.x;
			}

			field_type get_y() const{
				return base_type::value_.y;
			}

			static int compare(const value_type &lhs, const value_type &rhs){
				return (lhs.x == rhs.x && lhs.y == rhs.y) ? 0 : -1;
			}
		};

		typedef basic_point<::POINT, ::LONG> point;
		typedef basic_point<point_native_value<short>, short> short_point;
		typedef basic_point<point_native_value<float>, float> float_point;
	}
}

#endif /* !GRAFEEX_POINT_STRUCTURE_H */
