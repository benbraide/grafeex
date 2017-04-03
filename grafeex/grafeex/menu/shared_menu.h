#pragma once

#ifndef GRAFEEX_SHARED_MENU_H
#define GRAFEEX_SHARED_MENU_H

#include <list>
#include <memory>

#include "menu_object.h"

namespace grafeex{
	namespace menu{
		class shared : public object{
		public:
			typedef std::shared_ptr<item> item_type;
			typedef std::list<item_type> list_type;

			enum class option{
				nil,
				system,
			};

			explicit shared(const hwnd_type &target, option options = option::nil);

			virtual ~shared();

		protected:
			virtual void populate_items_();

			list_type list_;
		};
	}
}

#endif /* !GRAFEEX_SHARED_MENU_H */
