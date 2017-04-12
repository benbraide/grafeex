#pragma once

#ifndef GRAFEEX_WINDOW_TIMER_H
#define GRAFEEX_WINDOW_TIMER_H

#include "../common/windows_headers.h"

namespace grafeex{
	namespace window{
		class object;

		class timer{
		public:
			typedef ::UINT_PTR unit_ptr_type;
			typedef ::UINT uint_type;

			timer();

			timer(object &owner, uint_type duration);

			~timer();

			bool create(object &owner, uint_type duration);

			bool destroy();

			bool is_created() const;

			object *owner() const;

			unit_ptr_type id() const;

			uint_type duration() const;

		private:
			object *owner_;
			unit_ptr_type id_;
			uint_type duration_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_TIMER_H */
