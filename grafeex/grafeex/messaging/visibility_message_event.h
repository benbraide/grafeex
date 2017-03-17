#pragma once

#ifndef GRAFEEX_VISIBILITY_MESSAGE_EVENT_H
#define GRAFEEX_VISIBILITY_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class visibility_event : public message_event{
		public:
			typedef ::BOOL bool_type;

			enum class reason_type{
				nil							= 0,
				parent_minimized			= SW_PARENTCLOSING,
				other_window_maximized		= SW_OTHERZOOM,
				parent_restored				= SW_PARENTOPENING,
				other_window_restored		= SW_OTHERUNZOOM,
			};

			explicit visibility_event(object &value);

			virtual ~visibility_event();

			virtual message_event &dispatch() override;

			virtual bool is_hidden() const;

			virtual reason_type reason() const;

			virtual bool parent_is_minimized() const;

			virtual bool parent_is_restored() const;

			virtual bool other_window_is_maximized() const;

			virtual bool other_window_is_restored() const;
		};
	}
}

#endif /* !GRAFEEX_VISIBILITY_MESSAGE_EVENT_H */
