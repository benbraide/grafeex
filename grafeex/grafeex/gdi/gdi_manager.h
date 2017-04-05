#pragma once

#ifndef GRAFEEX_GDI_MANAGER_H
#define GRAFEEX_GDI_MANAGER_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include <list>

#include "../common/hook.h"
#include "gdi_object.h"

namespace grafeex{
	namespace application{
		class object;
	}

	namespace gdi{
		class manager{
		public:
			typedef ::HWND hwnd_type;
			typedef ::HDC dc_type;
			typedef ::HRGN rgn_type;

			typedef ::HINSTANCE instance_type;
			typedef const ::DEVMODEW *dev_mode_type;

			typedef ::BOOL bool_type;
			typedef ::DWORD dword_type;
			typedef ::LPCWSTR string_type;

			typedef object::value_type value_type;

			typedef std::shared_ptr<common::hook_interface> hook_type;
			typedef std::list<hook_type> hook_list_type;

			typedef std::list<value_type> object_list_type;

			struct dc_info{
				bool unknown;
				hwnd_type owner;
				object_list_type object_list;
			};

			struct object_info{
				bool deleted;
				object_list_type object_list;
			};

			typedef std::unordered_map<value_type, object *> owner_cache_type;
			typedef std::unordered_map<value_type, dc_info> dc_cache_type;
			typedef std::unordered_map<value_type, object_info> object_cache_type;

			typedef std::mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;

			static void init();

			static void uninit();

			static object *owner(value_type value);

		private:
			friend class object;
			friend class application::object;

			static void remove_dc_from_objects_(value_type dc, object_list_type &list);

			static hook_list_type hook_list_;
			static owner_cache_type owner_cache_;
			static dc_cache_type dc_cache_;
			static object_cache_type object_cache_;
			static lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_GDI_MANAGER_H */
