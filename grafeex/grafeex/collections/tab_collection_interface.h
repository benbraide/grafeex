#pragma once

#ifndef GRAFEEX_TAB_COLLECTION_INTERFACE_H
#define GRAFEEX_TAB_COLLECTION_INTERFACE_H

#include "../gui/gui_object_tree.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace collections{
		class tab_interface{
		public:
			typedef window::object item_type;
			typedef gui::object_tree::index_type index_type;

			typedef std::function<void(item_type &)> callback_type;

			virtual ~tab_interface() = default;

			virtual tab_interface &item(const std::wstring &title, callback_type callback) = 0;

			virtual tab_interface &dialog(const std::wstring &title, callback_type callback) = 0;

			virtual item_type *get_item(index_type index) const = 0;

			virtual item_type *get_first_item() const = 0;

			virtual item_type *get_last_item() const = 0;

			virtual index_type count() const = 0;

			virtual bool empty() const = 0;
		};
	}
}

#endif /* !GRAFEEX_TAB_COLLECTION_INTERFACE_H */
