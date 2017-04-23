#pragma once

#ifndef GRAFEEX_PAINTING_MESSAGE_EVENT_H
#define GRAFEEX_PAINTING_MESSAGE_EVENT_H

#include "../wrappers/hdc_wrapper.h"
#include "../d2d/d2d_hdc_render_target.h"
#include "../d2d/d2d_drawer.h"

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class erase_background_event : public message_event, public d2d::drawer<d2d::hdc_render_target>{
		public:
			using message_event::operator=;

			typedef d2d::drawer<d2d::hdc_render_target> drawer_type;
			typedef structures::rect rect_type;

			explicit erase_background_event(object &value);

			virtual ~erase_background_event();

			virtual message_event &dispatch() override;

			virtual hdc_type device();

			virtual rect_type clip_rect();

		protected:
			virtual void create_render_holder_() override;

			virtual void on_error_(hresult_type err) override;
		};

		class paint_event : public message_event, public d2d::drawer<d2d::hdc_render_target>{
		public:
			using message_event::operator=;

			typedef d2d::drawer<d2d::hdc_render_target> drawer_type;
			typedef structures::rect rect_type;

			explicit paint_event(object &value);

			virtual ~paint_event();

			virtual message_event &dispatch() override;

			virtual hdc_type device() = 0;

			virtual bool is_client() const = 0;

			virtual rect_type clip_rect() = 0;

		protected:
			virtual void create_render_holder_() override;

			virtual void on_error_(hresult_type err) override;
		};

		class nc_paint_event : public paint_event{
		public:
			using paint_event::operator=;

			explicit nc_paint_event(object &value);

			virtual ~nc_paint_event();

			virtual message_event &dispatch() override;

			virtual hdc_type device() override;

			virtual bool is_client() const override;

			virtual rect_type clip_rect() override;
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

			virtual hdc_type device() override;

			virtual bool is_client() const override;

			virtual rect_type clip_rect() override;

			virtual bool begin();

			virtual bool end();

			virtual bool has_begun() const;

			virtual bool erase_background();

		protected:
			info_ptr_type info_;
		};

		class print_client_event : public message_event, public d2d::drawer<d2d::hdc_render_target>{
		public:
			using message_event::operator=;

			typedef d2d::drawer<d2d::hdc_render_target> drawer_type;
			typedef structures::rect rect_type;

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

			virtual hdc_type device();

			virtual rect_type clip_rect();

			virtual option options() const;

			virtual bool erase_background() const;

		protected:
			virtual void create_render_holder_() override;

			virtual void on_error_(hresult_type err) override;
		};

		class print_event : public message_event, public d2d::drawer<d2d::hdc_render_target>{
		public:
			using message_event::operator=;

			typedef d2d::drawer<d2d::hdc_render_target> drawer_type;
			typedef structures::rect rect_type;

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

			virtual hdc_type device();

			virtual rect_type clip_rect();

			virtual option options() const;

			virtual bool erase_background() const;

		protected:
			virtual void create_render_holder_() override;

			virtual void on_error_(hresult_type err) override;
		};

		GRAFEEX_MAKE_OPERATORS(print_client_event::option)
		GRAFEEX_MAKE_OPERATORS(print_event::option)
	}
}

#endif /* !GRAFEEX_PAINTING_MESSAGE_EVENT_H */
