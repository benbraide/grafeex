#pragma once

#ifndef GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

#define GMEH_UNIFORM_DISPATCH(e, ev, w, r, m) forwarder_list_[(e)] = std::make_shared<uniform_event_forwarder<ev, w, r> >(&w::m)
#define GMEH_UNIFORM_DISPATCH2(e, ev, w, m) GMEH_UNIFORM_DISPATCH(e, ev, w, void, m)

#define GMEH_UNIFORM_SCMD_DISPATCH(e, m) GMEH_UNIFORM_DISPATCH2(e, command_event, static_command_event_handler, on_static_ ## m)
#define GMEH_UNIFORM_BCMD_DISPATCH(e, m) GMEH_UNIFORM_DISPATCH2(e, command_event, button_command_event_handler, on_button_ ## m)

namespace grafeex{
	namespace messaging{
		class event_forwarder_base;

		class command_event_handler{
		public:
			typedef ::UINT uint_type;

			typedef std::shared_ptr<event_forwarder_base> forwarder_type;
			typedef std::unordered_map<uint_type, forwarder_type> forwarder_list_type;

			virtual ~command_event_handler();

		protected:
			friend class command_event;

			static forwarder_list_type forwarder_list_;
		};

		class static_command_event_handler : public command_event_handler{
		public:
			virtual ~static_command_event_handler();

			static void create_forwarder_list();
			
		protected:
			template <class, class, class> friend class uniform_event_forwarder;

			virtual void on_static_disable(command_event &e);

			virtual void on_static_enable(command_event &e);

			virtual void on_static_clicked(command_event &e);

			virtual void on_static_dbl_clicked(command_event &e);
		};

		class button_command_event_handler : public command_event_handler{
		public:
			virtual ~button_command_event_handler();

			static void create_forwarder_list();

		protected:
			template <class, class, class> friend class uniform_event_forwarder;

			virtual void on_button_kill_focus(command_event &e);

			virtual void on_button_set_focus(command_event &e);

			virtual void on_button_clicked(command_event &e);

			virtual void on_button_dbl_clicked(command_event &e);
		};
	}
}

#endif /* !GRAFEEX_COMMAND_MESSAGE_EVENT_HANDLER_H */
