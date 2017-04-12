#pragma once

#ifndef GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"
#include "../d2d/d2d_hwnd_render_target.h"

namespace grafeex{
	namespace window{
		class view;
	}

	namespace messaging{
		class general_event_handler{
		public:
			typedef ::DWORD dword_type;

			typedef ::D2D1_COLOR_F d2d_color_type;
			typedef ::HGDIOBJ icon_type;

			typedef d2d::hwnd_render_target render_type;
			typedef window::view view_type;

			virtual ~general_event_handler();

			virtual view_type &view() = 0;

			virtual render_type &renderer() = 0;

		protected:
			friend class message_event;

			friend class scope_event;
			friend class nc_create_event;
			friend class create_event;
			friend class nc_destroy_event;
			friend class destroy_event;

			friend class close_event;

			friend class nc_activate_event;
			friend class activate_event;
			friend class child_activate_event;
			friend class cancel_mode_event;
			friend class enable_event;

			friend class erase_background_event;
			friend class paint_event;
			friend class nc_paint_event;
			friend class client_paint_event;

			friend class print_client_event;
			friend class print_event;

			friend class style_event;
			friend class changing_style_event;
			friend class changed_style_event;

			friend class visibility_event;

			friend class position_event;
			friend class changing_position_event;
			friend class changed_position_event;

			friend class movement_event;
			friend class changing_movement_event;
			friend class changed_movement_event;

			friend class size_event;
			friend class changing_size_event;
			friend class changed_size_event;

			friend class min_max_event;
			friend class calculate_size_event;

			friend class size_move_event;
			friend class enter_size_move_event;
			friend class exit_size_move_event;

			friend class query_open_event;
			friend class query_drag_icon_event;

			friend class theme_changed_event;
			friend class user_changed_event;
			friend class input_language_changed_event;
			friend class input_language_change_request_event;
			friend class display_changed_event;

			friend class command_event;
			friend class notify_event;

			friend class timer_event;

			virtual void on_unhandled_event(message_event &e);

			virtual void on_event(message_event &e);

			virtual bool on_scope(scope_event &e);

			virtual bool on_create(create_event &e);

			virtual bool on_nc_create(nc_create_event &e);

			virtual void on_destroy(destroy_event &e);

			virtual void on_nc_destroy(nc_destroy_event &e);

			virtual bool on_close(close_event &e);

			virtual bool on_nc_active_change(nc_activate_event &e);

			virtual void on_nc_activate(nc_activate_event &e);

			virtual bool on_nc_deactivate(nc_activate_event &e);

			virtual void on_active_change(activate_event &e);

			virtual void on_activate(activate_event &e);

			virtual void on_deactivate(activate_event &e);

			virtual void on_child_activate(child_activate_event &e);

			virtual void on_cancel_mode(cancel_mode_event &e);

			virtual void on_enable_change(enable_event &e);

			virtual void on_enable(enable_event &e);

			virtual void on_disable(enable_event &e);

			virtual bool on_position_change(position_event &e);

			virtual bool on_position_changing(changing_position_event &e);

			virtual void on_position_changed(changed_position_event &e);

			virtual bool on_movement_change(movement_event &e);

			virtual bool on_movement_changing(changing_movement_event &e);

			virtual void on_movement_changed(changed_movement_event &e);

			virtual bool on_size_change(size_event &e);

			virtual bool on_size_changing(changing_size_event &e);

			virtual void on_size_changed(changed_size_event &e);

			virtual void on_minimized(changed_size_event &e);

			virtual void on_maximized(changed_size_event &e);

			virtual void on_get_min_max_info(min_max_event &e);

			virtual dword_type on_calculate_size(calculate_size_event &e);

			virtual void on_size_move(size_move_event &e);

			virtual void on_enter_size_move(enter_size_move_event &e);

			virtual void on_exit_size_move(exit_size_move_event &e);

			virtual bool on_query_open(query_open_event &e);

			virtual icon_type on_query_drag_icon(query_drag_icon_event &e);

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

			virtual void on_print_client(print_client_event &e);

			virtual void on_print(print_event &e);

			virtual void on_theme_changed(theme_changed_event &e);

			virtual void on_user_changed(user_changed_event &e);

			virtual bool on_input_language_changed(input_language_changed_event &e);

			virtual bool on_input_language_change_request(input_language_change_request_event &e);

			virtual void on_display_changed(display_changed_event &e);

			virtual void on_timer(timer_event &e);

			virtual void on_command(command_event &e);

			virtual void on_accelerator(command_event &e);

			virtual void on_notify(notify_event &e);
		};
	}
}

#endif /* !GRAFEEX_GENERAL_MESSAGE_EVENT_HANDLER_H */
