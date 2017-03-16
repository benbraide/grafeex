#pragma once

#ifndef GRAFEEX_THREAD_EVENT_OBJECT_H
#define GRAFEEX_THREAD_EVENT_OBJECT_H

#include <string>
#include <chrono>

#include "../common/windows_headers.h"
#include "../wrappers/pointer_wrapper.h"

namespace grafeex{
	namespace threading{
		class event_object : public wrappers::pointer<::HANDLE, event_object>{
		public:
			typedef wrappers::pointer<::HANDLE, event_object> base_type;
			typedef ::DWORD dword_type;

			event_object();

			explicit event_object(const std::wstring &name);

			event_object(const event_object &) = delete;

			event_object(event_object &&target);

			virtual ~event_object();

			event_object &operator =(const event_object &) = delete;

			event_object &operator =(event_object &&target);

			virtual bool create(const std::wstring &name = L"");

			virtual bool destroy();

			virtual bool reset();

			virtual bool set();

			template <typename rep_type = std::chrono::milliseconds::rep, typename period_type = std::chrono::milliseconds::period>
			bool wait(const std::chrono::duration<rep_type, period_type> &delay = std::chrono::milliseconds(-1)){
				auto is_infinite = (delay == static_cast<std::chrono::duration<rep_type, period_type> >(-1));
				dword_type time_out = (is_infinite ? INFINITE : static_cast<dword_type>(delay.count()));
				return (::WaitForSingleObject(value_, time_out) == WAIT_OBJECT_0);
			}

			virtual bool is_created() const;

			virtual const value_type &get_value_ref() const;

		protected:
			bool create_(const std::wstring &name, bool manual);
		};

		class manual_event_object : public event_object{
		public:
			manual_event_object();

			explicit manual_event_object(const std::wstring &name);

			virtual ~manual_event_object();

			virtual bool create(const std::wstring &name = L"");
		};
	}
}

#endif /* !GRAFEEX_THREAD_EVENT_OBJECT_H */
