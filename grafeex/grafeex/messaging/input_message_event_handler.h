#pragma once

#ifndef GRAFEEX_INPUT_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_INPUT_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"
#include "mouse_state.h"

namespace grafeex{
	namespace messaging{
		class input_event_handler{
		public:
			typedef ::DWORD dword_type;
			typedef mouse_state mouse_state_type;

			typedef mouse_event::mouse_key_state_type mouse_key_state_type;
			typedef mouse_state::drag_info_e drag_info;

			typedef structures::point point_type;
			typedef structures::size size_type;

			input_event_handler();

			virtual ~input_event_handler();

			mouse_state_type &mouse_state();

		protected:
			friend class input_event;

			friend class key_event;
			friend class mouse_event;

			friend class key_down_event;
			friend class key_up_event;
			friend class char_event;
			friend class dead_char_event;

			friend class normal_key_down_event;
			friend class normal_key_up_event;
			friend class normal_char_event;
			friend class normal_dead_char_event;

			friend class system_key_down_event;
			friend class system_key_up_event;
			friend class system_char_event;
			friend class system_dead_char_event;

			friend class mouse_state;

			virtual void on_input(input_event &e);

			virtual void on_key(key_event &e);

			virtual void on_key_down(key_down_event &e);

			virtual void on_key_up(key_up_event &e);

			virtual void on_char(char_event &e);

			virtual void on_dead_char(dead_char_event &e);

			virtual void on_normal_key_down(normal_key_down_event &e);

			virtual void on_normal_key_up(normal_key_up_event &e);

			virtual void on_normal_char(normal_char_event &e);

			virtual void on_normal_dead_char(normal_dead_char_event &e);

			virtual void on_system_key_down(system_key_down_event &e);

			virtual void on_system_key_up(system_key_up_event &e);

			virtual void on_system_char(system_char_event &e);

			virtual void on_system_dead_char(system_dead_char_event &e);

			virtual void on_mouse(mouse_event &e);

			virtual void on_mouse_leave();

			virtual void on_mouse_client_leave();

			virtual void on_mouse_enter(mouse_move_event &e);

			virtual void on_mouse_nc_enter(mouse_nc_move_event &e);

			virtual void on_mouse_client_enter(mouse_client_move_event &e);

			virtual void on_mouse_move(mouse_move_event &e);

			virtual void on_mouse_nc_move(mouse_nc_move_event &e);

			virtual void on_mouse_client_move(mouse_client_move_event &e);

			virtual dword_type on_mouse_hover_request(const point_type &mouse_position);

			virtual void on_mouse_hover(const point_type &mouse_position);

			virtual void on_mouse_button_down(mouse_button_down_event &e);

			virtual void on_mouse_left_button_down(mouse_left_button_down_event &e);

			virtual void on_mouse_nc_left_button_down(mouse_nc_left_button_down_event &e);

			virtual void on_mouse_client_left_button_down(mouse_client_left_button_down_event &e);

			virtual void on_mouse_middle_button_down(mouse_middle_button_down_event &e);

			virtual void on_mouse_nc_middle_button_down(mouse_nc_middle_button_down_event &e);

			virtual void on_mouse_client_middle_button_down(mouse_client_middle_button_down_event &e);

			virtual void on_mouse_right_button_down(mouse_right_button_down_event &e);

			virtual void on_mouse_nc_right_button_down(mouse_nc_right_button_down_event &e);

			virtual void on_mouse_client_right_button_down(mouse_client_right_button_down_event &e);

			virtual void on_mouse_button_up(mouse_button_up_event &e);

			virtual void on_mouse_left_button_up(mouse_left_button_up_event &e);

			virtual void on_mouse_nc_left_button_up(mouse_nc_left_button_up_event &e);

			virtual void on_mouse_client_left_button_up(mouse_client_left_button_up_event &e);

			virtual void on_mouse_middle_button_up(mouse_middle_button_up_event &e);

			virtual void on_mouse_nc_middle_button_up(mouse_nc_middle_button_up_event &e);

			virtual void on_mouse_client_middle_button_up(mouse_client_middle_button_up_event &e);

			virtual void on_mouse_right_button_up(mouse_right_button_up_event &e);

			virtual void on_mouse_nc_right_button_up(mouse_nc_right_button_up_event &e);

			virtual void on_mouse_client_right_button_up(mouse_client_right_button_up_event &e);

			virtual void on_mouse_button_dbl_click(mouse_button_dbl_click_event &e);

			virtual void on_mouse_left_button_dbl_click(mouse_left_button_dbl_click_event &e);

			virtual void on_mouse_nc_left_button_dbl_click(mouse_nc_left_button_dbl_click_event &e);

			virtual void on_mouse_client_left_button_dbl_click(mouse_client_left_button_dbl_click_event &e);

			virtual void on_mouse_middle_button_dbl_click(mouse_middle_button_dbl_click_event &e);

			virtual void on_mouse_nc_middle_button_dbl_click(mouse_nc_middle_button_dbl_click_event &e);

			virtual void on_mouse_client_middle_button_dbl_click(mouse_client_middle_button_dbl_click_event &e);

			virtual void on_mouse_right_button_dbl_click(mouse_right_button_dbl_click_event &e);

			virtual void on_mouse_nc_right_button_dbl_click(mouse_nc_right_button_dbl_click_event &e);

			virtual void on_mouse_client_right_button_dbl_click(mouse_client_right_button_dbl_click_event &e);

			virtual bool on_mouse_begin_drag(const drag_info &info);

			virtual void on_mouse_end_drag(const drag_info &info);

			virtual void on_mouse_drag_out(const drag_info &info);

			virtual void on_mouse_drag(const drag_info &info);

			virtual void on_mouse_left_drag(const drag_info &info);

			virtual void on_mouse_middle_drag(const drag_info &info);

			virtual void on_mouse_right_drag(const drag_info &info);

			virtual bool on_mouse_wheel(mouse_wheel_event &e);

			virtual bool on_mouse_vertical_wheel(mouse_vertical_wheel_event &e);

			virtual bool on_mouse_horizontal_wheel(mouse_horizontal_wheel_event &e);

			mouse_state_type mouse_state_;
		};
	}
}

#endif /* !GRAFEEX_INPUT_MESSAGE_EVENT_HANDLER_H */
