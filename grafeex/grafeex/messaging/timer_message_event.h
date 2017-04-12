#pragma once

#ifndef GRAFEEX_TIMER_MESSAGE_EVENT_H
#define GRAFEEX_TIMER_MESSAGE_EVENT_H

#include "message_event.h"
#include "../window/window_timer.h"

namespace grafeex{
	namespace messaging{
		class timer_event : public message_event{
		public:
			using message_event::operator=;

			typedef window::timer timer_type;
			typedef window::timer::unit_ptr_type unit_ptr_type;

			explicit timer_event(object &value);

			virtual ~timer_event();

			virtual message_event &dispatch() override;

			virtual timer_type *timer() const;

			virtual unit_ptr_type id() const;
		};
	}
}

#endif /* !GRAFEEX_TIMER_MESSAGE_EVENT_H */
