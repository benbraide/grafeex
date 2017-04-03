#pragma once

#ifndef GRAFEEX_MENU_MESSAGE_EVENT_HANDLER_H
#define GRAFEEX_MENU_MESSAGE_EVENT_HANDLER_H

#include "../application/application_object.h"

namespace grafeex{
	namespace messaging{
		class menu_event_handler{
		public:
			virtual ~menu_event_handler();

		protected:
			friend class context_menu_event;
			friend class menu_init_event;
			friend class menu_popup_init_event;
			friend class menu_popup_uninit_event;
			friend class menu_next_event;
			friend class menu_rbutton_up_event;
			friend class menu_command_event;
			friend class menu_select_event;

			virtual void on_context_menu(context_menu_event &e);

			virtual void on_menu_init(menu_init_event &e);

			virtual void on_menu_popup_init(menu_popup_init_event &e);

			virtual void on_menu_popup_uninit(menu_popup_uninit_event &e);

			virtual void on_menu_next(menu_next_event &e);

			virtual void on_menu_rbutton_up(menu_rbutton_up_event &e);

			virtual void on_menu_select(menu_command_event &e);

			virtual void on_menu_highlight(menu_select_event &e);
		};
	}
}

#endif /* !GRAFEEX_MENU_MESSAGE_EVENT_HANDLER_H */
