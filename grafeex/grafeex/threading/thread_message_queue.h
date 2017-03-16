#pragma once

#ifndef GRAFEEX_THREAD_MESSAGE_QUEUE_H
#define GRAFEEX_THREAD_MESSAGE_QUEUE_H

#include <map>

#include "../wrappers/msg_wrapper.h"
#include "thread_event_object.h"

namespace grafeex{
	namespace threading{
		class message_queue{
		public:
			typedef structures::point point_type;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::msg msg_type;

			typedef ::UINT uint_type;
			typedef ::DWORD dword_type;
			typedef ::LRESULT result_type;

			typedef std::pair<uint_type, uint_type> filter_range_type;

			enum class peek_type : uint_type{
				nil					= PM_NOREMOVE,
				remove				= PM_REMOVE,
				dont_yield			= PM_NOYIELD,
			};

			enum class sent_type : dword_type{
				nil					= ISMEX_NOSEND,
				send				= ISMEX_SEND,
				notify				= ISMEX_NOTIFY,
				callback			= ISMEX_CALLBACK,
				replied				= ISMEX_REPLIED,
			};

			message_queue();

			bool get(msg_type &msg, const hwnd_type &target = nullptr, const filter_range_type &filter_range = {});

			bool peek(msg_type &msg, peek_type type = peek_type::nil, const hwnd_type &target = nullptr, const filter_range_type &filter_range = {});
			
			template <typename rep_type = std::chrono::milliseconds::rep, typename period_type = std::chrono::milliseconds::period>
			bool wait(const std::chrono::duration<rep_type, period_type> &delay = std::chrono::milliseconds(-1)){
				auto is_infinite = (delay == static_cast<std::chrono::duration<rep_type, period_type>>(-1));
				dword_type time_out = (is_infinite ? INFINITE : static_cast<dword_type>(delay.count()));
				return (::MsgWaitForMultipleObjectsEx(1, &event_.get_value_ref(), time_out, QS_ALLINPUT, MWMO_INPUTAVAILABLE) != WAIT_FAILED);
			}

			bool wake_wait();

			static point_type get_last_mouse_position();

			static long get_last_time();

			static bool is_sent();

			static sent_type get_sent_type();

			static bool reply(result_type value);

			static void post_quit(int exit_code = 0);

		protected:
			event_object event_;
		};
	}

	namespace messaging{
		using thread_queue = threading::message_queue;
	}
}

#endif /* !GRAFEEX_THREAD_MESSAGE_QUEUE_H */
