#pragma once

#ifndef GRAFEEX_SHARED_MENU_H
#define GRAFEEX_SHARED_MENU_H

#include <list>
#include <memory>

#include "menu_object.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace menu{
		class shared : public object{
		public:
			typedef window::object window_type;

			typedef std::shared_ptr<item> item_type;
			typedef std::list<item_type> list_type;

			enum class option{
				nil,
				system,
			};

			explicit shared(const hwnd_type &target, option options = option::nil);

			explicit shared(window_type &target, option options = option::nil);

			virtual ~shared();

		protected:
			virtual void remove_(object::child_type &child) override;

			virtual void populate_items_();

			list_type list_;
		};
	}
}

#endif /* !GRAFEEX_SHARED_MENU_H */
