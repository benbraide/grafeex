#pragma once

#ifndef GRAFEEX_STATE_MESSAGE_EVENT_H
#define GRAFEEX_STATE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class activate_event : public message_event{
		public:
			typedef ::BOOL bool_type;

			explicit activate_event(object &value);

			virtual ~activate_event();

			virtual message_event &dispatch() override;

			virtual bool is_active() const;

			virtual bool is_click() const;

			virtual bool is_minimized() const;
		};

		class enable_event : public message_event{
		public:
			typedef ::BOOL bool_type;

			explicit enable_event(object &value);

			virtual message_event &dispatch() override;

			virtual ~enable_event();

			virtual bool is_enabled() const;
		};
	}
}

#endif /* !GRAFEEX_STATE_MESSAGE_EVENT_H */
