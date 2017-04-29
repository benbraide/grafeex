#pragma once

#ifndef GRAFEEX_GUI_OBJECT_TREE_H
#define GRAFEEX_GUI_OBJECT_TREE_H

#include "../common/sequential_generic_tree.h"

#include "gui_generic_object.h"
#include "gui_object_attributes.h"

namespace grafeex{
	namespace messaging{
		class changed_position_event;
		class focus_change_event;
	}

	namespace window{
		class view;
	}

	namespace gui{
		class object_tree : public generic_object, public common::sequential_generic_tree<object, object_sibling>{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;
			typedef common::sequential_generic_tree<object, object_sibling> base_type;

			typedef object::size_type size_type;
			typedef object::sibling_type sibling_type;

			typedef gui::object_attributes attributes_type;
			typedef std::shared_ptr<attributes_type> attributes_ptr_type;

			typedef attributes_type::state attributes_state_type;
			typedef attributes_type::state_type attributes_state_value_type;

			typedef std::list<object_tree *> object_tree_list_type;
			typedef std::unordered_map<attributes_state_value_type, object_tree_list_type> attributes_cache_type;

			virtual ~object_tree();

			virtual object *get_hit_target(const point_type &value) const;

			virtual object *get_deepest_hit_target(const point_type &value) const;

			virtual attributes_type &attributes();

		protected:
			friend class object_attributes;

			friend class messaging::changed_position_event;
			friend class messaging::focus_change_event;

			friend class window::view;

			virtual void attribute_set_(attributes_state_value_type state);

			virtual void attribute_removed_(attributes_state_value_type state);

			virtual void set_attribute_cache_(attributes_state_value_type state, object_tree &target);

			virtual void remove_attribute_cache_(attributes_state_value_type state, object_tree &target);

			virtual void sized_();

			virtual void moved_();

			virtual attributes_ptr_type get_attributes_();

			template <typename attributes_type>
			attributes_ptr_type create_attributes_(){
				if (attributes_ == nullptr)
					attributes_ = std::make_shared<attributes_type>(*this);
				return attributes_;
			}

			attributes_ptr_type attributes_;
			attributes_cache_type attributes_cache_;
			gui_object_type *focused_child_ = nullptr;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_TREE_H */
