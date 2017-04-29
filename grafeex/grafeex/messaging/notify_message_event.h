#pragma once

#ifndef GRAFEEX_NOTIFY_MESSAGE_EVENT_H
#define GRAFEEX_NOTIFY_MESSAGE_EVENT_H

#include "../wrappers/hdc_wrapper.h"
#include "../d2d/d2d_hdc_render_target.h"
#include "../d2d/d2d_drawer.h"

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class notify_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::UINT uint_type;
			typedef ::UINT_PTR uint_ptr_type;
			typedef ::NMHDR info_type;

			explicit notify_event(object &value);

			virtual ~notify_event();

			virtual message_event &dispatch() override;

			virtual window_type *control() const;

			virtual uint_ptr_type id() const;

			virtual uint_type code() const;

			virtual info_type &info() const;

		protected:
			virtual message_event &dispatch_();
		};

		class custom_draw_event : public notify_event, public d2d::drawer<d2d::hdc_render_target>{
		public:
			typedef ::NMCUSTOMDRAW draw_info_type;
			typedef ::DWORD dword_type;
			typedef ::DWORD_PTR dword_ptr_type;

			typedef structures::rect rect_type;

			explicit custom_draw_event(object &value);

			virtual ~custom_draw_event();

			virtual message_event &dispatch() override;

			virtual hdc_type device() const;

			virtual rect_type clip_rect() const;

			virtual dword_type stage() const;

			virtual dword_ptr_type spec() const;

			virtual uint_type state() const;

			virtual draw_info_type &draw_info() const;

		protected:
			virtual void create_render_holder_() override;

			virtual void on_error_(hresult_type err) override;
		};
	}
}

#endif /* !GRAFEEX_NOTIFY_MESSAGE_EVENT_H */
