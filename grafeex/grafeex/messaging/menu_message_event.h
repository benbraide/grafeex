#pragma once

#ifndef GRAFEEX_MENU_MESSAGE_EVENT_H
#define GRAFEEX_MENU_MESSAGE_EVENT_H

#include <memory>

#include "../wrappers/menu_wrapper.h"
#include "message_event.h"

namespace grafeex{
	namespace menu{
		class object;
		class item;
	}

	namespace collections{
		class menu_interface;
	}

	namespace messaging{
		class context_menu_event : public message_event{
		public:
			using message_event::operator=;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type native_hwnd_type;

			typedef structures::point point_type;
			typedef collections::menu_interface menu_type;

			typedef std::shared_ptr<menu_type> menu_ptr_type;

			explicit context_menu_event(object &value);

			virtual ~context_menu_event();

			virtual message_event &dispatch() override;

			virtual window_type *target() const;

			virtual menu_type &menu();

			virtual point_type mouse_position() const;

		protected:
			menu_ptr_type menu_;
		};

		class menu_init_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			explicit menu_init_event(object &value);

			virtual ~menu_init_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;
		};

		class menu_popup_init_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			typedef ::BOOL bool_type;

			explicit menu_popup_init_event(object &value);

			virtual ~menu_popup_init_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual bool is_window() const;
		};

		class menu_popup_uninit_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			explicit menu_popup_uninit_event(object &value);

			virtual ~menu_popup_uninit_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual bool is_window() const;
		};

		class menu_next_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type hwnd_native_type;

			typedef ::MDINEXTMENU info_type;

			explicit menu_next_event(object &value);

			virtual ~menu_next_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual menu_type *current() const;

			virtual menu_next_event &next(menu_handle_type value);

			virtual menu_type *next() const;

			virtual menu_next_event &message_target(hwnd_native_type value);

			virtual window_type *message_target() const;

			virtual unsigned short key_code() const;

			virtual bool is_left() const;
		};

		class menu_rbutton_up_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;
			typedef menu::item menu_item_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			typedef structures::point point_type;
			typedef collections::menu_interface menu_collection_type;

			typedef std::shared_ptr<menu_collection_type> menu_ptr_type;

			explicit menu_rbutton_up_event(object &value);

			virtual ~menu_rbutton_up_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual menu_item_type *item() const;

			virtual menu_collection_type &context_menu();

			virtual point_type mouse_position() const;

		protected:
			menu_ptr_type menu_;
		};

		class menu_command_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;
			typedef menu::item menu_item_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			explicit menu_command_event(object &value);

			virtual ~menu_command_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual menu_item_type *item() const;
		};

		class menu_select_event : public message_event{
		public:
			using message_event::operator=;

			typedef menu::object menu_type;
			typedef menu::item menu_item_type;

			typedef wrappers::menu menu_wrapper_type;
			typedef wrappers::menu::value_type menu_handle_type;

			explicit menu_select_event(object &value);

			virtual ~menu_select_event();

			virtual message_event &dispatch() override;

			virtual menu_type *menu() const;

			virtual menu_item_type *item() const;

			virtual bool is_window() const;
		};
	}
}

#endif /* !GRAFEEX_MENU_MESSAGE_EVENT_H */
