#pragma once

#ifndef GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H

#include "../common/preprocessor.h"

namespace grafeex{
	namespace messaging{
		enum class scope_event_option : unsigned int{
			nil				= (0 << 0x0000),
			create			= (1 << 0x0000),
			client			= (1 << 0x0001),
		};

		GRAFEEX_MAKE_OPERATORS(scope_event_option)

		class message_event;
		class close_event;
		class erase_background_event;
		class paint_event;
		class scope_event;
		class activate_event;
		class enable_event;
		class style_event;
		class visibility_event;

		template <bool is_client>
		class typed_paint_event;

		template <scope_event_option options>
		class typed_scope_event;

		template <bool style_is_changing>
		class typed_style_event;

		class general_event_handler{
		public:
			using nc_paint_event = typed_paint_event<false>;
			using client_paint_event = typed_paint_event<true>;

			using nc_create_event = typed_scope_event<scope_event_option::create>;
			using create_event = typed_scope_event<scope_event_option::create | scope_event_option::client>;

			using nc_destroy_event = typed_scope_event<scope_event_option::nil>;
			using destroy_event = typed_scope_event<scope_event_option::client>;

			using changing_style_event = typed_style_event<true>;
			using changed_style_event = typed_style_event<false>;

			virtual ~general_event_handler();

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
