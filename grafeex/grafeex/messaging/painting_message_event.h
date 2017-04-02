#pragma once

#ifndef GRAFEEX_PAINTING_MESSAGE_EVENT_H
#define GRAFEEX_PAINTING_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class erase_background_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::HDC device_type;

			explicit erase_background_event(object &value);

			virtual ~erase_background_event();

			virtual message_event &dispatch() override;

			virtual device_type device();
		};

		class paint_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::HDC device_type;

			explicit paint_event(object &value);

			virtual ~paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() = 0;

			virtual bool is_client() const = 0;
		};

		class nc_paint_event : public paint_event{
		public:
			using paint_event::operator=;

			explicit nc_paint_event(object &value);

			virtual ~nc_paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() override;

			virtual bool is_client() const override;
		};

		class client_paint_event : public paint_event{
		public:
			using paint_event::operator=;

			explicit client_paint_event(object &value);

			virtual ~client_paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() override;

			virtual bool is_client() const override;
		};
	}
}

#endif /* !GRAFEEX_PAINTING_MESSAGE_EVENT_H */
