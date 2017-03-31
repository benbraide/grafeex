#pragma once

#ifndef GRAFEEX_GUI_OBJECT_TREE_H
#define GRAFEEX_GUI_OBJECT_TREE_H

#include "../common/sequential_generic_tree.h"
#include "gui_generic_object.h"

namespace grafeex{
	namespace gui{
		class object_tree : public generic_object, public common::sequential_generic_tree<object, object_sibling>{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;
			typedef common::sequential_generic_tree<object, object_sibling> base_type;

			typedef object::size_type size_type;
			typedef object::sibling_type sibling_type;

			virtual ~object_tree();

			virtual const object *get_hit_target(const point_type &value) const;

			virtual object *get_hit_target(const point_type &value);

			virtual const object *get_deepest_hit_target(const point_type &value) const;

			virtual object *get_deepest_hit_target(const point_type &value);
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_TREE_H */
