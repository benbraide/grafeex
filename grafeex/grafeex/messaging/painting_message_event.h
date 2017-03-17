#pragma once

#ifndef GRAFEEX_PAINTING_MESSAGE_EVENT_H
#define GRAFEEX_PAINTING_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class erase_background_event : public message_event{
		public:
			typedef ::HDC device_type;

			explicit erase_background_event(object &value);

			virtual ~erase_background_event();

			virtual message_event &dispatch() override;

			virtual device_type device();
		};

		class paint_event : public message_event{
		public:
			typedef ::HDC device_type;

			explicit paint_event(object &value);

			virtual ~paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() = 0;

			virtual bool is_client() const = 0;
		};

		template <bool is_client>
		class typed_paint_event;

		template <>
		class typed_paint_event<false> : public paint_event{
		public:
			explicit typed_paint_event(object &value)
				: paint_event(value){}

			virtual ~typed_paint_event(){}

			virtual message_event &dispatch() override{
				if (paint_event::dispatch().is_propagating())
					object_->target()->on_nc_paint(*this);
				return *this;
			}

			virtual device_type device() override{
				return nullptr;
			}

			virtual bool is_client() const override{
				return false;
			}
		};

		template <>
		class typed_paint_event<true> : public paint_event{
		public:
			explicit typed_paint_event(object &value)
				: paint_event(value){}

			virtual ~typed_paint_event(){}

			virtual message_event &dispatch() override{
				if (paint_event::dispatch().is_propagating())
					object_->target()->on_paint_client(*this);
				return *this;
			}

			virtual device_type device() override{
				return nullptr;
			}

			virtual bool is_client() const override{
				return true;
			}
		};

		using nc_paint_event = typed_paint_event<false>;
		using client_paint_event = typed_paint_event<true>;
	}
}

#endif /* !GRAFEEX_PAINTING_MESSAGE_EVENT_H */
