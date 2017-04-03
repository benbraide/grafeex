#pragma once

#ifndef GRAFEEX_MENU_GROUP_H
#define GRAFEEX_MENU_GROUP_H

#include "../wrappers/menu_wrapper.h"

#include "basic_menu_tree.h"
#include "menu_item.h"

namespace grafeex{
	namespace menu{
		class group : public basic_tree{
		public:
			typedef gui::object_tree base_type;
			
			typedef gui::object_tree::traverser_type traverser_type;
			typedef gui::object_tree::const_traverser_type const_traverser_type;

			typedef gui::object_tree::index_type index_type;
			typedef gui::object_tree::size_type size_type;

			typedef gui::object_tree::child_type child_type;
			typedef gui::object_tree::sibling_type sibling_type;

			group();

			explicit group(gui_object_type &parent);

			explicit group(const sibling_type &sibling);

			virtual ~group();

			virtual group &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual group &drag(const size_type &value) override;

			virtual point_type compute_alignment(alignment_type value, const size_type &delta) const override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type type() const override;

			virtual native_type native_value() const override;

			virtual index_type get_child_menu_index(const child_type &child) const override;

			virtual id_type generate_id() override;

			virtual bool create(gui_object_type &parent);

			virtual bool create(const sibling_type &sibling);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual index_type get_item_index_in_parent() const;

		protected:
			virtual void remove_parent_() override;

			virtual void insert_into_parent_(gui_object_type &parent);

			virtual void insert_into_parent_(const sibling_type &sibling);

			virtual bool destroy_(bool force);
		};
	}
}

#endif /* !GRAFEEX_MENU_GROUP_H */
