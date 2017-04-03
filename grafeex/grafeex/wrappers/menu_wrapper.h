#pragma once

#ifndef GRAFEEX_MENU_WRAPPER_H
#define GRAFEEX_MENU_WRAPPER_H

#include "../common/windows_headers.h"
#include "../common/preprocessor.h"

#include "pointer_wrapper.h"

namespace grafeex{
	namespace wrappers{
		class menu : public pointer<::HMENU, menu>{
		public:
			typedef pointer<::HMENU, menu> base_type;

			typedef ::MENUINFO info_type;
			typedef ::HBRUSH brush_type;

			typedef ::ULONG_PTR ulong_ptr_type;
			typedef ::DWORD dword_type;
			typedef ::UINT uint_type;

			explicit menu(value_type value);

			bool destroy();

			bool set(const info_type &info);

			template <typename... types>
			bool set(types... values){
				info_type info{ sizeof(info_type) };
				unwind_(info, values...);
				return set(info);
			}

			bool styles(dword_type value, bool apply_to_submenus = false);

			dword_type styles() const;

			bool max_height(uint_type value, bool apply_to_submenus = false);

			uint_type max_height() const;

			bool background_brush(brush_type value, bool apply_to_submenus = false);

			brush_type background_brush() const;

			bool context_help_id(dword_type value);

			dword_type context_help_id() const;

			bool data(ulong_ptr_type value);

			template <typename value_type = ulong_ptr_type>
			value_type data() const{
				info_type info;
				get_(info, MIM_MENUDATA);
				return (value_type)info.dwMenuData;
			}

			int count() const;

		protected:
			template <typename... types>
			void unwind_(info_type &info, bool apply_to_submenus, types... values){
				if (apply_to_submenus)
					GRAFEEX_SET(info.fMask, MIM_APPLYTOSUBMENUS);
				else
					GRAFEEX_REMOVE(info.fMask, MIM_APPLYTOSUBMENUS);

				unwind_(info, values...);
			}

			template <typename... types>
			void unwind_(info_type &info, dword_type styles, types... values){
				GRAFEEX_SET(info.fMask, MIM_STYLE);
				info.dwStyle = styles;
				unwind_(info, values...);
			}

			template <typename... types>
			void unwind_(info_type &info, brush_type background_brush, types... values){
				GRAFEEX_SET(info.fMask, MIM_BACKGROUND);
				info.hbrBack = background_brush;
				unwind_(info, values...);
			}

			template <typename... types>
			void unwind_(info_type &info, ulong_ptr_type data, types... values){
				GRAFEEX_SET(info.fMask, MIM_MENUDATA);
				info.dwMenuData = data;
				unwind_(info, values...);
			}

			template <typename... types>
			void unwind_(info_type &info){}

			void get_(info_type &info, dword_type masks) const;
		};
	}
}

#endif /* !GRAFEEX_MENU_WRAPPER_H */
