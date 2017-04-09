#pragma once

#ifndef GRAFEEX_PAINTING_MESSAGE_EVENT_H
#define GRAFEEX_PAINTING_MESSAGE_EVENT_H

#include <memory>

#include "../d2d/d2d_hwnd_render_target.h"
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

			virtual device_type device() const;
		};

		class paint_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::HDC device_type;
			typedef d2d::hwnd_render_target render_type;

			explicit paint_event(object &value);

			virtual ~paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() const = 0;

			virtual bool is_client() const = 0;
		};

		class nc_paint_event : public paint_event{
		public:
			using paint_event::operator=;

			explicit nc_paint_event(object &value);

			virtual ~nc_paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() const override;

			virtual bool is_client() const override;
		};

		class client_paint_event : public paint_event{
		public:
			using paint_event::operator=;

			typedef ::PAINTSTRUCT info_type;
			typedef std::shared_ptr<info_type> info_ptr_type;

			typedef structures::rect rect_type;

			explicit client_paint_event(object &value);

			virtual ~client_paint_event();

			virtual message_event &dispatch() override;

			virtual device_type device() const override;

			virtual bool is_client() const override;

			virtual bool begin();

			virtual bool end();

			virtual bool has_begun() const;

			virtual bool erase_background() const;

			virtual rect_type update_rect() const;

		protected:
			info_ptr_type info_;
		};

		class print_client_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::HDC device_type;
			typedef d2d::hwnd_render_target render_type;

			enum class option : unsigned int{
				nil						= 0,
				check_visible			= PRF_CHECKVISIBLE,
				non_client				= PRF_NONCLIENT,
				client					= PRF_CLIENT,
				erase_background		= PRF_ERASEBKGND,
				children				= PRF_CHILDREN,
				owned					= PRF_OWNED,
			};

			explicit print_client_event(object &value);

			virtual ~print_client_event();

			virtual message_event &dispatch() override;

			virtual device_type device() const;

			virtual option options() const;
		};

		class print_event : public message_event{
		public:
			using message_event::operator=;

			typedef ::HDC device_type;
			typedef d2d::hwnd_render_target render_type;

			enum class option : unsigned int{
				nil						= 0,
				check_visible			= PRF_CHECKVISIBLE,
				non				= PRF_NONCLIENT,
				client					= PRF_CLIENT,
				erase_background		= PRF_ERASEBKGND,
				children				= PRF_CHILDREN,
				owned					= PRF_OWNED,
			};

			explicit print_event(object &value);

			virtual ~print_event();

			virtual message_event &dispatch() override;

			virtual device_type device() const;

			virtual option options() const;
		};

		GRAFEEX_MAKE_OPERATORS(print_client_event::option)
		GRAFEEX_MAKE_OPERATORS(print_event::option)
	}
}

#endif /* !GRAFEEX_PAINTING_MESSAGE_EVENT_H */
