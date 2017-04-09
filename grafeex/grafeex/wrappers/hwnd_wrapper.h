#pragma once

#ifndef GRAFEEX_HWND_WRAPPER_H
#define GRAFEEX_HWND_WRAPPER_H

#include <string>
#include <chrono>

#include "../structures/enumerations.h"
#include "../structures/ref_rect_structure.h"
#include "../structures/color_structure.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace wrappers{
		class hwnd : public wrappers::pointer<::HWND, hwnd>{
		public:
			typedef ::LRESULT result_type;

			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;

			typedef ::LPVOID vptr_type;
			typedef ::LONG_PTR lptr_type;

			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;

			typedef ::CREATESTRUCTW create_info_type;
			typedef ::WINDOWPLACEMENT placement_info_type;

			typedef ::HMENU menu_type;

			typedef structures::enumerations::animation_type animation_type;
			typedef structures::enumerations::show_mode show_mode;
			typedef structures::enumerations::position_type position_type;
			typedef structures::enumerations::data_index data_index;
			typedef structures::enumerations::dialog_data_index dialog_data_index;
			typedef structures::enumerations::layered_attributes_option layered_attributes_option;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::rect rect_type;
			typedef structures::color color_type;

			typedef wrappers::pointer<::HWND, hwnd> base_type;

			hwnd(value_type value = nullptr);

			hwnd(const hwnd &) = default;

			hwnd &operator =(const hwnd &) = default;

			bool create(const create_info_type &info, hwnd parent);

			template <typename params_type>
			bool create(const create_info_type &info, params_type params, hwnd parent){
				return ((value_ = ::CreateWindowExW(
					info.dwExStyle,
					info.lpszClass,
					info.lpszName,
					info.style,
					info.x,
					info.y,
					info.cx,
					info.cy,
					parent,
					info.hMenu,
					info.hInstance,
					(vptr_type)params
				)) != nullptr);
			}

			bool destroy();

			bool set_menu(menu_type value);

			bool invalidate(const rect_type &rect, bool erase = true);

			bool invalidate(bool erase = true);

			bool validate(const rect_type &rect);

			bool validate();

			bool enable(bool enable = true);

			bool minimize();

			bool show(show_mode mode);

			bool show_asyn(show_mode mode);

			template <typename rep_type, typename period_type>
			bool animate(animation_type type, const std::chrono::duration<rep_type, period_type> &delay = std::chrono::milliseconds(200)){
				return (::AnimateWindow(value_, static_cast<dword_type>(delay.count()), static_cast<dword_type>(type)) != FALSE);
			}

			bool restore_minimized();

			bool move(const point_type &offset, const size_type &size, bool repaint);

			bool position(const point_type &offset, const size_type &size, position_type type, hwnd after);

			bool place(const placement_info_type &info);

			bool bring_to_top();

			bool update();

			bool switch_to_this(bool cause_is_alt_tab = false);

			hwnd activate();

			bool draw_menu_bar();

			bool set_as_foreground();

			bool set_layered_attributes(const color_type &color, layered_attributes_option options = layered_attributes_option::all);

			hwnd set_parent(hwnd parent);

			bool set_text(const std::wstring &value);

			template <typename value_type>
			value_type set_data(const value_type &data, data_index index = data_index::user_data){
				if (value_ == nullptr)
					return value_type();

				return (value_type)::SetWindowLongPtrW(value_, static_cast<int>(index), (lptr_type)data);
			}

			template <typename value_type>
			value_type set_dialog_data(const value_type &data, dialog_data_index index = dialog_data_index::user_data){
				if (value_ == nullptr)
					return value_type();

				return (value_type)::SetWindowLongPtrW(value_, static_cast<int>(index), (lptr_type)data);
			}

			template <typename value_type>
			value_type get_data(data_index index = data_index::user_data) const{
				if (value_ == nullptr)
					return value_type();

				return (value_type)::GetWindowLongPtrW(value_, static_cast<int>(index));
			}

			template <typename value_type>
			value_type get_dialog_data(dialog_data_index index = dialog_data_index::user_data) const{
				if (value_ == nullptr)
					return value_type();

				return (value_type)::GetWindowLongPtrW(value_, static_cast<int>(index));
			}

			window::object *get_owner() const;

			hwnd get_parent() const;

			std::wstring get_text() const;

			int get_text_length() const;

			rect_type get_update_rect() const;

			rect_type get_rect() const;

			rect_type get_client_rect() const;

			point_type client_to_screen(point_type value) const;

			rect_type client_to_screen(rect_type value) const;

			point_type screen_to_client(point_type value) const;

			rect_type screen_to_client(rect_type value) const;

			rect_type adjust_rect(const rect_type &value) const;

			bool is_visible() const;

			bool is_enabled() const;

			bool is_maximized() const;

			bool is_minimized() const;

			bool is_frozen() const;

			bool is_foreground() const;

			template <typename return_type = result_type, typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			return_type send_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()) const{
				if (value_ == nullptr)
					return return_type();

				return (return_type)::SendMessageW(value_, msg, (hwnd::wparam_type)wparam, (hwnd::lparam_type)lparam);
			}

			template <typename return_type = result_type, typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			return_type send_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()){
				if (value_ == nullptr)
					return return_type();

				return (return_type)::SendMessageW(value_, msg, (hwnd::wparam_type)wparam, (hwnd::lparam_type)lparam);
			}

			template <typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			bool post_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()) const{
				return (value_ != nullptr && ::PostMessageW(value_, msg, (hwnd::wparam_type)wparam, (hwnd::lparam_type)lparam) != FALSE);
			}

			template <typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			bool post_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()){
				return (value_ != nullptr && ::PostMessageW(value_, msg, (hwnd::wparam_type)wparam, (hwnd::lparam_type)lparam) != FALSE);
			}

			static hwnd get_active();

			static rect_type adjust_rect(rect_type value, dword_type styles, dword_type extended_styles, bool has_menu);
		};
	}
}

#endif /* !GRAFEEX_HWND_WRAPPER_H */
