#pragma once

#ifndef GRAFEEX_BUTTON_CONTROL_H
#define GRAFEEX_BUTTON_CONTROL_H

#include "control_object.h"

#include "../graphics/graphics_text.h"
#include "../messaging/command_message_event_handler.h"
#include "../messaging/notify_message_event_handler.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class button : public object, public messaging::button_command_event_handler,
				public messaging::button_notify_event_handler{
			public:
				typedef ::LOGFONTW font_info_type;
				typedef ::DWORD dword_type;

				typedef controls::button_style style_type;

				button();

				button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				virtual ~button();

				virtual dword_type white_listed_styles(bool is_extended) const override;

				virtual style_type &style() override;

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				virtual button &label(const std::wstring &value);

				virtual const std::wstring &label();

				virtual button &padding(const size_type &value);

				virtual const size_type &padding();

				static const dword_type general_styles = (BS_FLAT | BS_MULTILINE | BS_CENTER | BS_VCENTER);

			protected:
				virtual void on_set_font(messaging::set_font_event &e) override;

				virtual void on_set_text(messaging::set_text_event &e) override;

				virtual void reset_persistent_styles_() override;

				virtual style_ptr_type get_style_() override;

				virtual bool create_(const std::wstring &label, const point_type &offset, const size_type &padding);

				virtual size_type compute_size_(const std::wstring &label) override;

				size_type padding_;
			};
		}
	}
}

#endif /* !GRAFEEX_BUTTON_CONTROL_H */
