#pragma once

#ifndef GRAFEEX_MESSAGE_OBJECT_H
#define GRAFEEX_MESSAGE_OBJECT_H

#include "../wrappers/msg_wrapper.h"
#include "../threading/thread_message_queue.h"
#include "../window/window_object.h"

namespace grafeex{
	namespace messaging{
		class object{
		public:
			typedef ::WNDPROC procedure_type;
			typedef msg::result_type result_type;

			enum class state : unsigned int{
				nil				= (0 << 0x0000),
				sent			= (1 << 0x0000),
				cross			= (1 << 0x0001),
				replied			= (1 << 0x0002),
				skipped			= (1 << 0x0003),
				done			= (1 << 0x0004),
				has_value		= (1 << 0x0005),
				modified		= (1 << 0x0006),
			};

			enum class handle_type : unsigned int{
				nil				= (0 << 0x0000),
				write			= (1 << 0x0000),
				overwrite		= ((1 << 0x0000) | (1 << 0x0001)),
			};

			object(const msg &info, bool is_sent, procedure_type default_callback);

			virtual ~object();

			object &modify(const msg &value);

			object &handle(handle_type type = handle_type::write);

			object &skip();

			object &reply(bool value);

			object &reply();

			template <typename value_type>
			object &reply(value_type value){
				if (GRAFEEX_IS(states_, state::cross) && !GRAFEEX_IS(states_, state::replied)){
					thread_queue::reply((result_type)value);
					GRAFEEX_SET(states_, state::replied);
				}
				
				return *this;
			}

			object &operator =(bool value);

			template <typename value_type>
			object &operator =(value_type value){
				if (!GRAFEEX_IS(states_, state::has_value)){
					GRAFEEX_SET(states_, state::has_value);
					value_ = (result_type)value;
				}

				return *this;
			}

			object &operator <<(bool value);

			template <typename value_type>
			object &operator <<(value_type value){
				GRAFEEX_SET(states_, state::has_value);
				value_ = (result_type)value;
				return *this;
			}

			bool is_sent() const;

			bool is_cross_thread() const;

			bool is_replied() const;

			bool has_value() const;

			bool is_default() const;

			bool is_skipped() const;

			bool is_handled() const;

			bool is_modified() const;

			const msg &info() const;

			result_type value() const;

			window::object *target() const;

		protected:
			msg msg_;
			state states_;
			procedure_type default_callback_;
			result_type value_;
			window::object *target_;
		};

		GRAFEEX_MAKE_OPERATORS(object::state)
		GRAFEEX_MAKE_OPERATORS(object::handle_type)
	}
}

#endif /* !GRAFEEX_MESSAGE_OBJECT_H */
