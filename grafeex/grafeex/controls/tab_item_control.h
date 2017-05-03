#pragma once

#ifndef GRAFEEX_TAB_ITEM_CONTROL_H
#define GRAFEEX_TAB_ITEM_CONTROL_H

#include "control_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class tab;

			class tab_item_event_handler{
			public:
				virtual ~tab_item_event_handler() = default;

			protected:
				friend class tab;

				virtual void on_activate() = 0;

				virtual bool on_deactivate() = 0;
			};

			template <class my_base_type>
			class tab_item : public my_base_type, public tab_item_event_handler{
			public:
				typedef ::TCITEMW info_type;
				typedef ::DWORD dword_type;
				typedef ::LPARAM lparam_type;

				typedef my_base_type my_base_type;

				typedef structures::point point_type;
				typedef structures::size size_type;
				typedef gui::generic_object::events_type events_type;

				typedef window::object::object_type object_type;
				typedef window::object::sibling_type sibling_type;
				
				typedef structures::rect_origin_type alignment_type;

				class event_tunnel : public my_base_type::event_tunnel{
				public:
					typedef typename my_base_type::event_tunnel my_base_type;
					typedef typename my_base_type::void_event_type void_event_type;
					typedef typename my_base_type::bool_event_type bool_event_type;
					typedef typename my_base_type::event_object_type event_object_type;

					event_tunnel(){
						event_list_[activate_event_.group()] = &activate_event_;
						event_list_[deactivate_event_.group()] = &deactivate_event_;
					}

					virtual ~event_tunnel() = default;

					GGGO_VOID_EVENT2(activate)
					GGGO_BOOL_EVENT2(deactivate)

					void_event_type activate_event_;
					bool_event_type deactivate_event_;
				};

				tab_item(){
					reset_persistent_styles_();
				}

				tab_item(object_type &parent, const std::wstring &caption){
					reset_persistent_styles_();
					create(parent, caption);
				}

				tab_item(const sibling_type &sibling, const std::wstring &caption){
					reset_persistent_styles_();
					create(sibling, caption);
				}

				virtual dword_type black_listed_styles(bool is_extended) const override{
					return (my_base_type::black_listed_styles(is_extended) | (is_extended ? 0L : WS_OVERLAPPEDWINDOW));
				}

				virtual event_tunnel &events() override{
					return *dynamic_cast<event_tunnel *>(get_events_().get());
				}

				virtual bool destroy() override{
					if (!is_created())
						return true;

					return my_base_type::destroy();
				}

				virtual bool create(object_type &parent, const std::wstring &caption){
					my_base_type::insert_into_parent_(parent);
					return create_(caption, point_type{}, size_type{});
				}

				virtual bool create(const sibling_type &sibling, const std::wstring &caption){
					my_base_type::insert_into_parent_(sibling);
					return create_(caption, point_type{}, size_type{});
				}

			protected:
				virtual void on_activate() override{
					grafeex::events::object e(*this);
					events().activate_event_.fire(e);
				}

				virtual bool on_deactivate() override{
					grafeex::events::object e(*this);
					return events().deactivate_event_.fire(e, true);
				}

				virtual void reset_persistent_styles_() override{
					my_base_type::reset_persistent_styles_();
					GRAFEEX_REMOVE(my_base_type::persistent_styles_.basic, WS_OVERLAPPEDWINDOW);
				}

				virtual events_type get_events_() override{
					return my_base_type::create_events_<event_tunnel>();
				}

				virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size, dword_type styles = 0,
					dword_type extended_styles = 0, const wchar_t *class_name = nullptr) override{
					if (!my_base_type::create_(caption, offset, size, styles, extended_styles, class_name))
						return false;

					auto window_parent = dynamic_cast<window::object *>(my_base_type::parent_);
					auto index = window_parent->get_child_index(*this);
					info_type info{
						TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM,
						0,
						0,
						const_cast<wchar_t *>(caption.c_str()),
						0,
						-1,
						reinterpret_cast<lparam_type>(static_cast<gui::object *>(this))
					};

					if (TabCtrl_InsertItem(window_parent->operator HWND(), index, &info) == -1){
						window_parent->remove(*this);
						my_base_type::parent_ = nullptr;
					}

					my_base_type::attributes().fill_parent(true);
					my_base_type::attributes().align(true, alignment_type::top | alignment_type::left);

					if (window_parent->get_children_count() == 1u){
						my_base_type::view().show();
						on_activate();//First child -- activate
					}

					return true;
				}
			};
		}
	}
}

#endif /* !GRAFEEX_TAB_ITEM_CONTROL_H */
