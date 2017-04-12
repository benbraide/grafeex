#pragma once

#ifndef GRAFEEX_BUTTON_CONTROL_H
#define GRAFEEX_BUTTON_CONTROL_H

#include "control_object.h"
#include "../messaging/command_message_event_handler.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class button : public object, public messaging::button_command_event_handler{
			public:

			};
		}
	}
}

#endif /* !GRAFEEX_BUTTON_CONTROL_H */
