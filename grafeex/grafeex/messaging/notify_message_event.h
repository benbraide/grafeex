#pragma once

#ifndef GRAFEEX_NOTIFY_MESSAGE_EVENT_H
#define GRAFEEX_NOTIFY_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class notify_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::UINT uint_type;
			typedef ::UINT_PTR uint_ptr_type;
			typedef ::NMHDR info_type;

			explicit notify_event(object &value);

			virtual ~notify_event();

			virtual message_event &dispatch() override;

			virtual window_type *control() const;

			virtual uint_ptr_type id() const;

			virtual uint_type code() const;

			virtual info_type &info() const;
		};
	}
}

#endif /* !GRAFEEX_NOTIFY_MESSAGE_EVENT_H */
