#pragma once

#ifndef GRAFEEX_POINTER_WRAPPER_H
#define GRAFEEX_POINTER_WRAPPER_H

namespace grafeex{
	namespace wrappers{
		template <class value_type, class object_type>
		class pointer{
		public:
			typedef value_type *value_type;
			typedef object_type object_type;

			pointer(value_type value)
				: value_(value){}

			virtual operator value_type() const{
				return value_;
			}

			bool operator ==(std::nullptr_t rhs) const{
				return (compare(value_, rhs) == 0);
			}

			friend bool operator ==(std::nullptr_t lhs, const pointer &rhs){
				return (compare(lhs, rhs.value_) == 0);
			}

			bool operator ==(value_type rhs) const{
				return (compare(value_, rhs) == 0);
			}

			friend bool operator ==(value_type lhs, const pointer &rhs){
				return (compare(lhs, rhs.value_) == 0);
			}

			bool operator ==(const object_type &rhs) const{
				return (compare(value_, rhs) == 0);
			}

			bool operator !=(std::nullptr_t rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(std::nullptr_t lhs, const pointer &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(value_type rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(value_type lhs, const pointer &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(const object_type &rhs) const{
				return !(*this == rhs);
			}

			value_type get_native_value() const{
				return value_;
			}

			static int compare(value_type lhs, value_type rhs){
				return (lhs == rhs) ? 0 : -1;
			}

		protected:
			value_type value_;
		};

		template <class value_type, class object_type>
		class pointer<value_type *, object_type>{
		public:
			typedef value_type value_type;
			typedef object_type object_type;

			pointer(value_type value)
				: value_(value){}

			virtual operator value_type() const{
				return value_;
			}

			bool operator ==(std::nullptr_t rhs) const{
				return (compare(value_, rhs) == 0);
			}

			friend bool operator ==(std::nullptr_t lhs, const pointer &rhs){
				return (compare(lhs, rhs.value_) == 0);
			}

			bool operator ==(value_type rhs) const{
				return (compare(value_, rhs) == 0);
			}

			friend bool operator ==(value_type lhs, const pointer &rhs){
				return (compare(lhs, rhs.value_) == 0);
			}

			bool operator ==(const object_type &rhs) const{
				return (compare(value_, rhs) == 0);
			}

			bool operator !=(std::nullptr_t rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(std::nullptr_t lhs, const pointer &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(value_type rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(value_type lhs, const pointer &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(const object_type &rhs) const{
				return !(*this == rhs);
			}

			value_type get_native_value() const{
				return value_;
			}

			static int compare(value_type lhs, value_type rhs){
				return (lhs == rhs) ? 0 : -1;
			}

		protected:
			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_POINTER_WRAPPER_H */
