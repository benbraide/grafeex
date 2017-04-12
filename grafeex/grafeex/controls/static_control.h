#pragma once

#ifndef GRAFEEX_STATIC_CONTROL_H
#define GRAFEEX_STATIC_CONTROL_H

#include "control_object.h"
#include "../messaging/command_message_event_handler.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class static_control : public object, public messaging::static_command_event_handler{
			public:
				
			};
		}
	}
}

#endif /* !GRAFEEX_STATIC_CONTROL_H */
