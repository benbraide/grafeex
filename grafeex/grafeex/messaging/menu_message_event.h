#pragma once

#ifndef GRAFEEX_MENU_MESSAGE_EVENT_H
#define GRAFEEX_MENU_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class context_menu_event : public message_event{
		public:
			using message_event::operator=;

			typedef structures::point point_type;

			explicit context_menu_event(object &value);

			virtual ~context_menu_event();

			virtual message_event &dispatch() override;

			virtual window_type *target() const;

			virtual point_type mouse_position() const;

		protected:
			virtual message_event &write_bool_(bool value) override;
		};
	}
}

#endif /* !GRAFEEX_MENU_MESSAGE_EVENT_H */
