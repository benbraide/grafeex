#pragma once

#ifndef GRAFEEX_INPUT_MESSAGE_EVENT_H
#define GRAFEEX_INPUT_MESSAGE_EVENT_H

#include <bitset>
#include <vector>

#include "../structures/enumerations.h"
#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class input_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BYTE byte_type;
			typedef structures::enumerations::key_state_type key_state_type;

			struct key_map_info{
				byte_type key;
				key_state_type value;
				bool toggle;
			};

			typedef std::vector<key_map_info> key_map_info_list_type;

			explicit input_event(object &value);

			virtual ~input_event();

			virtual message_event &dispatch() override;

			virtual key_state_type key_states() const;

			virtual bool is_mouse() const = 0;

			static bool cache_key_states();

			static key_state_type retrieve_key_states();

			static byte_type keyboard_state[0x100];
		};

		class key_event : public input_event{
		public:
			using message_event::operator=;

			enum class state : unsigned int{
				nil					= (0 << 0x0000),
				is_system			= (1 << 0x0000),
				is_extended			= (1 << 0x0001),
				was_down			= (1 << 0x0002),
				being_released		= (1 << 0x0003),
				alt_down			= (1 << 0x0004),
				down				= (1 << 0x0005),
				up					= (1 << 0x0006),
				pressed				= (1 << 0x0007),
				dead				= (1 << 0x0008),
			};

			explicit key_event(object &value);

			virtual ~key_event();

			virtual message_event &dispatch() override;

			virtual bool is_mouse() const override;

			virtual bool is_system() const;

			virtual bool is_extended() const;

			virtual bool was_down() const;

			virtual bool is_being_released() const;

			virtual bool alt_key_down() const;

			virtual bool is_down() const;

			virtual bool is_up() const;

			virtual bool is_char() const;

			virtual bool is_dead() const;

			virtual unsigned short code() const;

			virtual short scan_code() const;

			virtual short repeat_count() const;

			virtual state states() const;

		protected:
			unsigned short code_;
			short scan_code_;
			short repeat_count_;
			state states_;
		};

		class key_down_event : public key_event{
		public:
			explicit key_down_event(object &value);

			virtual ~key_down_event();

			virtual message_event &dispatch() override;
		};

		class key_up_event : public key_event{
		public:
			explicit key_up_event(object &value);

			virtual ~key_up_event();

			virtual message_event &dispatch() override;
		};

		class char_event : public key_event{
		public:
			explicit char_event(object &value);

			virtual ~char_event();

			virtual message_event &dispatch() override;
		};

		class dead_char_event : public key_event{
		public:
			explicit dead_char_event(object &value);

			virtual ~dead_char_event();

			virtual message_event &dispatch() override;
		};

		class normal_key_down_event : public key_down_event{
		public:
			explicit normal_key_down_event(object &value);

			virtual ~normal_key_down_event();

			virtual message_event &dispatch() override;
		};

		class normal_key_up_event : public key_up_event{
		public:
			explicit normal_key_up_event(object &value);

			virtual ~normal_key_up_event();

			virtual message_event &dispatch() override;
		};

		class normal_char_event : public char_event{
		public:
			explicit normal_char_event(object &value);

			virtual ~normal_char_event();

			virtual message_event &dispatch() override;
		};

		class normal_dead_char_event : public dead_char_event{
		public:
			explicit normal_dead_char_event(object &value);

			virtual ~normal_dead_char_event();

			virtual message_event &dispatch() override;
		};

		class system_key_down_event : public key_down_event{
		public:
			explicit system_key_down_event(object &value);

			virtual ~system_key_down_event();

			virtual message_event &dispatch() override;
		};

		class system_key_up_event : public key_up_event{
		public:
			explicit system_key_up_event(object &value);

			virtual ~system_key_up_event();

			virtual message_event &dispatch() override;
		};

		class system_char_event : public char_event{
		public:
			explicit system_char_event(object &value);

			virtual ~system_char_event();

			virtual message_event &dispatch() override;
		};

		class system_dead_char_event : public dead_char_event{
		public:
			explicit system_dead_char_event(object &value);

			virtual ~system_dead_char_event();

			virtual message_event &dispatch() override;
		};

		class mouse_event : public input_event{
		public:
			using message_event::operator=;

			typedef structures::point point_type;
			typedef structures::enumerations::hit_target_type hit_target_type;
			typedef structures::enumerations::mouse_key_state_type mouse_key_state_type;

			explicit mouse_event(object &value);

			virtual ~mouse_event();

			virtual bool is_mouse() const override;

			virtual hit_target_type hit_target() const;

			virtual point_type position() const;
		};

		class mouse_leave_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_leave_event(object &value);

			virtual ~mouse_leave_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_leave_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_client_leave_event(object &value);

			virtual ~mouse_client_leave_event();

			virtual message_event &dispatch() override;
		};

		class mouse_move_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_move_event(object &value);

			virtual ~mouse_move_event();
		};

		class mouse_nc_move_event : public mouse_move_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_move_event(object &value);

			virtual ~mouse_nc_move_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_client_move_event : public mouse_move_event{
		public:
			using message_event::operator=;

			explicit mouse_client_move_event(object &value);

			virtual ~mouse_client_move_event();

			virtual message_event &dispatch() override;
		};

		class mouse_button_down_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_button_down_event(object &value);

			virtual ~mouse_button_down_event();

			virtual mouse_key_state_type button() const = 0;
		};

		class mouse_button_up_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_button_up_event(object &value);

			virtual ~mouse_button_up_event();

			virtual mouse_key_state_type button() const = 0;
		};

		class mouse_button_dbl_click_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_button_dbl_click_event(object &value);

			virtual ~mouse_button_dbl_click_event();

			virtual mouse_key_state_type button() const = 0;
		};

		class mouse_left_button_down_event : public mouse_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_left_button_down_event(object &value);

			virtual ~mouse_left_button_down_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_middle_button_down_event : public mouse_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_middle_button_down_event(object &value);

			virtual ~mouse_middle_button_down_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_right_button_down_event : public mouse_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_right_button_down_event(object &value);

			virtual ~mouse_right_button_down_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_left_button_up_event : public mouse_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_left_button_up_event(object &value);

			virtual ~mouse_left_button_up_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_middle_button_up_event : public mouse_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_middle_button_up_event(object &value);

			virtual ~mouse_middle_button_up_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_right_button_up_event : public mouse_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_right_button_up_event(object &value);

			virtual ~mouse_right_button_up_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_left_button_dbl_click_event : public mouse_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_left_button_dbl_click_event(object &value);

			virtual ~mouse_left_button_dbl_click_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_middle_button_dbl_click_event : public mouse_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_middle_button_dbl_click_event(object &value);

			virtual ~mouse_middle_button_dbl_click_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_right_button_dbl_click_event : public mouse_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_right_button_dbl_click_event(object &value);

			virtual ~mouse_right_button_dbl_click_event();

			virtual mouse_key_state_type button() const override;
		};

		class mouse_nc_left_button_down_event : public mouse_left_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_left_button_down_event(object &value);

			virtual ~mouse_nc_left_button_down_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_middle_button_down_event : public mouse_middle_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_middle_button_down_event(object &value);

			virtual ~mouse_nc_middle_button_down_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_right_button_down_event : public mouse_right_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_right_button_down_event(object &value);

			virtual ~mouse_nc_right_button_down_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_left_button_up_event : public mouse_left_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_left_button_up_event(object &value);

			virtual ~mouse_nc_left_button_up_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_middle_button_up_event : public mouse_middle_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_middle_button_up_event(object &value);

			virtual ~mouse_nc_middle_button_up_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_right_button_up_event : public mouse_right_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_right_button_up_event(object &value);

			virtual ~mouse_nc_right_button_up_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_left_button_dbl_click_event : public mouse_left_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_left_button_dbl_click_event(object &value);

			virtual ~mouse_nc_left_button_dbl_click_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_middle_button_dbl_click_event : public mouse_middle_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_middle_button_dbl_click_event(object &value);

			virtual ~mouse_nc_middle_button_dbl_click_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_nc_right_button_dbl_click_event : public mouse_right_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_nc_right_button_dbl_click_event(object &value);

			virtual ~mouse_nc_right_button_dbl_click_event();

			virtual message_event &dispatch() override;

			virtual hit_target_type hit_target() const override;
		};

		class mouse_client_left_button_down_event : public mouse_left_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_client_left_button_down_event(object &value);

			virtual ~mouse_client_left_button_down_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_middle_button_down_event : public mouse_middle_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_client_middle_button_down_event(object &value);

			virtual ~mouse_client_middle_button_down_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_right_button_down_event : public mouse_right_button_down_event{
		public:
			using message_event::operator=;

			explicit mouse_client_right_button_down_event(object &value);

			virtual ~mouse_client_right_button_down_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_left_button_up_event : public mouse_left_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_client_left_button_up_event(object &value);

			virtual ~mouse_client_left_button_up_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_middle_button_up_event : public mouse_middle_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_client_middle_button_up_event(object &value);

			virtual ~mouse_client_middle_button_up_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_right_button_up_event : public mouse_right_button_up_event{
		public:
			using message_event::operator=;

			explicit mouse_client_right_button_up_event(object &value);

			virtual ~mouse_client_right_button_up_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_left_button_dbl_click_event : public mouse_left_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_client_left_button_dbl_click_event(object &value);

			virtual ~mouse_client_left_button_dbl_click_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_middle_button_dbl_click_event : public mouse_middle_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_client_middle_button_dbl_click_event(object &value);

			virtual ~mouse_client_middle_button_dbl_click_event();

			virtual message_event &dispatch() override;
		};

		class mouse_client_right_button_dbl_click_event : public mouse_right_button_dbl_click_event{
		public:
			using message_event::operator=;

			explicit mouse_client_right_button_dbl_click_event(object &value);

			virtual ~mouse_client_right_button_dbl_click_event();

			virtual message_event &dispatch() override;
		};

		class mouse_wheel_event : public mouse_event{
		public:
			using message_event::operator=;

			explicit mouse_wheel_event(object &value);

			virtual ~mouse_wheel_event();

			virtual short delta() const;

			virtual bool is_vertical() const = 0;
		};

		class mouse_vertical_wheel_event : public mouse_wheel_event{
		public:
			using message_event::operator=;

			explicit mouse_vertical_wheel_event(object &value);

			virtual ~mouse_vertical_wheel_event();

			virtual message_event &dispatch() override;

			virtual bool is_vertical() const override;
		};

		class mouse_horizontal_wheel_event : public mouse_wheel_event{
		public:
			using message_event::operator=;

			explicit mouse_horizontal_wheel_event(object &value);

			virtual ~mouse_horizontal_wheel_event();

			virtual message_event &dispatch() override;

			virtual bool is_vertical() const override;
		};

		GRAFEEX_MAKE_OPERATORS(key_event::state)
	}
}

#endif /* !GRAFEEX_INPUT_MESSAGE_EVENT_H */
