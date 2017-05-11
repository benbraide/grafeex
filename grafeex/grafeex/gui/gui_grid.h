#pragma once

#ifndef GRAFEEX_GUI_GRID_H
#define GRAFEEX_GUI_GRID_H

#include "gui_row.h"

namespace grafeex{
	namespace gui{
		class grid : public box<object_tree>, public grid_member{
		public:
			typedef box<object_tree> base_type;

			using base_type::dimensions;

			struct row_info{
				row *object;
				bool is_fixed;
				long height;
			};

			typedef std::vector<row_info> cache_type;

			grid();

			explicit grid(gui_object_type &parent);

			explicit grid(const sibling_type &sibling);

			virtual ~grid();

			virtual grid &dimensions(const rect_type &value, bool inner = false) override;

			virtual grid &padding(const rect_type &value) override;

			virtual void refresh() override;

			virtual bool create(gui_object_type &parent);

			virtual bool create(const sibling_type &sibling);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual bool is_fixed() const;

		protected:
			virtual void sized_() override;

			virtual void refresh_();

			template <typename arg_type>
			bool create_(arg_type arg){
				if (is_created())
					return false;

				insert_into_parent_(arg);
				if (!is_fixed()){
					attributes().fill_parent(true);
					attributes().align(true, alignment_type::center | alignment_type::vertical_center);
				}

				refresh();
				return true;
			}
		};
	}
}

#endif /* !GRAFEEX_GUI_GRID_H */
