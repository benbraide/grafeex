#pragma once

#ifndef GRAFEEX_THREAD_ID_H
#define GRAFEEX_THREAD_ID_H

#include "../common/windows_headers.h"
#include "../common/generic_id.h"

namespace grafeex{
	namespace threading{
		class id : public common::generic_id<::DWORD>{
		public:
			typedef common::generic_id<::DWORD> base_type;

			id();

		private:
			friend id get_current_id();

			explicit id(value_type value);
		};
	}
}

#endif /* !GRAFEEX_THREAD_ID_H */
