#pragma once

#ifndef GRAFEEX_GUI_OBJECT_TREE_H
#define GRAFEEX_GUI_OBJECT_TREE_H

#include "../common/sequential_generic_tree.h"
#include "gui_object_sibling.h"

namespace grafeex{
	namespace gui{
		class object_tree : public object, common::sequential_generic_tree<object, object_sibling>{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;
			typedef common::sequential_generic_tree<object, object_sibling> base_type;
			typedef object::size_type size_type;

			virtual ~object_tree();

			virtual object *non_sibling() override;

			virtual const object *parent() const override;

			virtual object *parent() override;

			virtual object &traverse_siblings(sibling_traverser_type traverser) override;

			virtual const object &traverse_siblings(const_sibling_traverser_type traverser) const override;

			virtual hit_target_type test(const point_type &value) const override;

			virtual const object *get_hit_target(const point_type &value) const;

			virtual object *get_hit_target(const point_type &value);

			virtual const object *get_deepest_hit_target(const point_type &value) const;

			virtual object *get_deepest_hit_target(const point_type &value);

		protected:
			object *parent_ = nullptr;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_TREE_H */
