#pragma once

#ifndef GRAFEEX_GUI_COLUMN_H
#define GRAFEEX_GUI_COLUMN_H

#include "gui_grid_member.h"
#include "gui_object_tree.h"
#include "gui_object_attributes.h"
#include "gui_column_interface.h"

namespace grafeex{
	namespace gui{
		template <class my_base_type>
		class column : public my_base_type, public column_interface, public grid_member{
		public:
			typedef gui::object gui_object_type;
			typedef gui::object_sibling gui_object_sibling_type;

			typedef gui::object::rect_type rect_type;
			typedef gui::object_attributes::alignment_type alignment_type;
			typedef gui::object_attributes::state_type state_type;

			column(){}

			template <typename... optional_types>
			explicit column(gui_object_type &parent, optional_types... optional_values){
				create(parent, optional_values...);
			}

			template <typename... optional_types>
			explicit column(const gui_object_sibling_type &sibling, optional_types... optional_values){
				create(sibling, optional_values...);
			}

			virtual ~column(){
				my_base_type::destroy();
			}

			virtual column &dimensions(const rect_type &value, bool inner = false) override{
				my_base_type::dimensions(value, inner);
				refresh();
				return *this;
			}

			virtual int compute_fixed_width(int width) const override{
				return 0;
			}

			virtual int compute_fixed_height(int height) const override{
				return 0;
			}

			virtual bool is_fixed() const override{
				return false;
			}

			virtual void refresh() override{
				if (my_base_type::parent_ != nullptr)
					dynamic_cast<grid_member *>(my_base_type::parent_)->refresh();
			}

			template <typename... optional_types>
			bool create(gui_object_type &parent, optional_types... optional_values){
				if (my_base_type::is_created())
					return false;

				my_base_type::insert_into_parent_(parent);
				return my_base_type::create_(optional_values...);
			}

			template <typename... optional_types>
			bool create(const gui_object_sibling_type &sibling, optional_types... optional_values){
				if (my_base_type::is_created())
					return false;

				my_base_type::insert_into_parent_(sibling);
				return my_base_type::create_(optional_values...);
			}

		protected:
			virtual void dimensions_(const rect_type &value) override{
				my_base_type::dimensions(value, false);
			}
		};
	}
}

#endif /* !GRAFEEX_GUI_COLUMN_H */
