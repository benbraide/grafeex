#pragma once

#ifndef GRAFEEX_WINDOW_OBJECT_H
#define GRAFEEX_WINDOW_OBJECT_H

#include "../gui/gui_object_tree.h"
#include "../wrappers/wnd_class_wrapper.h"

#include "../messaging/general_message_event_handler.h"

namespace grafeex{
	namespace application{
		class object;
	}

	namespace messaging{
		class message_event;
	}

	namespace window{
		class object : public gui::object_tree, protected messaging::general_event_handler{
		public:
			typedef wrappers::wnd_class wnd_class_type;
			typedef wrappers::hwnd hwnd_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

		protected:
			friend class application::object;

			friend class messaging::message_event;
			friend class messaging::scope_event;
			friend class messaging::close_event;
			friend class messaging::activate_event;
			friend class messaging::enable_event;
			friend class messaging::erase_background_event;
			friend class messaging::paint_event;
			friend class messaging::style_event;
			friend class messaging::visibility_event;

			template <messaging::scope_event_option> friend class messaging::typed_scope_event;
			template <bool> friend class messaging::typed_paint_event;
			template <bool> friend class messaging::typed_style_event;

			procedure_type previous_procedure_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_OBJECT_H */
