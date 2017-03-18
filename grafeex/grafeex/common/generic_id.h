#pragma once

#ifndef GRAFEEX_GENERIC_ID_H
#define GRAFEEX_GENERIC_ID_H

namespace grafeex{
	namespace common{
		template <class value_type>
		class generic_id{
		public:
			typedef value_type value_type;

			generic_id()
				: value_(static_cast<value_type>(0)){}

			virtual operator value_type() const{
				return value_;
			}

			virtual bool operator <(const generic_id &rhs) const{
				return (value_ < rhs.value_);
			}

			virtual bool operator <=(const generic_id &rhs) const{
				return (value_ <= rhs.value_);
			}

			virtual bool operator ==(const generic_id &rhs) const{
				return (value_ == rhs.value_);
			}

			virtual bool operator !=(const generic_id &rhs) const{
				return (value_ != rhs.value_);
			}

			virtual bool operator >=(const generic_id &rhs) const{
				return (value_ >= rhs.value_);
			}

			virtual bool operator >(const generic_id &rhs) const{
				return (value_ > rhs.value_);
			}

		protected:
			explicit generic_id(value_type value)
				: value_(value){}

			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_GENERIC_ID_H */
