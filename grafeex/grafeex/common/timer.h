#pragma once

#ifndef GRAFEEX_TIMER_H
#define GRAFEEX_TIMER_H

#include <mutex>
#include <condition_variable>
#include <functional>

#include "thread_auto.h"

namespace grafeex{
	namespace common{
		class timer{
		public:
			typedef std::function<void(timer &)> callback_type;

			typedef std::condition_variable condition_variable_type;
			typedef std::mutex lock_type;

			typedef std::lock_guard<lock_type> guard_type;
			typedef std::unique_lock<lock_type> unique_guard_type;

			timer(){}

			template <typename duration_type>
			timer(duration_type duration, callback_type callback){
				start(duration, callback);
			}

			~timer(){
				stop();
			}

			template <typename duration_type>
			void start(duration_type duration, callback_type callback){
				if (is_active_)
					return;

				thread_auto([this, duration, callback]{
					unique_guard_type lock(lock_);

					is_active_ = true;
					auto result = condition_.wait_for(lock, duration, [this]{
						return is_active_;
					});

					is_active_ = false;
					lock.unlock();

					if (!result)//Time elapsed
						callback(*this);
				});
			}

			void stop(){
				guard_type guard(lock_);
				if (is_active_){
					is_active_ = false;
					condition_.notify_one();
				}
			}

			bool is_active() const{
				return is_active_;
			}

		private:
			bool is_active_ = false;
			condition_variable_type condition_;
			lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_TIMER_H */
