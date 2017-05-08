#pragma once

#ifndef GRAFEEX_CONTROL_OBJECT_H
#define GRAFEEX_CONTROL_OBJECT_H

#include "../window/window_object.h"
#include "../gdi/gdi_object_ptr.h"

#include "../messaging/command_message_event_handler.h"
#include "../messaging/notify_message_event_handler.h"

#include "control_views.h"
#include "control_styles.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class object : public window::object{
			public:
				typedef ::HFONT font_type;
				typedef ::INITCOMMONCONTROLSEX init_info_type;
				typedef ::DWORD dword_type;

				typedef window::object base_type;
				typedef controls::view view_type;

				typedef graphics::text::d2d_font_type d2d_font_type;
				typedef graphics::text::font_info_type font_info_type;

				typedef gdi::object_ptr<font_type> gdi_font_type;
				typedef app_type::control_object_type control_type;

				explicit object(control_type type);

				virtual ~object();

				virtual view_type &view() override;

				virtual dword_type white_listed_styles(bool is_extended) const override;

				virtual dword_type black_listed_styles(bool is_extended) const override;

				virtual control_type control_object_type() const;

				static dword_type get_initializer(control_type type);

				static const wchar_t *get_class_name(control_type type);

				static procedure_type get_procedure(const wchar_t *class_name);

			protected:
				friend class application::object;
				friend class controls::view;

				virtual void on_set_font(messaging::set_font_event &e) override;

				virtual void created_() override;

				virtual void reset_persistent_styles_() override;

				virtual view_ptr_type get_view_() override;

				virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size,
					dword_type styles = 0, dword_type extended_styles = 0, const wchar_t *class_name = nullptr) override;

				virtual bool init_common_(control_type type);

				virtual void update_size_();

				virtual size_type compute_size_(const std::wstring &label);

				virtual size_type compute_additional_size_(const std::wstring &label);

				control_type type_;
				std::wstring class_name_;
				gdi_font_type font_;
				font_type font_value_;

				static dword_type initialized_controls_;
			};
		}
	}
}

#endif /* !GRAFEEX_CONTROL_OBJECT_H */
