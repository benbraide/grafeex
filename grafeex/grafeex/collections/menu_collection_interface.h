#pragma once

#ifndef GRAFEEX_MENU_COLLECTION_INTERFACE_H
#define GRAFEEX_MENU_COLLECTION_INTERFACE_H

#include "../menu/menu_object.h"

#define GCMI_ITEM_BASIC		const std::wstring &value, void_callback_type callback
#define GCMI_ITEM_BASIC2	const std::wstring &value, void_no_args_callback_type callback
#define GCMI_ITEM_BASIC3	const std::wstring &value, callback_type callback

#define GCMI_ITEM_SUB		const std::wstring &value, sub_callback_type callback

#define GCMI_OWNER_DRAW		void_callback_type draw_callback, void_callback_type measure_callback
#define GCMI_APPEND_INDEX	index_type index = static_cast<index_type>(-1)
#define GCMI_APPEND_VALUE	static_cast<index_type>(-1)

namespace grafeex{
	namespace collections{
		class menu_interface{
		public:
			typedef gui::object gui_object_type;
			typedef grafeex::menu::object::index_type index_type;
			typedef grafeex::menu::object::event_tunnel::void_callback_type void_callback_type;
			typedef grafeex::menu::object::event_tunnel::void_no_args_callback_type void_no_args_callback_type;

			typedef std::function<void(menu_interface &)> sub_callback_type;

			virtual ~menu_interface() = default;

			virtual menu_interface &set_new_line(bool bordered = false) = 0;

			virtual menu_interface &clear_new_line() = 0;

			virtual menu_interface &item(GCMI_ITEM_BASIC, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &item(GCMI_ITEM_BASIC2, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &item(void_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &item(void_no_args_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &check(GCMI_ITEM_BASIC, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &check(GCMI_ITEM_BASIC2, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &check(void_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &check(void_no_args_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &separator(GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &separator(GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &sub(GCMI_ITEM_SUB, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &sub(sub_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) = 0;

			virtual menu_interface &group(sub_callback_type callback, GCMI_APPEND_INDEX) = 0;

			virtual gui_object_type *get_item(index_type index) const = 0;

			virtual gui_object_type *get_first_item() const = 0;

			virtual gui_object_type *get_last_item() const = 0;

			virtual index_type count() const = 0;

			virtual bool empty() const = 0;

			virtual bool is_new_line() const = 0;
		};
	}
}

#endif /* !GRAFEEX_MENU_COLLECTION_INTERFACE_H */
