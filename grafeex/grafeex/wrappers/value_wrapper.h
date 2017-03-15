#pragma once

#ifndef GRAFEEX_VALUE_WRAPPER_H
#define GRAFEEX_VALUE_WRAPPER_H

namespace grafeex{
	namespace wrappers{
		template <class value_type, class object_type>
		class value{
		public:
			typedef value_type value_type;
			typedef object_type object_type;

			explicit value(const value_type &value)
				: value_(value){}

			virtual operator const value_type &() const{
				return value_;
			}

			virtual operator value_type &(){
				return value_;
			}

			virtual operator const value_type *() const{
				return &value_;
			}

			virtual operator value_type *(){
				return &value_;
			}

			object_type &operator =(const value_type &value){
				value_ = value;
				return *this;
			}

			bool operator ==(const value_type &rhs) const{
				return (object_type::compare(value_, rhs) == 0);
			}

			friend bool operator ==(const value_type &lhs, const value &rhs){
				return (object_type::compare(lhs, rhs.value_) == 0);
			}

			bool operator ==(const object_type &rhs) const{
				return (object_type::compare(value_, rhs) == 0);
			}

			bool operator !=(const value_type &rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(const value_type &lhs, const value &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(const object_type &rhs) const{
				return !(*this == rhs);
			}

			const value_type &get_native_value() const{
				return value_;
			}

		protected:
			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_VALUE_WRAPPER_H */
