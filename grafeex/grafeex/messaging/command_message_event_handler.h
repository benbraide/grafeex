#pragma once

#ifndef GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

#define GMEH_UNIFORM_DISPATCH(e, ctrl, m) command_forwarder_list_[(e)] = std::make_shared<uniform_event_forwarder<ctrl> >(&ctrl::m, true)

#define GMEH_UNIFORM_SCMD_DISPATCH(e, m) GMEH_UNIFORM_DISPATCH(e, static_command_event_handler, on_static_ ## m)
#define GMEH_UNIFORM_BCMD_DISPATCH(e, m) GMEH_UNIFORM_DISPATCH(e, button_command_event_handler, on_button_ ## m)

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

			typedef application::object::dispatcher_list_type dispatcher_list_type;

			virtual ~command_event_handler();
		};

		class static_command_event_handler : public command_event_handler{
		public:
			virtual ~static_command_event_handler();

			static void create_forwarder_list();
			
		protected:
			template <class> friend class uniform_event_forwarder;

			virtual void on_static_disable(object &e);

			virtual void on_static_enable(object &e);

			virtual void on_static_clicked(object &e);

			virtual void on_static_dbl_clicked(object &e);

			static dispatcher_list_type command_forwarder_list_;
		};

		class button_command_event_handler : public command_event_handler{
		public:
			virtual ~button_command_event_handler();

			static void create_forwarder_list();

		protected:
			template <class> friend class uniform_event_forwarder;

			virtual void on_button_kill_focus(object &e);

			virtual void on_button_set_focus(object &e);

			virtual void on_button_clicked(object &e);

			virtual void on_button_dbl_clicked(object &e);

			static dispatcher_list_type command_forwarder_list_;
		};
	}
}

#endif /* !GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H */
