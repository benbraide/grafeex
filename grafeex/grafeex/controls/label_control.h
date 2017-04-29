#pragma once

#ifndef GRAFEEX_LABEL_CONTROL_H
#define GRAFEEX_LABEL_CONTROL_H

#include "control_object.h"

#include "../graphics/graphics_text.h"
#include "../messaging/command_message_event_handler.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class label : public object, public messaging::static_command_event_handler{
			public:
				label();

				label(object_type &parent, const std::wstring &label, const point_type &offset);

				label(const sibling_type &sibling, const std::wstring &label, const point_type &offset);

				virtual ~label();

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset);

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset);

				virtual label &text(const std::wstring &value);

				virtual const std::wstring &text();

			protected:
				virtual void on_set_font(messaging::set_font_event &e) override;

				virtual void on_set_text(messaging::set_text_event &e) override;

				virtual void reset_persistent_styles_() override;

				virtual size_type compute_additional_size_(const std::wstring &label) override;
			};
		}
	}
}

#endif /* !GRAFEEX_LABEL_CONTROL_H */
