#pragma once

#ifndef GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

#define GNEH_UNIFORM_DISPATCH(e, ctrl, m) notify_forwarder_list_[(e)] = std::make_shared<uniform_event_forwarder<ctrl> >(&ctrl::m, false)

#define GNEH_UNIFORM_CTRLNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, notify_event_handler, on_control_ ## m)
#define GNEH_UNIFORM_BNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, button_notify_event_handler, on_button_ ## m)
#define GNEH_UNIFORM_TTNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, tool_tip_notify_event_handler, on_tool_tip_ ## m)
#define GNEH_UNIFORM_TABNOT_DISPATCH(e, m) GNEH_UNIFORM_DISPATCH(e, tab_notify_event_handler, on_tab_ ## m)

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

		class tool_tip_notify_event_handler : public notify_event_handler{
		public:
			virtual ~tool_tip_notify_event_handler();

			static void create_forwarder_list();

		protected:
			template <class> friend class uniform_event_forwarder;
			friend class tool_tip_get_text_event;

			virtual const std::wstring &on_tool_tip_get_text(tool_tip_get_text_event &e) = 0;

			virtual void on_tool_tip_show(object &e);

			virtual void on_tool_tip_hide(object &e);

			virtual void on_tool_tip_link_click(object &e);

			static dispatcher_list_type notify_forwarder_list_;
		};

		class tab_notify_event_handler : public notify_event_handler{
		public:
			virtual ~tab_notify_event_handler();

			static void create_forwarder_list();

		protected:
			template <class> friend class uniform_event_forwarder;

			virtual void on_tab_click(object &e);

			virtual void on_tab_dbl_click(object &e);

			virtual void on_tab_right_click(object &e);

			virtual void on_tab_right_dbl_click(object &e);

			virtual void on_tab_released_capture(object &e);

			virtual void on_tab_focus_change(object &e);

			virtual void on_tab_key_down(object &e);

			virtual void on_tab_selection_change(object &e);

			virtual void on_tab_selection_changing(object &e);

			static dispatcher_list_type notify_forwarder_list_;
		};
	}
}

#endif /* !GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H */
