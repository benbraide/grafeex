#pragma once

#ifndef GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

namespace grafeex{
	namespace messaging{
		class general_event_handler{
		public:
			virtual ~general_event_handler();

		protected:
			friend class message_event;

			friend class scope_event;
			friend class nc_create_event;
			friend class create_event;
			friend class nc_destroy_event;
			friend class destroy_event;

			friend class close_event;

			friend class activate_event;
			friend class enable_event;

			friend class erase_background_event;
			friend class paint_event;
			friend class nc_paint_event;
			friend class client_paint_event;

			friend class style_event;
			friend class changing_style_event;
			friend class changed_style_event;

			friend class visibility_event;

			virtual void on_unhandled_event(message_event &e);

			virtual void on_event(message_event &e);

			virtual bool on_scope(scope_event &e);

			virtual bool on_create(create_event &e);

			virtual bool on_nc_create(nc_create_event &e);

			virtual void on_destroy(destroy_event &e);

			virtual void on_nc_destroy(nc_destroy_event &e);

			virtual bool on_close(close_event &e);

			virtual void on_active_change(activate_event &e);

			virtual void on_activate(activate_event &e);

			virtual void on_deactivate(activate_event &e);

			//virtual void on_child_activate(events::general &e);

			virtual void on_enable_change(enable_event &e);

			virtual void on_enable(enable_event &e);

			virtual void on_disable(enable_event &e);

			//virtual bool on_position_change(events::position_change &e);

			//virtual bool on_position_changing(events::position_change &e);

			//virtual void on_position_changed(events::position_change &e);

			//virtual bool on_move(events::move &e);

			//virtual bool on_moving(events::move &e);

			//virtual void on_moved(events::move &e);

			//virtual bool on_size(events::size &e);

			//virtual bool on_sizing(events::size &e);

			//virtual void on_sized(events::size &e);

			//virtual void on_minimized(events::size &e);

			//virtual void on_maximized(events::size &e);

			//virtual void on_get_min_max_info(events::min_max_info &e);

			virtual bool on_style_change(style_event &e);

			virtual bool on_style_changing(changing_style_event &e);

			virtual void on_style_changed(changed_style_event &e);

			virtual bool on_basic_style_changing(changing_style_event &e);

			virtual void on_basic_style_changed(changed_style_event &e);

			virtual bool on_extended_style_changing(changing_style_event &e);

			virtual void on_extended_style_changed(changed_style_event &e);

			virtual void on_visibility_change(visibility_event &e);

			virtual void on_show(visibility_event &e);

			virtual void on_hide(visibility_event &e);

			virtual bool on_erase_background(erase_background_event &e);

			virtual void on_paint(paint_event &e);

			virtual void on_nc_paint(nc_paint_event &e);

			virtual void on_paint_client(client_paint_event &e);

			//virtual void on_enter_size_move(events::general &e);

			//virtual void on_exit_size_move(events::general &e);

			//virtual void on_cancel_mode(events::general &e);

			//virtual bool on_query_open(events::general &e);

			//virtual void on_timer(events::timer &e);

			//virtual void on_notification(events::notification &e);

			//virtual void on_command(events::command &e);

			//virtual void on_menu_command(events::command &e);
		};
	}
}

#endif /* !GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H */
