#pragma once

#ifndef GRAFEEX_MENU_POPUP_H
#define GRAFEEX_MENU_POPUP_H

#include "menu_object.h"

namespace grafeex{
	namespace menu{
		class popup : public object{
		public:
			popup();

			explicit popup(item &owner);

			virtual ~popup();

			virtual bool track(const hwnd_type &owner, const point_type &offset, track_option options = track_option::left_align) override;

			virtual bool create();

			virtual bool create(item &owner);

			virtual bool destroy() override;

			virtual bool is_created() const;

			virtual popup &remove_owner();

			virtual popup &owner(item &owner);

			virtual item *owner() const;

		protected:
			friend class item;

			virtual bool update_owner_(item *owner);

			virtual bool destroy_(bool force);

			item *owner_;
		};
	}
}

#endif /* !GRAFEEX_MENU_POPUP_H */
