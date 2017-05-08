#pragma once

#ifndef GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class object;
		}
	}

	namespace messaging{
		class command_event_handler{
		public:
			typedef ::UINT uint_type;

			virtual ~command_event_handler();
		};

		class static_command_event_handler : public command_event_handler{
		public:
			virtual ~static_command_event_handler();

		protected:
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual void on_disable_command(command_event &e);

			virtual void on_enable_command(command_event &e);

			virtual void on_click_command(command_event &e);

			virtual void on_dbl_click_command(command_event &e);
		};

		class button_command_event_handler : public command_event_handler{
		public:
			virtual ~button_command_event_handler();

		protected:
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual void on_kill_focus_command(command_event &e);

			virtual void on_set_focus_command(command_event &e);

			virtual void on_click_command(command_event &e);

			virtual void on_dbl_click_command(command_event &e);
		};
	}
}

#endif /* !GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H */
