#pragma once

#ifndef GRAFEEX_WINDOW_OBJECT_H
#define GRAFEEX_WINDOW_OBJECT_H

#include "window_view.h"
#include "window_style.h"

#include "../gui/gui_object_tree.h"
#include "../d2d/d2d_hwnd_render_target.h"
#include "../d2d/d2d_render_target_manager.h"

#include "../wrappers/hwnd_wrapper.h"
#include "../wrappers/wnd_class_wrapper.h"

#include "../messaging/general_message_event_handler.h"
#include "../messaging/menu_message_event_handler.h"
#include "../messaging/input_message_event_handler.h"

#include "../menu/shared_menu.h"
#include "../collections/menu_collection.h"
#include "../collections/tab_collection_interface.h"

namespace grafeex{
	namespace messaging{
		class event_forwarder_base;
	}

	namespace window{
		class object : public gui::object_tree, public messaging::general_event_handler, public messaging::menu_event_handler,
			public messaging::input_event_handler{
		public:
			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;

			typedef ::D2D1_SIZE_F d2d_float_size_type;
			typedef ::D2D1_POINT_2F d2d_float_point_type;
			typedef ::D2D1_RECT_F d2d_float_rect_type;

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

			typedef application::object::d2d_point_type d2d_point_type;
			typedef application::object::d2d_size_type d2d_size_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef hwnd_type::create_info_type create_info_type;
			typedef application::object app_type;

			typedef window::view view_type;
			typedef std::shared_ptr<view_type> view_ptr_type;

			typedef window::style style_type;
			typedef std::shared_ptr<style_type> style_ptr_type;

			typedef menu::object menu_type;
			typedef menu::shared shared_menu_type;

			typedef collections::menu_bar menu_collection_type;
			typedef collections::shared_menu shared_menu_collection_type;
			typedef collections::tab_interface tab_collection_type;

			typedef std::shared_ptr<menu_type> menu_ptr_type;
			typedef std::shared_ptr<menu_collection_type> menu_collection_ptr_type;
			typedef std::shared_ptr<shared_menu_collection_type> shared_menu_collection_ptr_type;
			typedef std::shared_ptr<tab_collection_type> tab_collection_ptr_type;

			typedef general_event_handler::d2d_color_type d2d_color_type;
			typedef d2d::hwnd_render_target hwnd_render_type;
			typedef d2d::hdc_render_target d2d_hdc_render_type;

			typedef hwnd_render_type::interface_type render_type;
			typedef d2d_hdc_render_type::interface_type hdc_render_type;

			typedef d2d::render_target_manager<hwnd_render_type> render_manager_type;
			typedef d2d::render_target_manager<d2d_hdc_render_type> hdc_render_manager_type;

			typedef std::shared_ptr<render_manager_type> render_manager_ptr_type;
			typedef std::shared_ptr<hdc_render_manager_type> hdc_render_manager_ptr_type;

			typedef style_type::info_type persistent_styles;

			struct relative_info{
				bool active;
				d2d_point_type offset;
				d2d_size_type size;
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

			virtual d2d_float_point_type convert_to_dip(const point_type &value);

			virtual d2d_float_rect_type convert_to_dip(const rect_type &value);

			virtual point_type convert_from_dip(const d2d_float_point_type &value);

			virtual rect_type convert_from_dip(const d2d_float_rect_type &value);

			virtual bool is_dialog() const;

			virtual bool is_top_level() const;

			virtual bool is_ancestor(const object_type &target) const;

			virtual bool has_menu() const;

			virtual menu_collection_type &menu();

			virtual shared_menu_collection_type &system_menu();

			virtual tab_collection_type &tab();

			template <typename tab_type>
			tab_collection_type &typed_tab(){
				if (tab_ == nullptr)
					tab_ = std::make_shared<tab_type>(*this);
				return *tab_;
			}

			virtual view_type &view();

			virtual style_type &style();

			virtual hwnd_render_type &renderer();

			virtual render_manager_type &render_manager();

			virtual hdc_render_manager_type &hdc_render_manager();

			static d2d_point_type point_to_dip(const point_type &value);

			static d2d_size_type size_to_dip(const size_type &value);

			static point_type point_to_pixel(const d2d_point_type &value);

			static size_type size_to_pixel(const d2d_size_type &value);

			static app_type *&app_instance;

		protected:
			friend class application::object;

			friend class messaging::create_event;
			friend class messaging::nc_create_event;
			friend class messaging::nc_destroy_event;

			friend class messaging::activate_event;
			friend class messaging::focus_change_event;

			friend class messaging::changed_position_event;
			friend class messaging::changed_size_event;

			friend class messaging::erase_background_event;
			friend class messaging::paint_event;
			friend class messaging::print_client_event;
			friend class messaging::print_event;

			friend class messaging::custom_draw_event;

			friend class messaging::command_event;
			friend class messaging::notify_event;

			friend class messaging::set_text_event;

			friend class window::view;
			friend class window::style;

			explicit object(procedure_type previous_procedure = ::DefWindowProcW);

			virtual void on_recreate_drawing_resources(bool is_device) override;

			virtual events_type get_events_() override;

			virtual void sized_() override;

			virtual void add_(child_type &child) override;

			virtual void remove_(child_type &child) override;

			virtual void insert_into_parent_(object_type &parent);

			virtual void insert_into_parent_(const sibling_type &sibling);

			virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size, dword_type styles = 0,
				dword_type extended_styles = 0, const wchar_t *class_name = nullptr);

			virtual bool create_(const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size, dword_type styles = 0,
				dword_type extended_styles = 0, const wchar_t *class_name = nullptr);

			virtual bool create_(const create_info_type &info);

			virtual void created_();

			virtual hwnd_type get_parent_handle_();

			virtual object *get_window_parent_();

			virtual object *get_dialog_parent_();

			virtual void initialize_();

			virtual void uninitialize_();

			virtual void reset_persistent_styles_();

			virtual void sync_(object &target, bool add);

			virtual void unsync_();

			virtual view_ptr_type get_view_();

			template <typename view_type>
			view_ptr_type create_view_(){
				if (view_ == nullptr)
					view_ = std::make_shared<view_type>(*this);
				return view_;
			}

			virtual style_ptr_type get_style_();

			template <typename style_type>
			style_ptr_type create_style_(){
				if (style_ == nullptr)
					style_ = std::make_shared<style_type>(*this);
				return style_;
			}

			hwnd_type value_;
			std::wstring text_;
			relative_info relative_info_;
			procedure_type previous_procedure_;
			persistent_styles persistent_styles_{};
			shared_menu_collection_ptr_type system_menu_;
			menu_collection_ptr_type menu_;
			tab_collection_ptr_type tab_;
			view_ptr_type view_;
			style_ptr_type style_;
			render_manager_ptr_type renderer_;
			hdc_render_manager_ptr_type hdc_renderer_;
			object *synced_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_OBJECT_H */
