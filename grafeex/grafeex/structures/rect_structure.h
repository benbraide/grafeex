#pragma once

#ifndef GRAFEEX_RECT_STRUCTURE_H
#define GRAFEEX_RECT_STRUCTURE_H

#include "../common/preprocessor.h"

#include "point_structure.h"
#include "size_structure.h"

namespace grafeex{
	namespace structures{
		enum class rect_origin_type : unsigned int{
			nil						= (0 << 0x0000),
			left					= (0 << 0x0000),
			top						= (0 << 0x0000),
			right					= (1 << 0x0000),
			bottom					= (1 << 0x0001),
			center					= (1 << 0x0002),
			vertical_center			= (1 << 0x0003),
		};

		template <class value_type>
		struct rect_native_value{
			value_type left;
			value_type top;
			value_type right;
			value_type bottom;
		};

		template <class point_type, class size_type, class value_type>
		class basic_rect : public wrappers::value<value_type, basic_rect<point_type, size_type, value_type> >{
		public:
			typedef point_type point_type;
			typedef size_type size_type;

			typedef typename point_type::field_type field_type;
			typedef rect_origin_type origin_type;

			typedef wrappers::value<value_type, basic_rect<point_type, size_type, value_type> > base_type;

			basic_rect()
				: base_type(value_type{}){}

			basic_rect(field_type left, field_type top, field_type right, field_type bottom)
				: base_type(value_type{ left, top, right, bottom }){}

			basic_rect(field_type left, field_type top_bottom, field_type right)
				: base_type(value_type{ left, top_bottom, right, top_bottom }){}

			basic_rect(field_type left_right, field_type top_bottom)
				: base_type(value_type{ left_right, top_bottom, left_right, top_bottom }){}

			explicit basic_rect(field_type value)
				: base_type(value_type{ value, value, value, value }){}

			basic_rect(const point_type &top_left, const point_type &bottom_right)
				: base_type(value_type{ top_left.x(), top_left.y(), bottom_right.x(), bottom_right.y() }){}

			basic_rect(const point_type &top_left, const size_type &size, origin_type origin = origin_type::nil)
				: base_type(value_type{ top_left.x(), top_left.y(), top_left.x() + size.width(),
					top_left.y() + size.height() }){
				align_(origin);
			}

			basic_rect(const value_type &value)
				: base_type(value){}

			basic_rect(const basic_rect &value)
				: base_type(value.value_){}

			basic_rect(basic_rect &&value)
				: base_type(value.value_){
				value.value_ = {};
			}

			basic_rect &operator =(const value_type &value){
				base_type::value_ = value;
				return *this;
			}

			basic_rect &operator =(const basic_rect &value){
				base_type::value_ = value.value_;
				return *this;
			}

			basic_rect &operator =(basic_rect &&value){
				base_type::value_ = value.value_;
				value.value_ = {};
				return *this;
			}

			basic_rect operator +(const size_type &rhs) const{
				basic_rect copy(*this);
				return (copy += rhs);
			}

			basic_rect operator -(const size_type &rhs) const{
				basic_rect copy(*this);
				return (copy -= rhs);
			}

			basic_rect &operator +=(const size_type &rhs){
				return offset(rhs);
			}

			basic_rect &operator -=(const size_type &rhs){
				return offset(size_type{ -rhs.width(), -rhs.height() });
			}

			basic_rect &normalize(){
				if (base_type::value_.right < base_type::value_.left)
					std::swap(base_type::value_.left, base_type::value_.right);

				if (base_type::value_.bottom < base_type::value_.top)
					std::swap(base_type::value_.top, base_type::value_.bottom);

				return *this;
			}

			basic_rect &set(field_type left, field_type top, field_type right, field_type bottom){
				base_type::value_ = value_type{ left, top, right, bottom };
				return *this;
			}

			basic_rect &set(field_type left, field_type top_bottom, field_type right){
				base_type::value_ = value_type{ left, top_bottom, right, top_bottom };
				return *this;
			}

			basic_rect &set(field_type left_right, field_type top_bottom){
				base_type::value_ = value_type{ left_right, top_bottom, left_right, top_bottom };
				return *this;
			}

			basic_rect &set(field_type value){
				base_type::value_ = value_type{ value, value, value, value };
				return *this;
			}

			basic_rect &set(const point_type &top_left, const point_type &bottom_right){
				base_type::value_ = value_type{ top_left.x(), top_left.y(), bottom_right.x(), bottom_right.y() };
				return *this;
			}

			basic_rect &set(const point_type &top_left, const size_type &size, origin_type origin = origin_type::nil){
				base_type::value_ = value_type{ top_left.x(), top_left.y(), top_left.x() + size.width(),
					top_left.y() + size.height() };
				align_(origin);
				return *this;
			}

			basic_rect &left(field_type value){
				base_type::value_.left = value;
				return *this;
			}

			basic_rect &top(field_type value){
				base_type::value_.top = value;
				return *this;
			}

			basic_rect &right(field_type value){
				base_type::value_.right = value;
				return *this;
			}

			basic_rect &bottom(field_type value){
				base_type::value_.bottom = value;
				return *this;
			}

			basic_rect &top_left(const point_type &value){
				base_type::value_.left = value.x();
				base_type::value_.top = value.y();
				return *this;
			}

			basic_rect &top_right(const point_type &value){
				base_type::value_.right = value.x();
				base_type::value_.top = value.y();
				return *this;
			}

			basic_rect &bottom_right(const point_type &value){
				base_type::value_.right = value.x();
				base_type::value_.bottom = value.y();
				return *this;
			}

			basic_rect &bottom_left(const point_type &value){
				base_type::value_.left = value.x();
				base_type::value_.bottom = value.y();
				return *this;
			}

			basic_rect &inflate(const size_type &value){
				base_type::value_.left -= value.width();
				base_type::value_.top -= value.height();
				base_type::value_.right += value.width();
				base_type::value_.bottom += value.height();
				return *this;
			}

			basic_rect &inflate(const basic_rect &value){
				base_type::value_.left -= value.value_.left;
				base_type::value_.top -= value.value_.top;
				base_type::value_.right += value.value_.right;
				base_type::value_.bottom += value.value_.bottom;
				return *this;
			}

			basic_rect &deflate(const size_type &value){
				base_type::value_.left += value.width();
				base_type::value_.top += value.height();
				base_type::value_.right -= value.width();
				base_type::value_.bottom -= value.height();
				return *this;
			}

			basic_rect &deflate(const basic_rect &value){
				base_type::value_.left += value.value_.left;
				base_type::value_.top += value.value_.top;
				base_type::value_.right -= value.value_.right;
				base_type::value_.bottom -= value.value_.bottom;
				return *this;
			}

			basic_rect &offset(const size_type &value){
				base_type::value_.left += value.width();
				base_type::value_.top += value.height();
				base_type::value_.right += value.width();
				base_type::value_.bottom += value.height();
				return *this;
			}

			basic_rect &move_to(const point_type &value){
				return offset(value - top_left());
			}

			const value_type &get() const{
				return base_type::value_;
			}

			field_type left() const{
				return base_type::value_.left;
			}

			field_type top() const{
				return base_type::value_.top;
			}

			field_type right() const{
				return base_type::value_.right;
			}

			field_type bottom() const{
				return base_type::value_.bottom;
			}

			point_type top_left() const{
				return point_type{ base_type::value_.left, base_type::value_.top };
			}

			point_type top_right() const{
				return point_type{ base_type::value_.right, base_type::value_.top };
			}

			point_type bottom_right() const{
				return point_type{ base_type::value_.right, base_type::value_.bottom };
			}

			point_type bottom_left() const{
				return point_type{ base_type::value_.left, base_type::value_.bottom };
			}

			size_type size() const{
				return size_type{ base_type::value_.right - base_type::value_.left, base_type::value_.bottom - base_type::value_.top };
			}

			size_type sum() const{
				return size_type{ base_type::value_.right + base_type::value_.left, base_type::value_.bottom + base_type::value_.top };
			}

			basic_rect get_inflated(const size_type &value) const{
				basic_rect copy(*this);
				return copy.inflate(value);
			}

			basic_rect get_inflated(const basic_rect &value) const{
				basic_rect copy(*this);
				return copy.inflate(value);
			}

			basic_rect get_deflated(const size_type &value) const{
				basic_rect copy(*this);
				return copy.deflate(value);
			}

			basic_rect get_deflated(const basic_rect &value) const{
				basic_rect copy(*this);
				return copy.deflate(value);
			}

			basic_rect get_after_offset(const size_type &value) const{
				basic_rect copy(*this);
				return copy.offset(value);
			}

			basic_rect get_moved(const point_type &value) const{
				basic_rect copy(*this);
				return copy.move_to(value);
			}

			basic_rect get_intersection(const basic_rect &value) const{
				return basic_rect{
					(base_type::value_.left > value.value_.left) ? base_type::value_.left : value.value_.left,
					(base_type::value_.top > value.value_.top) ? base_type::value_.top : value.value_.top,
					(base_type::value_.right < value.value_.right) ? base_type::value_.right : value.value_.right,
					(base_type::value_.bottom < value.value_.bottom) ? base_type::value_.bottom : value.value_.bottom
				};
			}

			basic_rect get_union(const basic_rect &value) const{
				return basic_rect{
					(base_type::value_.left < value.value_.left) ? base_type::value_.left : value.value_.left,
					(base_type::value_.top < value.value_.top) ? base_type::value_.top : value.value_.top,
					(base_type::value_.right > value.value_.right) ? base_type::value_.right : value.value_.right,
					(base_type::value_.bottom > value.value_.bottom) ? base_type::value_.bottom : value.value_.bottom
				};
			}

			bool is_empty() const{
				return (base_type::value_.left >= base_type::value_.right || base_type::value_.top >= base_type::value_.bottom);
			}

			bool is_normalized() const{
				return (base_type::value_.left <= base_type::value_.right && base_type::value_.top <= base_type::value_.bottom);
			}

			bool intersects(const basic_rect &value) const{
				return (is_empty() || value.is_empty()) ? false : !get_intersection(value).is_empty();
			}

			bool contains(const basic_rect &value) const{
				if (is_empty() || value.is_empty())
					return false;

				return (value.value_.left >= base_type::value_.left && value.value_.top >= base_type::value_.top &&
					value.value_.right <= base_type::value_.right && value.value_.bottom <= base_type::value_.bottom);
			}

			bool contains(const point_type &value) const{
				return (value.x() >= base_type::value_.left && value.y() >= base_type::value_.top &&
					value.x() < base_type::value_.right && value.y() < base_type::value_.bottom);
			}

			static int compare(const value_type &lhs, const value_type &rhs){
				return (lhs.left == rhs.left && lhs.top == rhs.top && lhs.right == rhs.right && lhs.bottom == rhs.bottom) ? 0 : -1;
			}

			static basic_rect compute_circle_bounding_rect(const point_type &top_left, field_type radius, origin_type origin = origin_type::nil){
				return basic_rect(top_left, size_type{ radius * 2 }, origin);
			}

			template <typename list_type>
			static basic_rect compute_bounding_rect(const list_type &points, bool inclusive = true){
				if (points.empty())
					return basic_rect();

				auto iter = points.begin();
				value_type computed{ iter->x(), iter->y(), iter->x(), iter->y() };

				for (++iter; iter != points.end(); ++iter){
					if (iter->x() < computed.left)
						computed.left = iter->x();
					else if (iter->x() > computed.right)
						computed.right = iter->x();

					if (iter->y() < computed.top)
						computed.top = iter->y();
					else if (iter->y() > computed.bottom)
						computed.bottom = iter->y();
				}

				if (inclusive){
					++computed.right;
					++computed.bottom;
				}

				return computed;
			}

		private:
			void align_(origin_type origin){
				auto size = this->size();
				if (GRAFEEX_IS(origin, origin_type::right)){
					base_type::value_.right = base_type::value_.left;
					base_type::value_.left -= size.width();
				}
				else if (GRAFEEX_IS(origin, origin_type::center)){
					base_type::value_.left -= size.width() / 2;
					base_type::value_.right -= size.width() / 2;
				}

				if (GRAFEEX_IS(origin, origin_type::bottom)){
					base_type::value_.bottom = base_type::value_.top;
					base_type::value_.top -= size.height();
				}
				else if (GRAFEEX_IS(origin, origin_type::vertical_center)){
					base_type::value_.top -= size.height() / 2;
					base_type::value_.bottom -= size.height() / 2;
				}
			}
		};

		GRAFEEX_MAKE_OPERATORS(rect_origin_type)

		typedef basic_rect<point, size, ::RECT> rect;
		typedef basic_rect<short_point, short_size, rect_native_value<short> > short_rect;
		typedef basic_rect<float_point, float_size, rect_native_value<float> > float_rect;
	}
}

#endif /* !GRAFEEX_RECT_STRUCTURE_H */
