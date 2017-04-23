#pragma once

#ifndef GRAFEEX_GDI_OBJECT_PTR_H
#define GRAFEEX_GDI_OBJECT_PTR_H

#include "gdi_object.h"

namespace grafeex{
	namespace gdi{
		template <class value_type>
		class object_ptr{
		public:
			typedef value_type value_type;

			object_ptr()
				: value_(nullptr){}

			explicit object_ptr(value_type value)
				: value_(value){}

			object_ptr(object_ptr &&target)
				: value_(target.value_){
				target.value_ = nullptr;
			}

			object_ptr(const object_ptr &) = delete;
			
			virtual ~object_ptr(){
				reset();
			}

			object_ptr &operator =(value_type value){
				reset();
				value_ = value;
				return *this;
			}

			object_ptr &operator =(object_ptr &&target){
				reset();
				value_ = target.value_;
				target.value_ = nullptr;
				return *this;
			}

			object_ptr &operator =(const object_ptr &) = delete;

			operator value_type() const{
				return value_;
			}

			bool operator ==(value_type value) const{
				return (value_ == value);
			}

			bool operator !=(value_type value) const{
				return (value_ != value);
			}

			bool operator ==(std::nullptr_t) const{
				return (value_ == nullptr);
			}

			bool operator !=(std::nullptr_t) const{
				return (value_ != nullptr);
			}

			void reset(){
				if (value_ != nullptr){
					::DeleteObject(value_);
					value_ = nullptr;
				}
			}

			value_type release(){
				auto value = value_;
				value_ = nullptr;
				return value;
			}

			value_type get() const{
				return value_;
			}

		protected:
			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_GDI_OBJECT_PTR_H */
