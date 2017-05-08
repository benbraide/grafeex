#pragma once

#ifndef GRAFEEX_UNIFORM_MESSAGE_EVENT_FORWARDER_H
#define GRAFEEX_UNIFORM_MESSAGE_EVENT_FORWARDER_H

#include "message_event_forwarder.h"

namespace grafeex{
	namespace messaging{
		template <class event_type, class control_type, class return_type, class target_event_type = event_type>
		class uniform_event_forwarder : public event_forwarder_base{
		public:
			typedef ::NMHDR notify_info_type;

			typedef event_type event_type;
			typedef control_type control_type;
			typedef return_type return_type;
			typedef target_event_type target_event_type;

			typedef return_type(control_type::*method_type)(target_event_type &);

			explicit uniform_event_forwarder(method_type method)
				: method_(method){}

			virtual ~uniform_event_forwarder() = default;

			virtual void forward(message_event &object) override{
				do_forward_<target_event_type>(object);
			}

		private:
			template <typename tet = target_event_type>
			std::enable_if_t<std::is_same<tet, event_type>::value> do_forward_(message_event &object){
				forward_<return_type>(object);
			}

			template <typename tet = target_event_type>
			std::enable_if_t<!std::is_same<tet, event_type>::value> do_forward_(message_event &object){
				target_event_type ev(const_cast<messaging::object &>(object.get_object()));
				forward_<return_type>(ev);
			}

			template <typename rt = return_type>
			std::enable_if_t<std::is_same<rt, void>::value> forward_(message_event &object){
				auto e = dynamic_cast<target_event_type *>(&object);
				auto control = e->control();
				(dynamic_cast<control_type *>(control)->*method_)(*e);
			}

			template <typename rt = return_type>
			std::enable_if_t<!std::is_same<rt, void>::value> forward_(message_event &object){
				auto e = dynamic_cast<target_event_type *>(&object);
				auto control = e->control();
				object << (dynamic_cast<control_type *>(control)->*method_)(*e);
			}

			method_type method_;
		};
	}
}

#endif /* !GRAFEEX_UNIFORM_MESSAGE_EVENT_FORWARDER_H */
