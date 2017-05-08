#pragma once

#ifndef GRAFEEX_TAB_CONTROL_H
#define GRAFEEX_TAB_CONTROL_H

#include "tab_item_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class tab : public object, public messaging::tab_notify_event_handler{
			public:
				typedef ::TCITEMW item_info_type;

				typedef controls::tab_style style_type;

				typedef object::dword_type dword_type;

				class event_tunnel : public object::event_tunnel{
				public:
					event_tunnel();

					virtual ~event_tunnel();

					GGGO_VOID_EVENT2(activate)
					GGGO_BOOL_EVENT2(deactivate)

					void_event_type activate_event_;
					bool_event_type deactivate_event_;
				};

				tab();

				explicit tab(gui_object_type &parent);

				explicit tab(const sibling_type &sibling);

				virtual ~tab();

				virtual rect_type dimensions(bool inner = false) const override;

				virtual dword_type white_listed_styles(bool is_extended) const override;

				virtual style_type &style() override;

				virtual event_tunnel &events() override;

				virtual bool create(gui_object_type &parent);

				virtual bool create(const sibling_type &sibling);

				virtual gui_object_type *current_item() const;

				static const dword_type general_styles = (TCS_BUTTONS | TCS_FLATBUTTONS | TCS_HOTTRACK | TCS_MULTILINE |
					TCS_RIGHTJUSTIFY | TCS_SCROLLOPPOSITE);

			protected:
				friend class tab_style;

				virtual void on_selection_change_notify(messaging::notify_event &e) override;

				virtual bool on_selection_changing_notify(messaging::notify_event &e) override;

				virtual void reset_persistent_styles_() override;

				virtual void created_() override;

				virtual style_ptr_type get_style_() override;

				virtual events_type get_events_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_TAB_CONTROL_H */
