#pragma once

#ifndef GRAFEEX_EVENT_OBJECT_H
#define GRAFEEX_EVENT_OBJECT_H

#include "../messaging/message_event.h"
#include "../gui/gui_object.h"

namespace grafeex{
	namespace events{
		class object{
		public:
			typedef gui::object gui_object_type;
			typedef messaging::message_event message_object_type;

			enum class state : unsigned int{
				nil						= (0 << 0x0000),
				default_prevented		= (1 << 0x0000),
				propagation_stopped		= (1 << 0x0001),
				unhandled				= (1 << 0x0002),
			};

			explicit object(gui_object_type &target);

			object(gui_object_type &target, message_object_type &object);

			virtual object &prevent_default();

			virtual object &do_default();

			virtual object &stop_propagation();

			virtual bool default_is_prevented() const;

			virtual bool is_default() const;

			virtual bool is_propagating() const;

			virtual gui_object_type &target() const;

			virtual message_object_type *message_object() const;

		protected:
			gui_object_type *target_;
			message_object_type *object_;
			state states_;
		};

		GRAFEEX_MAKE_OPERATORS(object::state)
	}
}

#endif /* !GRAFEEX_EVENT_OBJECT_H */
