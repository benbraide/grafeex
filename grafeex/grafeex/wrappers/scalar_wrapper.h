#pragma once

#ifndef GRAFEEX_SCALAR_WRAPPER_H
#define GRAFEEX_SCALAR_WRAPPER_H

namespace grafeex{
	namespace wrappers{
		template <class value_type, class object_type>
		class scalar{
		public:
			typedef value_type value_type;
			typedef object_type object_type;

			explicit scalar(value_type value)
				: value_(value){}

			virtual operator value_type() const{
				return value_;
			}

			object_type &operator =(value_type value){
				value_ = value;
				return *this;
			}

			bool operator ==(value_type rhs) const{
				return (value_ == rhs);
			}

			friend bool operator ==(value_type lhs, const scalar &rhs){
				return (lhs == rhs.value_);
			}

			bool operator ==(const object_type &rhs) const{
				return (value_ == rhs.operator value_type());
			}

			bool operator !=(value_type rhs) const{
				return !(*this == rhs);
			}

			friend bool operator !=(value_type lhs, const scalar &rhs){
				return !(lhs == rhs);
			}

			bool operator !=(const object_type &rhs) const{
				return !(*this == rhs);
			}

			value_type get_native_value() const{
				return value_;
			}

		protected:
			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_SCALAR_WRAPPER_H */
