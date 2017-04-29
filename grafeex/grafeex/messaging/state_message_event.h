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

		class mouse_activate_event : public message_event{
		public:
			using message_event::operator=;

			typedef structures::enumerations::hit_target_type hit_target_type;
			typedef ::WORD word_type;

			enum class return_type{
				activate				= MA_ACTIVATE,
				activate_and_eat		= MA_ACTIVATEANDEAT,
				no_activate				= MA_NOACTIVATE,
				no_activate_and_eat		= MA_NOACTIVATEANDEAT,
			};

			explicit mouse_activate_event(object &value);

			virtual ~mouse_activate_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit() const;

			virtual word_type mouse_message() const;
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

			virtual ~enable_event();

			virtual message_event &dispatch() override;

			virtual bool is_enabled() const;
		};

		class focus_change_event : public message_event{
		public:
			using message_event::operator=;

			explicit focus_change_event(object &value);

			virtual ~focus_change_event();

			virtual message_event &dispatch() override;

			virtual bool is_focused() const = 0;
		};

		class set_focus_event : public focus_change_event{
		public:
			using message_event::operator=;

			explicit set_focus_event(object &value);

			virtual ~set_focus_event();

			virtual message_event &dispatch() override;

			virtual bool is_focused() const override;
		};

		class kill_focus_event : public focus_change_event{
		public:
			using message_event::operator=;

			explicit kill_focus_event(object &value);

			virtual ~kill_focus_event();

			virtual message_event &dispatch() override;

			virtual bool is_focused() const override;
		};
	}
}

#endif /* !GRAFEEX_STATE_MESSAGE_EVENT_H */
