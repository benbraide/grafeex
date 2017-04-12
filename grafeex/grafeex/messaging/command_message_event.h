#pragma once

#ifndef GRAFEEX_COMMAND_MESSAGE_EVENT_H
#define GRAFEEX_COMMAND_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class command_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::WORD word_ype;

			explicit command_event(object &value);

			virtual ~command_event();

			virtual message_event &dispatch() override;

			virtual window_type *control() const;

			virtual word_ype id() const;

			virtual word_ype code() const;

			virtual bool is_menu() const;

			virtual bool is_accelerator() const;
		};
	}
}

#endif /* !GRAFEEX_COMMAND_MESSAGE_EVENT_H */
