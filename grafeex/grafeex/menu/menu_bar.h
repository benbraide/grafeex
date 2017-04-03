#pragma once

#ifndef GRAFEEX_MENU_BAR_H
#define GRAFEEX_MENU_BAR_H

#include "menu_object.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace menu{
		class bar : public object{
		public:
			typedef window::object window_type;

			bar();

			explicit bar(window_type &owner);

			virtual ~bar();

			virtual bool create();

			virtual bool create(window_type &owner);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual bar &remove_owner();

			virtual bar &owner(window_type &owner);

			virtual window_type *owner() const;

			virtual bool redraw();

		protected:
			virtual bool update_owner_(window_type *owner);

			virtual bool destroy_(bool force);

			window_type *owner_;
		};
	}
}

#endif /* !GRAFEEX_MENU_BAR_H */
