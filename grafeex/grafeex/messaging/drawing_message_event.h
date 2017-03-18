#pragma once

#ifndef GRAFEEX_DRAWING_MESSAGE_EVENT_H
#define GRAFEEX_DRAWING_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class draw_event : public message_event{
		public:
			typedef ::UINT uint_type;
			typedef ::DRAWITEMSTRUCT info_type;

			enum class draw_action_type : uint_type{
				nil				= 0,
				entire			= ODA_DRAWENTIRE,
				focused			= ODA_FOCUS,
				selected		= ODA_SELECT,
			};

			enum class item_state_type : uint_type{
				nil					= 0,
				checked				= ODS_CHECKED,
				combo_box_edit		= ODS_COMBOBOXEDIT,
				default				= ODS_DEFAULT,
				disabled			= ODS_DISABLED,
				focused				= ODS_FOCUS,
				grayed				= ODS_GRAYED,
				hot_light			= ODS_HOTLIGHT,
				inactive			= ODS_INACTIVE,
				no_accel			= ODS_NOACCEL,
				no_focus_rect		= ODS_NOFOCUSRECT,
				selected			= ODS_SELECTED,
			};

			explicit draw_event(object &value);

			virtual ~draw_event();

			virtual message_event &dispatch() override;

		protected:
			info_type *info_;
		};
	}
}

#endif /* !GRAFEEX_DRAWING_MESSAGE_EVENT_H */
