#pragma once

#ifndef GRAFEEX_GUI_ROW_H
#define GRAFEEX_GUI_ROW_H

#include <vector>

#include "gui_column.h"
#include "gui_box.h"

namespace grafeex{
	namespace gui{
		class row : public box<object_tree>, public grid_member{
		public:
			typedef box<object_tree> base_type;

			using base_type::dimensions;

			struct column_info{
				column_interface *object;
				bool is_fixed;
				long width;
			};

			typedef std::vector<column_info> cache_type;

			row();

			explicit row(gui_object_type &parent);

			explicit row(const sibling_type &sibling);

			virtual ~row();

			virtual row &dimensions(const rect_type &value, bool inner = false) override;

			virtual row &padding(const rect_type &value) override;

			virtual void refresh() override;

			virtual bool create(gui_object_type &parent);

			virtual bool create(const sibling_type &sibling);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual int compute_fixed_width(int width) const;

			virtual int compute_fixed_height(int height) const;

			virtual bool is_fixed() const;

		protected:
			friend class grid;

			virtual void sized_() override;

			virtual void dimensions_(const rect_type &value);

			virtual void refresh_();
		};
	}
}

#endif /* !GRAFEEX_GUI_ROW_H */
