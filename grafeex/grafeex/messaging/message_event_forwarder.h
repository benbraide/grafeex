#pragma once

#ifndef GRAFEEX_MESSAGE_EVENT_FORWARDER_H
#define GRAFEEX_MESSAGE_EVENT_FORWARDER_H

#include "../window/window_object.h"

namespace grafeex{
	namespace messaging{
		template <class control_type>
		class uniform_event_forwarder : public event_dispatcher_base{
		public:
			typedef ::NMHDR notify_info_type;

			typedef window::object window_type;
			typedef control_type control_type;
			typedef void(control_type::*method_type)(object &);

			uniform_event_forwarder(method_type method, bool is_command)
				: method_(method), is_command_(is_command){}

			virtual ~uniform_event_forwarder() = default;

			virtual void dispatch(object &object) override{
				(dynamic_cast<control_type *>(target(object))->*method_)(object);
			}

			virtual window_type *target(object &object){
				if (is_command_){
					auto handle = object.info().lparam<wrappers::hwnd::value_type>();
					return (handle == nullptr) ? nullptr : wrappers::hwnd(handle).get_data<window_type *>();
				}

				return wrappers::hwnd(object.info().lparam<notify_info_type *>()->hwndFrom).get_data<window_type *>();
			}

		private:
			method_type method_;
			bool is_command_;
		};
	}
}

#endif /* !GRAFEEX_MESSAGE_EVENT_FORWARDER_H */
