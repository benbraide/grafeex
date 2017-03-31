#pragma once

#ifndef GRAFEEX_MENU_SEPARATOR_H
#define GRAFEEX_MENU_SEPARATOR_H

#include "menu_item.h"

namespace grafeex{
	namespace menu{
		class separator : public item{
		public:
			separator();

			explicit separator(gui_object_type &parent);

			explicit separator(const sibling_type &sibling);

			virtual ~separator();

			virtual item &select();

			virtual item &enable(bool value = true);

			virtual item &gray();

			virtual item &check(bool value = true);

			virtual item &set_as_default();

			virtual bool is_action() const;

			virtual bool is_separator() const;

			virtual bool create(gui_object_type &parent);

			virtual bool create(const sibling_type &sibling);

		protected:
			virtual bool create_(index_type index, const std::wstring &value) override;

			virtual bool create_(index_type index);
		};
	}
}

#endif /* !GRAFEEX_MENU_SEPARATOR_H */
