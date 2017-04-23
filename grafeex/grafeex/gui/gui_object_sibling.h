#pragma once

#ifndef GRAFEEX_GUI_OBJECT_SIBLING_H
#define GRAFEEX_GUI_OBJECT_SIBLING_H

#include "../common/generic_tree.h"
#include "gui_object.h"

namespace grafeex{
	namespace gui{
		class object_sibling : public object{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;
			typedef tree_type::index_type index_type;

			enum class sibling_value_type{
				previous,
				next,
			};

			object_sibling();

			object_sibling(const object &value, sibling_value_type type);

			object_sibling(object &value, sibling_value_type type);

			virtual ~object_sibling();

			virtual object *non_sibling() override;

			virtual object *parent() const override;

			virtual object &traverse_siblings(sibling_traverser_type traverser) override;

			virtual const object &traverse_siblings(const_sibling_traverser_type traverser) const override;

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual rect_type relative_dimensions() const override;

			virtual object &size(const size_type &value, bool inner = false) override;

			virtual size_type size(bool inner = false) const override;

			virtual object &offset(const size_type &value) override;

			virtual point_type offset() const override;

			virtual object &drag(const size_type &value) override;

			virtual object &move(const point_type &value) override;

			virtual object &align(alignment_type value, const size_type &delta = {}) override;

			virtual point_type compute_alignment(alignment_type value, const size_type &delta = {}) const override;

			virtual hit_target_type test(const point_type &value) const override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type type() const override;

			virtual event_tunnel &events() override;

			virtual bool is_previous() const;

			virtual index_type get_insert_index() const;

		protected:
			virtual void remove_parent_() override;

			object *value_;
			sibling_value_type type_;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_SIBLING_H */
