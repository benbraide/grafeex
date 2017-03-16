#pragma once

#ifndef GRAFEEX_REF_RECT_STRUCTURE_H
#define GRAFEEX_REF_RECT_STRUCTURE_H

#include "../wrappers/pointer_wrapper.h"

#include "rect_structure.h"

namespace grafeex{
	namespace structures{
		template <class rect_type>
		class basic_ref_rect : public wrappers::pointer<typename rect_type::value_type, basic_ref_rect<rect_type> >{
		public:
			typedef rect_type rect_type;

			typedef typename rect_type::point_type point_type;
			typedef typename rect_type::size_type size_type;

			typedef typename point_type::field_type field_type;
			typedef typename rect_type::origin_type origin_type;

			typedef wrappers::pointer<typename rect_type::value_type, basic_ref_rect<rect_type> > base_type;

			basic_ref_rect()
				: base_type(nullptr){}

			basic_ref_rect(value_type value)
				: base_type(value){}

			basic_ref_rect(const basic_ref_rect &value)
				: base_type(value.value_){}

			basic_ref_rect(basic_ref_rect &&value)
				: base_type(value.value_){
				value.value_ = nullptr;
			}

			operator rect_type() const{
				return rect_type{ *base_type::value_ };
			}

			operator const typename rect_type::value_type &() const{
				return *base_type::value_;
			}

			operator typename rect_type::value_type &(){
				return *base_type::value_;
			}

			basic_ref_rect &operator =(value_type value){
				base_type::value_ = value;
				return *this;
			}

			basic_ref_rect &operator =(const basic_ref_rect &value){
				base_type::value_ = value.value_;
				return *this;
			}

			basic_ref_rect &operator =(basic_ref_rect &&value){
				base_type::value_ = value.value_;
				value.value_ = nullptr;
				return *this;
			}

			basic_ref_rect operator +(const size_type &rhs) const{
				basic_ref_rect copy(*this);
				return (copy += rhs);
			}

			basic_ref_rect operator -(const size_type &rhs) const{
				basic_ref_rect copy(*this);
				return (copy -= rhs);
			}

			basic_ref_rect &operator +=(const size_type &rhs){
				return offset(rhs);
			}

			basic_ref_rect &operator -=(const size_type &rhs){
				return offset(size_type{ -rhs.width(), -rhs.height() });
			}

			basic_ref_rect &normalize(){
				if (base_type::value_->right < base_type::value_->left)
					std::swap(base_type::value_->left, base_type::value_->right);

				if (base_type::value_->bottom < base_type::value_->top)
					std::swap(base_type::value_->top, base_type::value_->bottom);

				return *this;
			}

			basic_ref_rect &set(field_type left, field_type top, field_type right, field_type bottom){
				*base_type::value_ = rect_type::value_type{ left, top, right, bottom };
				return *this;
			}

			basic_ref_rect &set(field_type left, field_type top_bottom, field_type right){
				*base_type::value_ = rect_type::value_type{ left, top_bottom, right, top_bottom };
				return *this;
			}

			basic_ref_rect &set(field_type left_right, field_type top_bottom){
				*base_type::value_ = rect_type::value_type{ left_right, top_bottom, left_right, top_bottom };
				return *this;
			}

			basic_ref_rect &set(field_type value){
				*base_type::value_ = rect_type::value_type{ value, value, value, value };
				return *this;
			}

			basic_ref_rect &set(const point_type &top_left, const point_type &bottom_right){
				*base_type::value_ = rect_type::value_type{ top_left.x(), top_left.y(), bottom_right.x(), bottom_right.y() };
				return *this;
			}

			basic_ref_rect &set(const point_type &top_left, const size_type &size, origin_type origin = origin_type::nil){
				*base_type::value_ = rect_type::value_type{ top_left.x(), top_left.y(), top_left.x() + size.width(),
					top_left.y() + size.height() };
				align_(origin);
				return *this;
			}

			basic_ref_rect &left(field_type value){
				base_type::value_->left = value;
				return *this;
			}

			basic_ref_rect &top(field_type value){
				base_type::value_->top = value;
				return *this;
			}

			basic_ref_rect &right(field_type value){
				base_type::value_->right = value;
				return *this;
			}

			basic_ref_rect &bottom(field_type value){
				base_type::value_->bottom = value;
				return *this;
			}

			basic_ref_rect &top_left(const point_type &value){
				base_type::value_->left = value.x();
				base_type::value_->top = value.y();
				return *this;
			}

			basic_ref_rect &top_right(const point_type &value){
				base_type::value_->right = value.x();
				base_type::value_->top = value.y();
				return *this;
			}

			basic_ref_rect &bottom_right(const point_type &value){
				base_type::value_->right = value.x();
				base_type::value_->bottom = value.y();
				return *this;
			}

			basic_ref_rect &bottom_left(const point_type &value){
				base_type::value_->left = value.x();
				base_type::value_->bottom = value.y();
				return *this;
			}

			basic_ref_rect &inflate(const size_type &value){
				base_type::value_->left -= value.width();
				base_type::value_->top -= value.height();
				base_type::value_->right += value.width();
				base_type::value_->bottom += value.height();
				return *this;
			}

			basic_ref_rect &inflate(const basic_ref_rect &value){
				base_type::value_->left -= value.value_->left;
				base_type::value_->top -= value.value_->top;
				base_type::value_->right += value.value_->right;
				base_type::value_->bottom += value.value_->bottom;
				return *this;
			}

			basic_ref_rect &deflate(const size_type &value){
				base_type::value_->left += value.width();
				base_type::value_->top += value.height();
				base_type::value_->right -= value.width();
				base_type::value_->bottom -= value.height();
				return *this;
			}

			basic_ref_rect &deflate(const basic_ref_rect &value){
				base_type::value_->left += value.value_->left;
				base_type::value_->top += value.value_->top;
				base_type::value_->right -= value.value_->right;
				base_type::value_->bottom -= value.value_->bottom;
				return *this;
			}

			basic_ref_rect &offset(const size_type &value){
				base_type::value_->left += value.width();
				base_type::value_->top += value.height();
				base_type::value_->right += value.width();
				base_type::value_->bottom += value.height();
				return *this;
			}

			basic_ref_rect &move_to(const point_type &value){
				return offset(value - top_left());
			}

			const typename rect_type::value_type &get() const{
				return *base_type::value_;
			}

			field_type left() const{
				return base_type::value_->left;
			}

			field_type top() const{
				return base_type::value_->top;
			}

			field_type right() const{
				return base_type::value_->right;
			}

			field_type bottom() const{
				return base_type::value_->bottom;
			}

			point_type top_left() const{
				return point_type{ base_type::value_->left, base_type::value_->top };
			}

			point_type top_right() const{
				return point_type{ base_type::value_->right, base_type::value_->top };
			}

			point_type bottom_right() const{
				return point_type{ base_type::value_->right, base_type::value_->bottom };
			}

			point_type bottom_left() const{
				return point_type{ base_type::value_->left, base_type::value_->bottom };
			}

			size_type size() const{
				return size_type{ base_type::value_->right - base_type::value_->left, base_type::value_->bottom - base_type::value_->top };
			}

			size_type sum() const{
				return size_type{ base_type::value_->right + base_type::value_->left, base_type::value_->bottom + base_type::value_->top };
			}

			rect_type get_inflated(const size_type &value) const{
				rect_type copy(*this);
				return copy.inflate(value);
			}

			rect_type get_inflated(const rect_type &value) const{
				rect_type copy(*this);
				return copy.inflate(value);
			}

			rect_type get_deflated(const size_type &value) const{
				rect_type copy(*this);
				return copy.deflate(value);
			}

			rect_type get_deflated(const rect_type &value) const{
				rect_type copy(*this);
				return copy.deflate(value);
			}

			rect_type get_after_offset(const size_type &value) const{
				rect_type copy(*this);
				return copy.offset(value);
			}

			rect_type get_moved(const point_type &value) const{
				rect_type copy(*this);
				return copy.move_to(value);
			}

			rect_type get_intersection(const rect_type &value) const{
				return rect_type{
					(base_type::value_->left > value.left()) ? base_type::value_->left : value.left(),
					(base_type::value_->top > value.top()) ? base_type::value_->top : value.top(),
					(base_type::value_->right < value.right()) ? base_type::value_->right : value.right(),
					(base_type::value_->bottom < value.bottom()) ? base_type::value_->bottom : value.bottom()
				};
			}

			rect_type get_union(const rect_type &value) const{
				return rect_type{
					(base_type::value_->left < value.left()) ? base_type::value_->left : value.left(),
					(base_type::value_->top < value.top()) ? base_type::value_->top : value.top(),
					(base_type::value_->right > value.right()) ? base_type::value_->right : value.right(),
					(base_type::value_->bottom > value.bottom()) ? base_type::value_->bottom : value.bottom()
				};
			}

			bool is_empty() const{
				return (base_type::value_->left >= base_type::value_->right || base_type::value_->top >= base_type::value_->bottom);
			}

			bool is_normalized() const{
				return (base_type::value_->left <= base_type::value_->right && base_type::value_->top <= base_type::value_->bottom);
			}

			bool intersects(const basic_ref_rect &value) const{
				return (is_empty() || value.is_empty()) ? false : !intersection(value).is_empty();
			}

			bool contains(const basic_ref_rect &value) const{
				if (is_empty() || value.is_empty())
					return false;

				return (value.value_->left >= base_type::value_->left && value.value_->top >= base_type::value_->top &&
					value.value_->right <= base_type::value_->right && value.value_->bottom <= base_type::value_->bottom);
			}

			bool contains(const point_type &value) const{
				return (value.x() >= base_type::value_->left && value.y() >= base_type::value_->top &&
					value.x() < base_type::value_->right && value.y() < base_type::value_->bottom);
			}

			static int compare(const value_type &lhs, const value_type &rhs){
				return (lhs->left == rhs->left && lhs->top == rhs->top && lhs->right == rhs->right && lhs->bottom == rhs->bottom) ? 0 : -1;
			}

		private:
			void align_(origin_type origin){
				auto size = size();
				if (GRAFEEX_IS(origin, origin_type::right)){
					base_type::value_->right = base_type::value_->left;
					base_type::value_->left -= size.width();
				}
				else if (GRAFEEX_IS(origin, origin_type::center)){
					base_type::value_->left -= size.width() / 2;
					base_type::value_->right -= size.width() / 2;
				}

				if (GRAFEEX_IS(origin, origin_type::bottom)){
					base_type::value_->bottom = base_type::value_->top;
					base_type::value_->top -= size.height();
				}
				else if (GRAFEEX_IS(origin, origin_type::vertical_center)){
					base_type::value_->top -= size.height() / 2;
					base_type::value_->bottom -= size.height() / 2;
				}
			}
		};

		typedef basic_ref_rect<rect> ref_rect;
		typedef basic_ref_rect<short_rect> short_ref_rect;
		typedef basic_ref_rect<float_rect> float_ref_rect;
	}
}

#endif /* !GRAFEEX_REF_RECT_STRUCTURE_H */
