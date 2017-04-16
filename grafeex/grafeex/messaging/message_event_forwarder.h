#pragma once

#ifndef GRAFEEX_MESSAGE_EVENT_FORWARDER_H
#define GRAFEEX_MESSAGE_EVENT_FORWARDER_H

#include "../window/window_object.h"

namespace grafeex{
	namespace messaging{
		class event_forwarder_base{
		public:
			virtual ~event_forwarder_base() = default;

			virtual void dispatch(message_event &e) = 0;
		};

		template <class event_type, class window_type, class return_type = void>
		class uniform_event_forwarder : public event_forwarder_base{
		public:
			typedef event_type event_type;
			typedef window_type window_type;

			typedef return_type return_type;
			typedef return_type(window_type::*method_type)(event_type &);

			uniform_event_forwarder(method_type method)
				: method_(method){}

			virtual ~uniform_event_forwarder() = default;

			virtual void dispatch(message_event &e) override{
				(dynamic_cast<window_type *>(e.get_object().target())->*method_)(*dynamic_cast<event_type *>(&e));
			}

		private:
			method_type method_;
		};
	}
}

#endif /* !GRAFEEX_MESSAGE_EVENT_FORWARDER_H */
