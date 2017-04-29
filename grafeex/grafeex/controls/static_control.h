#pragma once

#ifndef GRAFEEX_STATIC_CONTROL_H
#define GRAFEEX_STATIC_CONTROL_H

#include "control_object.h"

#include "../graphics/graphics_text.h"
#include "../messaging/command_message_event_handler.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class static_control : public object, public messaging::static_command_event_handler{
			public:
				static_control();

				static_control(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &size);

				static_control(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &size);

				virtual ~static_control();

				virtual dword_type white_listed_styles(bool is_extended) const override;

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &size);

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &size);

				virtual static_control &label(const std::wstring &value);

				virtual const std::wstring &label();

			protected:
				virtual void reset_persistent_styles_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_STATIC_CONTROL_H */
