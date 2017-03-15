#pragma once

#ifndef GRAFEEX_GUI_OBJECT_H
#define GRAFEEX_GUI_OBJECT_H

#include <functional>

#include "../structures/rect_structure.h"
#include "../structures/enumerations.h"

namespace grafeex{
	namespace gui{
		class object_sibling;

		class object{
		public:
			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::rect rect_type;

			typedef structures::rect::origin_type alignment_type;
			typedef structures::enumerations::hit_target_type hit_target_type;

			typedef std::function<bool(object_sibling &)> sibling_traverser_type;
			typedef std::function<bool(const object_sibling &)> const_sibling_traverser_type;

			enum class object_type{
				unspecified,
				windowed,
				non_windowed,
				menu,
			};

			virtual ~object(){}

			virtual object *non_sibling() = 0;

			virtual const object *parent() const = 0;

			virtual object *parent() = 0;

			virtual object &traverse_siblings(sibling_traverser_type traverser) = 0;

			virtual const object &traverse_siblings(const_sibling_traverser_type traverser) const = 0;

			virtual object &dimensions(const rect_type &value, bool inner = false) = 0;

			virtual rect_type dimensions(bool inner = false) const = 0;

			virtual object &size(const size_type &value, bool inner = false) = 0;

			virtual size_type size(bool inner = false) const = 0;

			virtual object &offset(const size_type &value) = 0;

			virtual point_type offset() const = 0;

			virtual object &drag(const size_type &value) = 0;

			virtual object &move(const point_type &value) = 0;

			virtual object &align(alignment_type value, const size_type &delta = {}) = 0;

			virtual hit_target_type test(const point_type &value) const = 0;

			virtual point_type convert_to_screen(const point_type &value) const = 0;

			virtual rect_type convert_to_screen(const rect_type &value) const = 0;

			virtual point_type convert_from_screen(const point_type &value) const = 0;

			virtual rect_type convert_from_screen(const rect_type &value) const = 0;

			virtual object_type type() const = 0;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_H */
