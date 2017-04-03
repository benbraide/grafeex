#pragma once

#ifndef GRAFEEX_MENU_CHECK_ITEM_H
#define GRAFEEX_MENU_CHECK_ITEM_H

#include "menu_item.h"

namespace grafeex{
	namespace menu{
		class check_item : public item{
		public:
			class event_tunnel : public item::event_tunnel{
			public:
				event_tunnel();

				virtual ~event_tunnel();

				GGGO_VOID_EVENT2(checked)
				GGGO_VOID_EVENT2(unchecked)

				void_event_type checked_event_;
				void_event_type unchecked_event_;
			};

			explicit check_item(option options = option::nil);

			check_item(gui_object_type &parent, const std::wstring &value, option options = option::nil);

			check_item(const sibling_type &sibling, const std::wstring &value, option options = option::nil);

			virtual ~check_item();

			virtual event_tunnel &events() override;

			virtual check_item &toggle();

		protected:
			friend class messaging::menu_command_event;

			virtual events_type get_events_() override;

			virtual void on_checked(messaging::menu_command_event &e);

			virtual void on_unchecked(messaging::menu_command_event &e);
		};
	}
}

#endif /* !GRAFEEX_MENU_CHECK_ITEM_H */
