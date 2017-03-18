#pragma once

#ifndef GRAFEEX_WINDOW_OBJECT_H
#define GRAFEEX_WINDOW_OBJECT_H

#include "../gui/gui_object_tree.h"

#include "../wrappers/hwnd_wrapper.h"
#include "../wrappers/wnd_class_wrapper.h"

#include "../messaging/general_message_event_handler.h"

namespace grafeex{
	namespace window{
		class object : public gui::object_tree, public messaging::general_event_handler{
		public:
			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;

			typedef gui::object object_type;
			typedef gui::object_sibling object_sibling_type;
			typedef gui::object_tree object_tree_type;

			typedef wrappers::wnd_class wnd_class_type;
			typedef wrappers::hwnd hwnd_type;

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

			struct persistent_styles{
				dword_type basic;
				dword_type extended;
			};

			virtual ~object();

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual object &drag(const size_type &value) override;

			virtual point_type compute_alignment(alignment_type value, const size_type &delta) const override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type::object_type type() const override;

			virtual bool destroy();

			virtual bool is_created() const;

			virtual dword_type filter_style(dword_type value, bool is_extended) const;

			virtual dword_type white_listed_styles(bool is_extended) const;

			virtual dword_type black_listed_styles(bool is_extended) const;

			virtual bool is_dialog() const;

			static app_type *&app_instance;

		protected:
			friend class application::object;

			object(procedure_type previous_procedure = ::DefWindowProcW);

			virtual void add_(child_type &child) override;

			virtual void remove_(child_type &child) override;

			virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size, dword_type styles = 0,
				dword_type extended_styles = 0, const wchar_t *class_name = nullptr);

			virtual bool create_(const create_info_type &info);

			virtual hwnd_type get_parent_handle_();

			virtual object *get_window_parent_();

			virtual void initialize_();

			virtual void uninitialize_();

			hwnd_type value_;
			std::wstring text_;
			procedure_type previous_procedure_;
			color_type background_color_;
			persistent_styles persistent_styles_ = {};
		};
	}
}

#endif /* !GRAFEEX_WINDOW_OBJECT_H */
