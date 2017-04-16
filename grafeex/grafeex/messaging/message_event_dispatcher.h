#pragma once

#ifndef GRAFEEX_MESSAGE_EVENT_DISPATCHER_H
#define GRAFEEX_MESSAGE_EVENT_DISPATCHER_H

#include <memory>
#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class event_dispatcher_base{
		public:
			virtual ~event_dispatcher_base() = default;

			virtual void dispatch(object &object) = 0;
		};

		template <class event_type>
		class event_dispatcher : public event_dispatcher_base{
		public:
			virtual ~event_dispatcher() = default;

			virtual void dispatch(object &object) override{
				event_type(object).dispatch();
			}
		};
	}
}

#endif /* !GRAFEEX_MESSAGE_EVENT_DISPATCHER_H */
