#pragma once

#ifndef GRAFEEX_MESSAGE_DISPATCHER_H
#define GRAFEEX_MESSAGE_DISPATCHER_H

#include "message_object.h"

namespace grafeex{
	namespace messaging{
		class message_event{
		public:
			enum class state : unsigned int{
				nil						= (0 << 0x0000),
				event_disabled			= (1 << 0x0000),
				propagation_stopped		= (1 << 0x0001),
			};

			typedef object::result_type result_type;
			typedef object::handle_type handle_type;
			
			message_event();

			explicit message_event(object &value);

			virtual ~message_event();

			virtual message_event &dispatch() = 0;

			virtual message_event &handle(handle_type type = handle_type::overwrite);

			virtual message_event &skip();

			virtual message_event &reply(bool value);

			virtual message_event &reply();

			template <typename value_type>
			message_event &reply(value_type value){
				object_->reply(value);
				return *this;
			}

			virtual message_event &operator =(result_type value);

			virtual message_event &operator =(bool value);

			template <typename value_type>
			message_event &operator =(value_type value){
				return operator=((result_type)value);
			}

			virtual message_event &operator <<(result_type value);

			virtual message_event &operator <<(bool value);

			template <typename value_type>
			message_event &operator <<(value_type value){
				return operator<<((result_type)value);
			}

			virtual bool is_sent() const;

			virtual bool is_cross_thread() const;

			virtual bool is_replied() const;

			virtual bool has_value() const;

			virtual bool is_default() const;

			virtual bool is_skipped() const;

			virtual bool is_handled() const;

			virtual message_event &disable_event();

			virtual message_event &stop_propagation();

			virtual bool event_is_disabled() const;

			virtual bool is_propagating() const;

			virtual const object &get_object() const;

		protected:
			virtual message_event &write_(result_type value);

			virtual message_event &write_bool_(bool value);

			virtual result_type value_from_bool_(bool value);

			object *object_;
			state states_;
		};

		GRAFEEX_MAKE_OPERATORS(message_event::state)
	}
}

#endif /* !GRAFEEX_MESSAGE_DISPATCHER_H */
