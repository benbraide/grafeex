#pragma once

#ifndef GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

#define GNEH_UNIFORM_DISPATCH(e, ctrl, m) notify_forwarder_list_[(e)] = std::make_shared<uniform_event_forwarder<ctrl> >(&ctrl::m, false)

#define GNEH_UNIFORM_CTRLNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, notify_event_handler, on_control_ ## m)
#define GNEH_UNIFORM_BNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, button_notify_event_handler, on_button_ ## m)

namespace grafeex{
	namespace window{
		namespace controls{
			class object;
		}
	}

	namespace messaging{
		class event_forwarder_base;

		class notify_event_handler{
		public:
			typedef ::UINT uint_type;
			typedef ::DWORD dword_type;

			typedef application::object::dispatcher_list_type dispatcher_list_type;

			virtual ~notify_event_handler();

		protected:
			template <class> friend class uniform_event_forwarder;

			friend class notify_event;
			friend class custom_draw_event;

			friend class window::controls::object;

			virtual dword_type on_control_draw(custom_draw_event &e);
		};

		class button_notify_event_handler : public notify_event_handler{
		public:
			typedef ::NMBCHOTITEM info_type;

			virtual ~button_notify_event_handler();

			static void create_forwarder_list();

		protected:
			template <class> friend class uniform_event_forwarder;

			virtual void on_button_dropdown(object &e);

			virtual void on_button_highlight_change(object &e);

			virtual void on_button_enter(object &e);

			virtual void on_button_leave(object &e);

			static dispatcher_list_type notify_forwarder_list_;
		};
	}
}

#endif /* !GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H */
