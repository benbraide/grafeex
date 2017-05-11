#pragma once

#ifndef GRAFEEX_NON_WINDOW_OBJECT_H
#define GRAFEEX_NON_WINDOW_OBJECT_H

#include "../gui/gui_box.h"

namespace grafeex{
	namespace non_window{
		class object : public gui::box<gui::object_tree>{
		public:
			typedef gui::box<gui::object_tree> base_type;

			using base_type::dimensions;
			using base_type::padding;

			enum class state : unsigned int{
				nil				= (0 << 0x0000),
				dirty			= (1 << 0x0000),
				visible			= (1 << 0x0001),
				minimized		= (1 << 0x0002),
				maximized		= (1 << 0x0003),
			};

			object();

			object(gui_object_type &parent, const rect_type &dimensions, const rect_type &padding = {});

			object(const sibling_type &sibling, const rect_type &dimensions, const rect_type &padding = {});

			virtual ~object();

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual object &padding(const rect_type &value) override;

			virtual object &paint();

			virtual object &paint(const rect_type &bounding_rect);

			virtual bool create(gui_object_type &parent, const rect_type &dimensions, const rect_type &padding = {});

			virtual bool create(const sibling_type &sibling, const rect_type &dimensions, const rect_type &padding = {});

			virtual bool destroy();

			virtual bool is_created() const;

		protected:
			virtual void sized_() override;

			virtual bool create_(const rect_type &dimensions, const rect_type &padding);

			virtual void paint_(const rect_type &bounding_rect);

			virtual void clear_();

			state states_;
		};

		GRAFEEX_MAKE_OPERATORS(object::state)
	}
}

#endif /* !GRAFEEX_NON_WINDOW_OBJECT_H */
