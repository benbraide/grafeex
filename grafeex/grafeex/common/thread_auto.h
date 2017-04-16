#pragma once

#ifndef GRAFEEX_THREAD_AUTO_H
#define GRAFEEX_THREAD_AUTO_H

#include <thread>

namespace grafeex{
	namespace common{
		class thread_auto{
		public:
			template <class callback_type, class... value_types>
			explicit thread_auto(callback_type &&callback, value_types &&... args)
				: handle_(callback, args...){}

			~thread_auto(){
				handle_.detach();
			}

		private:
			std::thread handle_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_AUTO_H */
