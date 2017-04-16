#pragma once

#ifndef GRAFEEX_SYSTEM_MESSAGE_EVENT_H
#define GRAFEEX_SYSTEM_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class theme_changed_event : public message_event{
		public:
			using message_event::operator=;

			explicit theme_changed_event(object &value);

			virtual ~theme_changed_event();

			virtual message_event &dispatch() override;
		};

		class user_changed_event : public message_event{
		public:
			using message_event::operator=;

			explicit user_changed_event(object &value);

			virtual ~user_changed_event();

			virtual message_event &dispatch() override;
		};

		class input_language_changed_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;

			explicit input_language_changed_event(object &value);

			virtual ~input_language_changed_event();

			virtual message_event &dispatch() override;

			virtual wparam_type character_set() const;

			virtual lparam_type locale_id() const;
		};

		class input_language_change_request_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;

			explicit input_language_change_request_event(object &value);

			virtual ~input_language_change_request_event();

			virtual message_event &dispatch() override;

			virtual wparam_type locale() const;

			virtual lparam_type locale_id() const;
		};

		class display_changed_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::WPARAM wparam_type;
			typedef ::WORD word_type;

			explicit display_changed_event(object &value);

			virtual ~display_changed_event();

			virtual message_event &dispatch() override;

			virtual wparam_type image_depth() const;

			virtual word_type horizontal_resolution() const;

			virtual word_type vertical_resolution() const;
		};

		class capture_changed_event : public message_event{
		public:
			using message_event::operator=;

			explicit capture_changed_event(object &value);

			virtual ~capture_changed_event();

			virtual message_event &dispatch() override;

			virtual window_type *window_with_capture() const;
		};
	}
}

#endif /* !GRAFEEX_SYSTEM_MESSAGE_EVENT_H */
