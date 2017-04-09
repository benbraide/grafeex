#pragma once

#ifndef GRAFEEX_STATE_MESSAGE_EVENT_H
#define GRAFEEX_STATE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class activate_app_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;
			typedef ::DWORD dword_type;

			explicit activate_app_event(object &value);

			virtual ~activate_app_event();

			virtual message_event &dispatch() override;

			virtual dword_type other() const;

			virtual bool is_active() const;
		};

		class nc_activate_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;

			explicit nc_activate_event(object &value);

			virtual ~nc_activate_event();

			virtual message_event &dispatch() override;

			virtual bool is_active() const;
		};

		class activate_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;

			explicit activate_event(object &value);

			virtual ~activate_event();

			virtual message_event &dispatch() override;

			virtual bool is_active() const;

			virtual bool is_click() const;

			virtual bool is_minimized() const;
		};

		class child_activate_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;

			explicit child_activate_event(object &value);

			virtual ~child_activate_event();

			virtual message_event &dispatch() override;
		};

		class cancel_mode_event : public message_event{
		public:
			using message_event::operator=;

			explicit cancel_mode_event(object &value);

			virtual ~cancel_mode_event();

			virtual message_event &dispatch() override;
		};

		class enable_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;

			explicit enable_event(object &value);

			virtual message_event &dispatch() override;

			virtual ~enable_event();

			virtual bool is_enabled() const;
		};
	}
}

#endif /* !GRAFEEX_STATE_MESSAGE_EVENT_H */
