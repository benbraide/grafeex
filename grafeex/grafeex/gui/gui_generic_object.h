#pragma once

#ifndef GRAFEEX_GUI_GENERIC_OBJECT_H
#define GRAFEEX_GUI_GENERIC_OBJECT_H

#include "../common/generic_tree.h"
#include "gui_object_sibling.h"

namespace grafeex{
	namespace gui{
		class generic_object : public object{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;

			typedef object::size_type size_type;
			typedef object::sibling_type sibling_type;

			virtual ~generic_object();

			virtual object *non_sibling() override;

			virtual object *parent() const override;

			virtual object &traverse_siblings(sibling_traverser_type traverser) override;

			virtual const object &traverse_siblings(const_sibling_traverser_type traverser) const override;

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual object &size(const size_type &value, bool inner = false) override;

			virtual size_type size(bool inner = false) const override;

			virtual object &offset(const size_type &value) override;

			virtual point_type offset() const override;

			virtual object &move(const point_type &value) override;

			virtual object &drag(const size_type &value) override;

			virtual object &align(alignment_type value, const size_type &delta = {}) override;

			virtual point_type compute_alignment(alignment_type value, const size_type &delta = {}) const override;

			virtual hit_target_type test(const point_type &value) const override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type type() const override;

		protected:
			object *parent_ = nullptr;
		};
	}
}

#endif /* !GRAFEEX_GUI_GENERIC_OBJECT_H */
