#pragma once

#ifndef GRAFEEX_WINDOW_OBJECT_H
#define GRAFEEX_WINDOW_OBJECT_H

#include "window_view.h"

#include "../gui/gui_object_tree.h"

#include "../wrappers/hwnd_wrapper.h"
#include "../wrappers/wnd_class_wrapper.h"

#include "../messaging/general_message_event_handler.h"
#include "../messaging/menu_message_event_handler.h"

#include "../menu/shared_menu.h"
#include "../collections/menu_collection.h"

namespace grafeex{
	namespace window{
		class object : public gui::object_tree, public messaging::general_event_handler, public messaging::menu_event_handler{
		public:
			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;

			typedef gui::object object_type;
			typedef gui::object::sibling_type sibling_type;
			typedef gui::object::tree_type tree_type;

			typedef wrappers::wnd_class wnd_class_type;
			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type native_value_type;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::rect rect_type;

			typedef structures::float_size float_size_type;
			typedef structures::color color_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef hwnd_type::create_info_type create_info_type;
			typedef application::object app_type;

			typedef view view_type;
			typedef std::shared_ptr<view_type> view_ptr_type;

			typedef menu::object menu_type;
			typedef menu::shared shared_menu_type;
			typedef collections::menu_bar menu_collection_type;

			typedef std::shared_ptr<menu_type> menu_ptr_type;
			typedef std::shared_ptr<menu_collection_type> menu_collection_ptr_type;

			struct persistent_styles{
				dword_type basic;
				dword_type extended;
			};

			class event_tunnel : public gui::object_tree::event_tunnel{
			public:
				event_tunnel();

				virtual ~event_tunnel();

				GGGO_VOID_EVENT2(menu_select)
				GGGO_VOID_EVENT2(menu_highlight)
				GGGO_VOID_EVENT2(menu_init)
				GGGO_VOID_EVENT2(context_menu)

				GGGO_BOOL_EVENT2(create)
				GGGO_VOID_EVENT2(destroy)
				GGGO_BOOL_EVENT2(close)

				GGGO_VOID_EVENT2(size)
				GGGO_VOID_EVENT2(maximize)
				GGGO_VOID_EVENT2(minimize)

				GGGO_VOID_EVENT2(show)
				GGGO_VOID_EVENT2(hide)

				GGGO_VOID_EVENT2(erase_background)
				GGGO_VOID_EVENT2(paint)

				GGGO_VOID_EVENT2(timer)

				void_event_type menu_select_event_;
				void_event_type menu_highlight_event_;
				void_event_type menu_init_event_;
				void_event_type context_menu_event_;

				bool_event_type create_event_;
				void_event_type destroy_event_;
				bool_event_type close_event_;

				void_event_type size_event_;
				void_event_type maximize_event_;
				void_event_type minimize_event_;

				void_event_type show_event_;
				void_event_type hide_event_;

				void_event_type erase_background_event_;
				void_event_type paint_event_;

				void_event_type timer_event_;
			};

			virtual ~object();

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual object &drag(const size_type &value) override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type::object_type type() const override;

			virtual event_tunnel &events() override;

			virtual bool destroy() override;

			virtual bool is_created() const;

			virtual dword_type filter_style(dword_type value, bool is_extended) const;

			virtual dword_type white_listed_styles(bool is_extended) const;

			virtual dword_type black_listed_styles(bool is_extended) const;

			virtual operator hwnd_type() const;

			virtual operator native_value_type() const;

			virtual bool is_dialog() const;

			virtual bool is_top_level() const;

			virtual bool has_menu() const;

			virtual menu_collection_type &menu();

			virtual menu_type &system_menu();

			virtual view_type &view();

			static app_type *&app_instance;

		protected:
			friend class application::object;

			friend class messaging::create_event;
			friend class messaging::nc_create_event;
			friend class messaging::nc_destroy_event;

			friend class window::view;

			object(procedure_type previous_procedure = ::DefWindowProcW);

			virtual events_type get_events_() override;

			virtual void add_(child_type &child) override;

			virtual void remove_(child_type &child) override;

			virtual void insert_into_parent_(object_type &parent);

			virtual void insert_into_parent_(const sibling_type &sibling);

			virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size, dword_type styles = 0,
				dword_type extended_styles = 0, const wchar_t *class_name = nullptr);

			virtual bool create_(const create_info_type &info);

			virtual hwnd_type get_parent_handle_();

			virtual object *get_window_parent_();

			virtual void initialize_();

			virtual void uninitialize_();

			virtual view_ptr_type get_view_();

			template <typename view_type>
			view_ptr_type create_view_(){
				if (view_ == nullptr)
					view_ = std::make_shared<view_type>(*this);
				return view_;
			}

			hwnd_type value_;
			std::wstring text_;
			procedure_type previous_procedure_;
			color_type background_color_;
			persistent_styles persistent_styles_ = {};
			menu_ptr_type system_menu_;
			menu_collection_ptr_type menu_;
			view_ptr_type view_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_OBJECT_H */
