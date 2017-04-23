#pragma once

#ifndef GRAFEEX_VALUE_MESSAGE_EVENT_H
#define GRAFEEX_VALUE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class set_font_event : public message_event{
		public:
			using message_event::operator=;

			explicit set_font_event(object &value);

			virtual ~set_font_event();

			virtual message_event &dispatch() override;
		};

		class get_font_event : public message_event{
		public:
			using message_event::operator=;

			explicit get_font_event(object &value);

			virtual ~get_font_event();

			virtual message_event &dispatch() override;
		};

		class set_text_event : public message_event{
		public:
			using message_event::operator=;

			explicit set_text_event(object &value);

			virtual ~set_text_event();

			virtual message_event &dispatch() override;
		};

		class get_text_event : public message_event{
		public:
			using message_event::operator=;

			explicit get_text_event(object &value);

			virtual ~get_text_event();

			virtual message_event &dispatch() override;
		};

		class get_text_length_event : public message_event{
		public:
			using message_event::operator=;

			explicit get_text_length_event(object &value);

			virtual ~get_text_length_event();

			virtual message_event &dispatch() override;
		};
	}
}

#endif /* !GRAFEEX_VALUE_MESSAGE_EVENT_H */
