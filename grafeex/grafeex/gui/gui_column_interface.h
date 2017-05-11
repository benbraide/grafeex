#pragma once

#ifndef GRAFEEX_GUI_COLUMN_INTERFACE_H
#define GRAFEEX_GUI_COLUMN_INTERFACE_H

#include "gui_object.h"

namespace grafeex{
	namespace gui{
		class column_interface{
		public:
			typedef gui::object::rect_type rect_type;

			virtual ~column_interface() = default;

			virtual int compute_fixed_width(int width) const = 0;

			virtual int compute_fixed_height(int height) const = 0;

			virtual bool is_fixed() const = 0;

		protected:
			friend class row;

			virtual void dimensions_(const rect_type &value) = 0;
		};
	}
}

#endif /* !GRAFEEX_GUI_COLUMN_INTERFACE_H */
