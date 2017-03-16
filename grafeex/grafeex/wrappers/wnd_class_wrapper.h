#pragma once

#ifndef GRAFEEX_WND_CLASS_WRAPPER_H
#define GRAFEEX_WND_CLASS_WRAPPER_H

#include <string>

#include "../common/windows_headers.h"
#include "value_wrapper.h"

namespace grafeex{
	namespace wrappers{
		class wnd_class : public value<::WNDCLASSEXW, wnd_class>{
		public:
			typedef value<::WNDCLASSEXW, wnd_class> base_type;

			typedef ::WNDPROC procedure_type;
			typedef ::HINSTANCE instance_type;

			typedef ::UINT styles_type;
			typedef ::ATOM id_type;

			typedef ::HICON icon_type;
			typedef ::HCURSOR cursor_type;
			typedef ::HBRUSH brush_type;

			wnd_class();

			template <typename... types>
			wnd_class(types... args)
				: base_type(value_type{ sizeof(value_type) }), id_(0){
				unwind_(args...);
				create();
			}

			virtual ~wnd_class();

			operator const wchar_t *() const;

			template <typename... types>
			wnd_class &set(types... args){
				if (!is_created())
					unwind_(args...);
				return *this;
			}

			wnd_class &name(const std::wstring &value);

			const std::wstring &name() const;

			wnd_class &styles(styles_type value);

			styles_type styles() const;

			wnd_class &procedure(procedure_type value);

			procedure_type procedure() const;

			wnd_class &instance(instance_type value);

			instance_type instance() const;

			wnd_class &background_brush(brush_type value);

			brush_type background_brush() const;

			wnd_class &cursor(cursor_type value);

			cursor_type cursor() const;

			wnd_class &icon(icon_type value);

			icon_type icon() const;

			wnd_class &small_icon(icon_type value);

			icon_type small_icon() const;

			wnd_class &menu(const std::wstring &value);

			const std::wstring &menu() const;

			virtual bool create();

			virtual bool destroy();

			virtual bool is_created() const;

		private:
			template <typename... types>
			void unwind_(const wchar_t *string, types... args){
				if (value_.lpszClassName == nullptr)//Set name
					value_.lpszClassName = (name_ = string).c_str();
				else//Set menu
					value_.lpszMenuName = (menu_ = string).c_str();

				unwind_(args...);
			}

			template <typename... types>
			void unwind_(std::wstring string, types... args){
				if (value_.lpszClassName == nullptr)//Set name
					value_.lpszClassName = (name_ = std::move(string)).c_str();
				else//Set menu
					value_.lpszMenuName = (menu_ = std::move(string)).c_str();

				unwind_(args...);
			}

			template <typename... types>
			void unwind_(procedure_type procedure, types... args){
				value_.lpfnWndProc = procedure;
				unwind_(args...);
			}

			template <typename... types>
			void unwind_(instance_type instance, types... args){
				value_.hInstance = instance;
				unwind_(args...);
			}

			template <typename... types>
			void unwind_(std::nullptr_t instance, types... args){
				value_.hInstance = instance;
				unwind_(args...);
			}

			template <typename... types>
			void unwind_(styles_type styles, types... args){
				value_.style = styles;
				unwind_(args...);
			}

			template <typename... types>
			void unwind_(icon_type icon, types... args){
				if (value_.hCursor == nullptr)
					value_.hCursor = icon;
				else if (value_.hIcon == nullptr)
					value_.hIcon = icon;
				else
					value_.hIconSm = icon;

				unwind_(args...);
			}

			template <typename... types>
			void unwind_(brush_type brush, types... args){
				value_.hbrBackground = brush;
				unwind_(args...);
			}

			template <typename... types>
			void unwind_(){}

			id_type id_;
			std::wstring name_, menu_;
		};
	}
}

#endif /* !GRAFEEX_WND_CLASS_WRAPPER_H */
