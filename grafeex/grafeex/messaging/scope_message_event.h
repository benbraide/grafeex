#pragma once

#ifndef GRAFEEX_SCOPE_MESSAGE_EVENT_H
#define GRAFEEX_SCOPE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class scope_event : public message_event{
		public:
			enum class option : unsigned int{
				nil				= (0 << 0x0000),
				create			= (1 << 0x0000),
				client			= (1 << 0x0001),
			};

			explicit scope_event(object &value);

			virtual ~scope_event();

			virtual bool is_create() const = 0;

			virtual bool is_client() const = 0;
		};

		GRAFEEX_MAKE_OPERATORS(scope_event::option)

		template <scope_event::option options>
		class typed_scope_event;

		template <>
		class typed_scope_event<scope_event::option::create> : public scope_event{
		public:
			explicit typed_scope_event(object &value)
				: scope_event(value){}

			virtual ~typed_scope_event(){}

			virtual message_event &dispatch() override{
				return *this;
			}

			virtual bool is_create() const override{
				return true;
			}

			virtual bool is_client() const override{
				return false;
			}
		};

		template <>
		class typed_scope_event<scope_event::option::create | scope_event::option::client> : public scope_event{
		public:
			explicit typed_scope_event(object &value)
				: scope_event(value){}

			virtual ~typed_scope_event(){}

			virtual message_event &dispatch() override{
				return *this;
			}

			virtual bool is_create() const override{
				return true;
			}

			virtual bool is_client() const override{
				return true;
			}

		protected:
			virtual result_type value_from_bool_(bool value) override{
				return (value ? 0 : -1);
			}
		};

		template <>
		class typed_scope_event<scope_event::option::nil> : public scope_event{
		public:
			explicit typed_scope_event(object &value)
				: scope_event(value){}

			virtual ~typed_scope_event(){}

			virtual message_event &dispatch() override{
				return *this;
			}

			virtual bool is_create() const override{
				return false;
			}

			virtual bool is_client() const override{
				return false;
			}
		};

		template <>
		class typed_scope_event<scope_event::option::client> : public scope_event{
		public:
			explicit typed_scope_event(object &value)
				: scope_event(value){}

			virtual ~typed_scope_event(){}

			virtual message_event &dispatch() override{
				return *this;
			}

			virtual bool is_create() const override{
				return false;
			}

			virtual bool is_client() const override{
				return true;
			}
		};
	}
}

#endif /* !GRAFEEX_SCOPE_MESSAGE_EVENT_H */
