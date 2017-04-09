#pragma once

#ifndef GRAFEEX_DIMENSIONS_MESSAGE_EVENT_H
#define GRAFEEX_DIMENSIONS_MESSAGE_EVENT_H

#include "message_event.h"
#include "../structures/ref_rect_structure.h"

namespace grafeex{
	namespace messaging{
		class position_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::WINDOWPOS info_type;

			explicit position_event(object &value);

			virtual ~position_event();

			virtual message_event &dispatch() override;

			virtual info_type &info() const;

			virtual bool is_changing() const = 0;
		};

		class changing_position_event : public position_event{
		public:
			using position_event::operator=;

			explicit changing_position_event(object &value);

			virtual ~changing_position_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;
		};

		class changed_position_event : public position_event{
		public:
			using position_event::operator=;

			explicit changed_position_event(object &value);

			virtual ~changed_position_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;
		};

		class movement_event : public message_event{
		public:
			using message_event::operator=;

			explicit movement_event(object &value);

			virtual ~movement_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const = 0;
		};

		class changing_movement_event : public movement_event{
		public:
			using movement_event::operator=;

			typedef structures::ref_rect info_type;

			explicit changing_movement_event(object &value);

			virtual ~changing_movement_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;

			virtual info_type &dimensions();

		protected:
			info_type info_;
		};

		class changed_movement_event : public movement_event{
		public:
			using movement_event::operator=;

			explicit changed_movement_event(object &value);

			virtual ~changed_movement_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;
		};

		class size_event : public message_event{
		public:
			using message_event::operator=;

			explicit size_event(object &value);

			virtual ~size_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const = 0;
		};

		class changing_size_event : public size_event{
		public:
			using size_event::operator=;

			enum class edge_type{
				nil					= 0,
				left				= WMSZ_LEFT,
				top					= WMSZ_TOP,
				right				= WMSZ_RIGHT,
				bottom				= WMSZ_BOTTOM,
				top_left			= WMSZ_TOPLEFT,
				top_right			= WMSZ_TOPRIGHT,
				bottom_right		= WMSZ_BOTTOMRIGHT,
				bottom_left			= WMSZ_BOTTOMLEFT,
			};

			typedef structures::ref_rect info_type;

			explicit changing_size_event(object &value);

			virtual ~changing_size_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;

			virtual info_type &drag_rect();

			virtual edge_type edge() const;

		protected:
			info_type info_;
		};

		class changed_size_event : public size_event{
		public:
			using size_event::operator=;

			explicit changed_size_event(object &value);

			virtual ~changed_size_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;

			virtual bool minimized() const;

			virtual bool maximized() const;

			virtual bool other_window_restored() const;

			virtual bool other_window_maximized() const;
		};

		class min_max_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::MINMAXINFO info_type;

			explicit min_max_event(object &value);

			virtual ~min_max_event();

			virtual message_event &dispatch() override;

			virtual info_type &info() const;
		};

		class calculate_size_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::BOOL bool_type;
			typedef ::NCCALCSIZE_PARAMS valid_info_type;
			typedef structures::ref_rect non_valid_info_type;

			explicit calculate_size_event(object &value);

			virtual ~calculate_size_event();

			virtual message_event &dispatch() override;

			virtual bool indicate_valid_part() const;

			virtual valid_info_type &valid_info() const;

			virtual non_valid_info_type &non_valid_info();

		protected:
			non_valid_info_type non_valid_info_;
		};

		class size_move_event : public message_event{
		public:
			using message_event::operator=;

			explicit size_move_event(object &value);

			virtual ~size_move_event();

			virtual message_event &dispatch() override;

			virtual bool is_entered() const = 0;
		};

		class enter_size_move_event : public size_move_event{
		public:
			using message_event::operator=;

			explicit enter_size_move_event(object &value);

			virtual ~enter_size_move_event();

			virtual message_event &dispatch() override;

			virtual bool is_entered() const override;
		};

		class exit_size_move_event : public size_move_event{
		public:
			using message_event::operator=;

			explicit exit_size_move_event(object &value);

			virtual ~exit_size_move_event();

			virtual message_event &dispatch() override;

			virtual bool is_entered() const override;
		};

		class query_open_event : public message_event{
		public:
			using message_event::operator=;

			explicit query_open_event(object &value);

			virtual ~query_open_event();

			virtual message_event &dispatch() override;
		};

		class query_drag_icon_event : public message_event{
		public:
			using message_event::operator=;

			explicit query_drag_icon_event(object &value);

			virtual ~query_drag_icon_event();

			virtual message_event &dispatch() override;
		};
	}
}

#endif /* !GRAFEEX_DIMENSIONS_MESSAGE_EVENT_H */
