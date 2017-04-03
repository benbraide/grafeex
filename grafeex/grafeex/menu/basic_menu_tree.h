#pragma once

#ifndef GRAFEEX_BASIC_MENU_TREE_H
#define GRAFEEX_BASIC_MENU_TREE_H

#include "menu_tree.h"

namespace grafeex{
	namespace menu{
		class basic_tree : public gui::object_tree, public tree{
		public:
			typedef gui::object_tree::traverser_type traverser_type;
			typedef gui::object_tree::const_traverser_type const_traverser_type;

			typedef gui::object_tree::index_type index_type;
			typedef gui::object_tree::child_type child_type;

			virtual ~basic_tree();

			virtual tree &traverse_children_absolute(traverser_type traverser) override;

			virtual const tree &traverse_children_absolute(const_traverser_type traverser) const override;

			virtual child_type *get_child_absolute(index_type index) const override;

			virtual index_type get_child_index_absolute(const child_type &child) const override;

			virtual index_type get_child_menu_index(const child_type &child) const override;

			virtual index_type get_children_count_absolute() const override;

			virtual child_type *find_child(id_type id) const override;

		protected:
			virtual child_type *get_child_absolute_(tree_type &tree_child, index_type &child_index, index_type index) const;
		};
	}
}

#endif /* !GRAFEEX_BASIC_MENU_TREE_H */
