#pragma once

#ifndef GRAFEEX_TOOL_TIP_COLLECTION_INTERFACE_H
#define GRAFEEX_TOOL_TIP_COLLECTION_INTERFACE_H

#include "../controls/tool_tip_control.h"

#define GCTTC_ARGS callback_type callback
#define GCTTC_ARGS2 const rect_type &bounding_rect
#define GCTTC_ARGS3 GCTTC_ARGS2, GCTTC_ARGS

namespace grafeex{
	namespace collections{
		class tool_tip_interface{
		public:
			typedef window::controls::tool_tip_item item_type;

			typedef events::tunnel<std::wstring> string_event_type;
			typedef string_event_type::callback_type string_callback_type;

			typedef std::function<void(item_type &)> callback_type;

			typedef gui::object gui_object_type;
			typedef structures::rect rect_type;

			typedef std::size_t size_type;
			
			virtual ~tool_tip_interface() = default;

			virtual tool_tip_interface &item(gui_object_type &owner, const std::wstring &value, GCTTC_ARGS = nullptr) = 0;

			virtual tool_tip_interface &item(gui_object_type &owner, const std::wstring &value, GCTTC_ARGS3 = nullptr) = 0;

			virtual tool_tip_interface &item(gui_object_type &owner, string_callback_type string_callback, GCTTC_ARGS = nullptr) = 0;

			virtual tool_tip_interface &item(gui_object_type &owner, string_callback_type string_callback, GCTTC_ARGS3 = nullptr) = 0;

			virtual item_type *get_item(size_type index) const = 0;

			virtual item_type *get_first_item() const = 0;

			virtual item_type *get_last_item() const = 0;

			virtual size_type count() const = 0;

			virtual bool empty() const = 0;
		};
	}
}

#endif /* !GRAFEEX_TOOL_TIP_COLLECTION_INTERFACE_H */
