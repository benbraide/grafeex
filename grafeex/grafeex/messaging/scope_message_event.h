#pragma once

#ifndef GRAFEEX_SCOPE_MESSAGE_EVENT_H
#define GRAFEEX_SCOPE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class scope_event : public message_event{
		public:
			typedef scope_event_option option;

			explicit scope_event(object &value);

			virtual ~scope_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const = 0;

			virtual bool is_client() const = 0;
		};

		template <scope_event::option options>
		class typed_scope_event;

		template <>
		class typed_scope_event<scope_event::option::create> : public scope_event{
		public:
			explicit typed_scope_event(object &value)
				: scope_event(value){}

			virtual ~typed_scope_event(){}

			virtual message_event &dispatch() override{
				if (scope_event::dispatch().is_propagating())
					*this << object_->target()->on_nc_create(*this);
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
				if (scope_event::dispatch().is_propagating())
					*this << object_->target()->on_create(*this);
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
				if (scope_event::dispatch().is_propagating())
					object_->target()->on_nc_destroy(*this);
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
				if (scope_event::dispatch().is_propagating())
					object_->target()->on_destroy(*this);
				return *this;
			}

			virtual bool is_create() const override{
				return false;
			}

			virtual bool is_client() const override{
				return true;
			}
		};

		using nc_create_event = typed_scope_event<scope_event::option::create>;
		using create_event = typed_scope_event<scope_event::option::create | scope_event::option::client>;

		using nc_destroy_event = typed_scope_event<scope_event::option::nil>;
		using destroy_event = typed_scope_event<scope_event::option::client>;
	}
}

#endif /* !GRAFEEX_SCOPE_MESSAGE_EVENT_H */
