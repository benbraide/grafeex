#pragma once

#ifndef GRAFEEX_MESSAGE_DISPATCHER_H
#define GRAFEEX_MESSAGE_DISPATCHER_H

#include "../gui/gui_object.h"
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

			typedef window::object window_type;

			typedef gui::object gui_object_type;
			typedef gui::object::event_tunnel event_type;
			
			message_event();

			explicit message_event(object &value);

			virtual ~message_event();

			virtual message_event &dispatch();

			virtual message_event &handle(handle_type type = handle_type::write);

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

			template <typename return_type, typename object_type, typename function_type, typename... value_types>
			return_type call(function_type method, object_type &object, const value_types &... values){
				return (object.*method)(values...);
			}

			template <typename return_type, typename object_type, typename function_type, typename... value_types>
			return_type call_ref_args(function_type method, object_type &object, value_types &... values){
				return (object.*method)(values...);
			}

			template <typename return_type, typename object_type, typename function_type, typename... value_types>
			return_type call_val_args(function_type method, object_type &object, value_types... values){
				return (object.*method)(values...);
			}

		protected:
			virtual message_event &write_(result_type value);

			virtual message_event &write_bool_(bool value);

			virtual result_type value_from_bool_(bool value);

			virtual event_type *get_event_(gui_object_type *object = nullptr);

			object *object_;
			state states_;
		};

		class null_event : public message_event{
		public:
			using message_event::operator=;

			explicit null_event(object &value);

			virtual ~null_event();

			virtual message_event &dispatch() override;
		};

		class unhandled_event : public message_event{
		public:
			using message_event::operator=;

			explicit unhandled_event(object &value);

			virtual ~unhandled_event();

			virtual message_event &dispatch() override;
		};

		GRAFEEX_MAKE_OPERATORS(message_event::state)
	}
}

#endif /* !GRAFEEX_MESSAGE_DISPATCHER_H */
