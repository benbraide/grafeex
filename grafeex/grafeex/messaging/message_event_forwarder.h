#pragma once

#ifndef GRAFEEX_MESSAGE_EVENT_FORWARDER_H
#define GRAFEEX_MESSAGE_EVENT_FORWARDER_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class event_forwarder_base{
		public:
			virtual ~event_forwarder_base() = default;

			virtual void forward(message_event &object) = 0;
		};

		template <class event_type>
		class event_forwarder : public event_forwarder_base{
		public:
			virtual ~event_forwarder() = default;

			virtual void forward(message_event &object) override{
				event_type(const_cast<messaging::object &>(object.get_object())).dispatch();
			}
		};
	}
}

#endif /* !GRAFEEX_MESSAGE_EVENT_FORWARDER_H */
