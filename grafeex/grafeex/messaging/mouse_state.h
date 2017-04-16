#pragma once

#ifndef GRAFEEX_MOUSE_STATE_H
#define GRAFEEX_MOUSE_STATE_H

#include "../common/timer.h"
#include "../common/preprocessor.h"

#include "../structures/point_structure.h"
#include "../structures/size_structure.h"
#include "../structures/enumerations.h"

#include "../gui/gui_object_tree.h"

#define GMMS_F1(x) (&input_event_handler::on_mouse_button_ ## x)
#define GMMS_F2(x, y) (&input_event_handler::on_mouse_ ## y ##_button_ ## x)
#define GMMS_F3(x, y, z) (&input_event_handler::on_mouse_ ## z ## _ ## y ##_button_ ## x)

#define GMMS_FF(x, y, z, i) dispatch_on_button_(e, GMMS_F1(x), GMMS_F2(x, y), GMMS_F3(x, y, z), i)

namespace grafeex{
	namespace window{
		class object;
	}

	namespace messaging{
		class mouse_event;

		class mouse_leave_event;
		class mouse_client_leave_event;

		class mouse_nc_move_event;
		class mouse_client_move_event;

		class mouse_nc_left_button_down_event;
		class mouse_nc_middle_button_down_event;
		class mouse_nc_right_button_down_event;

		class mouse_nc_left_button_up_event;
		class mouse_nc_middle_button_up_event;
		class mouse_nc_right_button_up_event;

		class mouse_nc_left_button_dbl_click_event;
		class mouse_nc_middle_button_dbl_click_event;
		class mouse_nc_right_button_dbl_click_event;

		class mouse_client_left_button_down_event;
		class mouse_client_middle_button_down_event;
		class mouse_client_right_button_down_event;

		class mouse_client_left_button_up_event;
		class mouse_client_middle_button_up_event;
		class mouse_client_right_button_up_event;

		class mouse_client_left_button_dbl_click_event;
		class mouse_client_middle_button_dbl_click_event;
		class mouse_client_right_button_dbl_click_event;

		class mouse_vertical_wheel_event;
		class mouse_horizontal_wheel_event;

		class input_event_handler;
		class general_event_handler;

		class mouse_state{
		public:
			typedef ::DWORD dword_type;
			typedef ::TRACKMOUSEEVENT track_info_type;

			typedef structures::point point_type;
			typedef structures::size size_type;

			typedef structures::enumerations::key_state_type key_state_type;
			typedef structures::enumerations::mouse_key_state_type mouse_key_state_type;

			typedef common::timer timer_type;

			enum class state : unsigned int{
				nil				= (0 << 0x0000),
				inside			= (1 << 0x0000),
				inside_client	= (1 << 0x0001),
				child			= (1 << 0x0002),
				button_down		= (1 << 0x0003),
				dragging		= (1 << 0x0004),
				drag_rejected	= (1 << 0x0005),
				no_click		= (1 << 0x0006),
				tracking		= (1 << 0x0007),
			};

			struct button_info{
				mouse_key_state_type states;
				point_type position;
			};

			struct drag_info{
				size_type threshold;
				mouse_key_state_type states;
			};

			struct drag_info_e{
				mouse_key_state_type button;
				point_type origin;
				size_type delta;
			};

			struct object_info{
				input_event_handler *owner;
				general_event_handler *general_event_owner;
				gui::object *object_owner;
				input_event_handler *parent;
				input_event_handler *moused;
				input_event_handler *focused;
			};

			explicit mouse_state(input_event_handler &owner);

			~mouse_state();

			input_event_handler *next_object(const point_type &position);

			input_event_handler *moused();

			void leave(mouse_leave_event &e);
			void leave(mouse_client_leave_event &e);

			void move(mouse_nc_move_event &e);
			void move(mouse_client_move_event &e);

			void down(mouse_nc_left_button_down_event &e);
			void down(mouse_nc_middle_button_down_event &e);
			void down(mouse_nc_right_button_down_event &e);

			void down(mouse_client_left_button_down_event &e);
			void down(mouse_client_middle_button_down_event &e);
			void down(mouse_client_right_button_down_event &e);

			void up(mouse_nc_left_button_up_event &e);
			void up(mouse_nc_middle_button_up_event &e);
			void up(mouse_nc_right_button_up_event &e);

			void up(mouse_client_left_button_up_event &e);
			void up(mouse_client_middle_button_up_event &e);
			void up(mouse_client_right_button_up_event &e);

			void dbl_click(mouse_nc_left_button_dbl_click_event &e);
			void dbl_click(mouse_nc_middle_button_dbl_click_event &e);
			void dbl_click(mouse_nc_right_button_dbl_click_event &e);

			void dbl_click(mouse_client_left_button_dbl_click_event &e);
			void dbl_click(mouse_client_middle_button_dbl_click_event &e);
			void dbl_click(mouse_client_right_button_dbl_click_event &e);

			void wheel(mouse_vertical_wheel_event &e);
			void wheel(mouse_horizontal_wheel_event &e);

		protected:
			friend class nc_destroy_event;
			friend class window::object;

			void recursive_leave_();

			void leave_(mouse_leave_event &e);

			void child_leave_(mouse_state &child, mouse_leave_event &e);

			void child_enter_(mouse_state &child, mouse_nc_move_event &e);

			bool begin_drag_(const point_type &mouse_position);

			bool drag_handled_();

			void track_(bool client);

			void dispatch_generic_(mouse_event &e);

			void dispatch_on_enter_(mouse_nc_move_event &e);

			void dispatch_on_enter_(mouse_client_move_event &e);

			void dispatch_on_drag_(const drag_info_e &info);

			template <typename event_type, typename f1t, typename f2t, typename f3t>
			void dispatch_on_button_(event_type &e, f1t f1, f2t f2, f3t f3, int index){
				timer_.stop();
				button_info_.position = e.position();

				switch (index){
				case 0:
					GRAFEEX_SET(button_info_.states, e.button());
					break;
				case 1:
					GRAFEEX_REMOVE(button_info_.states, e.button());
					break;
				default:
					break;
				}

				dispatch_generic_(e);
				if (e.is_propagating())
					(object_info_.owner->*f1)(e);

				if (e.is_propagating())
					(object_info_.owner->*f2)(e);

				if (e.is_propagating())
					(object_info_.owner->*f3)(e);
			}

			template <typename event_type>
			void pipe_on_button_down_(event_type &e){
				if (object_info_.parent != nullptr){//Pipe event to parent
					mouse_client_left_button_down_event ev(const_cast<object &>(e.get_object()));
					object_info_.parent->mouse_state_.object_info_.focused = object_info_.owner;
					object_info_.parent->mouse_state_.down(ev);
				}
			}

			template <typename event_type>
			void pipe_on_button_up_(event_type &e){
				if (object_info_.parent != nullptr){//Pipe event to parent
					mouse_client_left_button_up_event ev(const_cast<object &>(e.get_object()));
					object_info_.parent->mouse_state_.up(ev);
				}
			}

			template <typename event_type>
			void pipe_on_button_dbl_click_(event_type &e){
				if (object_info_.parent != nullptr){//Pipe event to parent
					mouse_client_left_button_dbl_click_event ev(const_cast<object &>(e.get_object()));
					object_info_.parent->mouse_state_.dbl_click(ev);
				}
			}

			void update_moused_(input_event_handler *target);

			object_info object_info_;
			button_info button_info_;
			drag_info drag_info_;
			state states_;
			timer_type timer_;
		};

		GRAFEEX_MAKE_OPERATORS(mouse_state::state)
	}
}

#endif /* !GRAFEEX_MOUSE_STATE_H */
