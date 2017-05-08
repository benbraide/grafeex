#pragma once

#ifndef GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class object;
		}
	}

	namespace messaging{
		class notify_event_handler{
		public:
			typedef ::UINT uint_type;
			typedef ::DWORD dword_type;

			virtual ~notify_event_handler();
		};

		class button_notify_event_handler : public notify_event_handler{
		public:
			typedef ::NMBCHOTITEM info_type;

			virtual ~button_notify_event_handler();

		protected:
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual dword_type on_draw_notify(custom_draw_event &e);

			virtual void on_dropdown_notify(notify_event &e);

			virtual void on_highlight_change_notify(notify_event &e);

			virtual void on_enter_notify(notify_event &e);

			virtual void on_leave_notify(notify_event &e);
		};

		class tool_tip_notify_event_handler : public notify_event_handler{
		public:
			virtual ~tool_tip_notify_event_handler();

		protected:
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual dword_type on_draw_notify(custom_draw_event &e);

			virtual const std::wstring &on_get_text_notify(tool_tip_get_text_event &e) = 0;

			virtual bool on_show_notify(notify_event &e);

			virtual void on_hide_notify(notify_event &e);

			virtual void on_link_click_notify(notify_event &e);
		};

		class tab_notify_event_handler : public notify_event_handler{
		public:
			virtual ~tab_notify_event_handler();

		protected:
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual void on_click_notify(notify_event &e);

			virtual void on_dbl_click_notify(notify_event &e);

			virtual void on_right_click_notify(notify_event &e);

			virtual void on_right_dbl_click_notify(notify_event &e);

			virtual void on_capture_release_notify(notify_event &e);

			virtual void on_focus_change_notify(notify_event &e);

			virtual void on_key_down_notify(notify_event &e);

			virtual void on_selection_change_notify(notify_event &e);

			virtual bool on_selection_changing_notify(notify_event &e);
		};

		class tool_bar_notify_event_handler : public notify_event_handler{
		public:
			typedef structures::rect rect_type;

			enum class drop_down_type{
				default				= TBDDRET_DEFAULT,
				no_default			= TBDDRET_NODEFAULT,
				treat_as_pressed	= TBDDRET_TREATPRESSED,
			};

			virtual ~tool_bar_notify_event_handler();

		protected://on__(.+)?\(
			GAPP_EHANDLER_BASIC_FRIENDS;

			virtual dword_type on_draw_notify(custom_draw_event &e);

			virtual void on_click_notify(notify_event &e);

			virtual void on_dbl_click_notify(notify_event &e);

			virtual void on_right_click_notify(notify_event &e);

			virtual void on_right_dbl_click_notify(notify_event &e);

			virtual void on_capture_release_notify(notify_event &e);

			virtual void on_key_down_notify(notify_event &e);

			virtual bool on_initialize_customize_notify(notify_event &e);

			virtual dword_type on_reset_notify(notify_event &e);

			virtual void on_begin_adjust_notify(notify_event &e);

			virtual void on_end_adjust_notify(notify_event &e);

			virtual void on_begin_drag_notify(notify_event &e);

			virtual void on_end_drag_notify(notify_event &e);

			virtual void on_drag_out_notify(notify_event &e);

			virtual bool on_drag_over_notify(notify_event &e);

			virtual void on_deleting_button_notify(notify_event &e);

			virtual bool on_query_delete_notify(notify_event &e);

			virtual bool on_query_insert_notify(notify_event &e);

			virtual drop_down_type on_drop_down_notify(notify_event &e);

			virtual bool on_hot_item_change_notify(notify_event &e);

			virtual bool on_get_button_info_notify(notify_event &e);

			virtual void on_change_notify(notify_event &e);

			virtual void on_customize_help_notify(notify_event &e);
		};
	}
}

#endif /* !GRAFEEX_NOTIFY_MESSAGE_EVENT_HANDLER_H */
