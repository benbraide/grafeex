#pragma once

#ifndef GRAFEEX_MENU_TREE_H
#define GRAFEEX_MENU_TREE_H

#include "../gui/gui_object_tree.h"

namespace grafeex{
	namespace menu{
		class tree{
		public:
			typedef ::HMENU native_type;
			typedef ::WORD id_type;

			typedef gui::object_tree::traverser_type traverser_type;
			typedef gui::object_tree::const_traverser_type const_traverser_type;

			typedef gui::object_tree::index_type index_type;
			typedef gui::object_tree::size_type size_type;

			typedef gui::object_tree::child_type child_type;

			virtual native_type native_value() const = 0;

			virtual tree &traverse_children_absolute(traverser_type traverser) = 0;

			virtual const tree &traverse_children_absolute(const_traverser_type traverser) const = 0;

			virtual child_type *get_child_absolute(index_type index) const = 0;

			virtual index_type get_child_index_absolute(const child_type &child) const = 0;

			virtual index_type get_child_menu_index(const child_type &child) const = 0;

			virtual index_type get_children_count_absolute() const = 0;

			virtual child_type *find_child(id_type id) const = 0;

			virtual id_type generate_id() = 0;
		};
	}
}

#endif /* !GRAFEEX_MENU_TREE_H */