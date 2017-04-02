#pragma once

#ifndef GRAFEEX_CLOSE_MESSAGE_EVENT_H
#define GRAFEEX_CLOSE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class close_event : public message_event{
		public:
			using message_event::operator=;

			explicit close_event(object &value);

			virtual ~close_event();

			virtual message_event &dispatch() override;

		protected:
			virtual message_event &write_bool_(bool value) override;
		};
	}
}

#endif /* !GRAFEEX_CLOSE_MESSAGE_EVENT_H */
