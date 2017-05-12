#pragma once

#ifndef GRAFEEX_WINDOW_MANAGER_H
#define GRAFEEX_WINDOW_MANAGER_H

#include <mutex>
#include <memory>
#include <list>

#include "../common/hook.h"
#include "../common/random_string.h"

#include "../wrappers/hwnd_wrapper.h"
#include "../wrappers/msg_wrapper.h"
#include "../wrappers/wnd_class_wrapper.h"

#include "../messaging/message_event.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace application{
		class object;

		class window_manager{
		public:
			typedef ::INT_PTR dialog_return_type;
			typedef ::WNDPROC procedure_type;

			typedef ::HHOOK hook_type;
			typedef ::CBT_CREATEWND create_hook_info_type;
			typedef ::FLASHWINFO flash_info_type;

			typedef ::LRESULT result_type;
			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;

			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;
			typedef ::UINT_PTR uint_ptr_type;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::rect rect_type;

			typedef wrappers::msg msg_type;
			typedef wrappers::wnd_class wnd_class_type;

			typedef wrappers::hwnd hwnd_type;
			typedef hwnd_type::create_info_type create_info_type;

			typedef std::list<hwnd_type> hwnd_list_type;
			typedef std::recursive_mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;

			typedef window::object window_type;
			typedef messaging::message_event message_event_type;

			enum class beep_type : uint_type{
				default			= MB_OK,
				simple			= 0xffffffff,
				info			= MB_ICONINFORMATION,
				warning			= MB_ICONWARNING,
				error			= MB_ICONERROR,
				question		= MB_ICONQUESTION,
			};

			explicit window_manager(object &app_instance);

			virtual ~window_manager();

			virtual void on_nc_create(window_type &target, const hwnd_type &owner);

			virtual void on_create(window_type &target);

			virtual void on_nc_destroy(window_type &target);

			virtual void on_close(window_type &target);

			virtual void on_changed_position(window_type &target, uint_type flags);

			virtual void focus(window_type &target);

			virtual void blur(window_type &target);

			virtual bool flash(window_type &target, beep_type beep = beep_type::warning, uint_type count = 5) const;

			virtual bool flash_only(window_type &target, uint_type count = 5) const;

			virtual bool modal_consume(const msg_type &msg, window_type &target) const;

			virtual bool modal_consume(const msg_type &msg) const;

			virtual bool is_ancestor(const window_type &offspring, const window_type &ancestor) const;

			virtual bool is_related(const window_type &target, const window_type &with) const;

			virtual window_type *top_ancestor(const window_type &target) const;

			static window_manager *instance;
			static object *app_instance;

		protected:
			friend class object;

			virtual hwnd_type create_(window_type &owner, const create_info_type &info);

			static result_type CALLBACK entry_(hwnd_type::value_type window_handle, uint_type msg, wparam_type wparam, lparam_type lparam);

			static result_type CALLBACK hook_(int code, wparam_type wparam, lparam_type lparam);

			static result_type CALLBACK msg_hook_(int code, wparam_type wparam, lparam_type lparam);
			
			wnd_class_type class_;
			wnd_class_type dialog_class_;

			hwnd_list_type windows_;
			hwnd_list_type top_level_windows_;

			window_type *active_dialog_;
			void *recent_owner_;

			hook_type msg_hook_value_;
			mutable lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_MANAGER_H */
