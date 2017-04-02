#pragma once

#ifndef GRAFEEX_EVENT_ENTRY_H
#define GRAFEEX_EVENT_ENTRY_H

#include <unordered_map>

#include "../common/windows_headers.h"

namespace grafeex{
	namespace events{
		class entry{
		public:
			typedef ::ULONG_PTR group_type;
			typedef unsigned long long value_type;

			entry();

			bool operator ==(const entry &rhs) const;

			bool operator !=(const entry &rhs) const;

			group_type group() const;

		private:
			friend struct entry_hasher;
			template <class, class, class...> friend class listeners;

			entry(group_type group, value_type value);

			group_type group_;
			value_type value_;
		};

		struct entry_hasher{
			std::size_t operator ()(const entry &value) const;
		};
	}
}

#endif /* !GRAFEEX_EVENT_ENTRY_H */
