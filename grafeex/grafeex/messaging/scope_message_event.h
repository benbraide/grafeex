#pragma once

#ifndef GRAFEEX_SCOPE_MESSAGE_EVENT_H
#define GRAFEEX_SCOPE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class scope_event : public message_event{
		public:
			explicit scope_event(object &value);

			virtual ~scope_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const = 0;

			virtual bool is_client() const = 0;
		};

		class nc_create_event : public scope_event{
		public:
			explicit nc_create_event(object &value);

			virtual ~nc_create_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const override;

			virtual bool is_client() const override;
		};

		class create_event : public scope_event{
		public:
			explicit create_event(object &value);

			virtual ~create_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const override;

			virtual bool is_client() const override;

		protected:
			virtual result_type value_from_bool_(bool value) override;
		};

		class nc_destroy_event : public scope_event{
		public:
			explicit nc_destroy_event(object &value);

			virtual ~nc_destroy_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const override;

			virtual bool is_client() const override;
		};

		class destroy_event : public scope_event{
		public:
			explicit destroy_event(object &value);

			virtual ~destroy_event();

			virtual message_event &dispatch() override;

			virtual bool is_create() const override;

			virtual bool is_client() const override;
		};
	}
}

#endif /* !GRAFEEX_SCOPE_MESSAGE_EVENT_H */
