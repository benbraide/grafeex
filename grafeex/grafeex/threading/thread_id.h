#pragma once

#ifndef GRAFEEX_THREAD_ID_H
#define GRAFEEX_THREAD_ID_H

#include "../common/windows_headers.h"

namespace grafeex{
	namespace threading{
		class id{
		public:
			typedef ::DWORD value_type;

			id();

			operator value_type() const;

			bool operator <(const id &rhs) const;

			bool operator <=(const id &rhs) const;

			bool operator ==(const id &rhs) const;

			bool operator !=(const id &rhs) const;

			bool operator >=(const id &rhs) const;

			bool operator >(const id &rhs) const;

		private:
			friend id get_current_id();

			explicit id(value_type value);

			value_type value_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_ID_H */
