#pragma once

#ifndef GRAFEEX_HOOK_H
#define GRAFEEX_HOOK_H

#include <easyhook.h>

#include "../common/preprocessor.h"
#include "windows_headers.h"

namespace grafeex{
	namespace common{
		enum class hook_function_call_type{
			nil,
			windows,
			std,
			fast,
			c,
			cpp,
			vector,
		};

		enum class hook_state : unsigned int{
			nil				= (0 << 0x0000),
			set				= (1 << 0x0000),
			hooked			= (1 << 0x0001),
		};

		GRAFEEX_MAKE_OPERATORS(hook_state)

		class hook_interface{
		public:
			virtual ~hook_interface(){}

			virtual bool hook() = 0;

			virtual bool unhook() = 0;

			virtual bool is_set() const = 0;

			virtual bool is_hooked() const = 0;
		};

		template <class function_type>
		class basic_hook : public hook_interface{
		public:
			typedef hook_state state;
			typedef function_type function_type;

			typedef ::BYTE byte_type;
			typedef ::HINSTANCE instance_type;
			typedef ::HOOK_TRACE_INFO info_type;

			typedef const char *string_type;

			basic_hook(){}

			basic_hook(const wchar_t *module, string_type target, function_type detour){
				set(module, target, detour);
			}

			basic_hook(instance_type module, string_type target, function_type detour){
				set(module, target, detour);
			}

			basic_hook(function_type original, function_type detour){
				set(original, detour);
			}

			~basic_hook(){
				unhook();
			}

			virtual bool set(const wchar_t *module, string_type target, function_type detour){
				return set(::GetModuleHandleW(module), target, detour);
			}

			virtual bool set(instance_type module, string_type target, function_type detour){
				auto original = ::GetProcAddress(module, target);
				if (original == nullptr)
					return false;

				return set(reinterpret_cast<function_type>(original), detour);
			}

			virtual bool set(function_type original, function_type detour){
				if (is_set() || FAILED(::LhInstallHook(original, detour, nullptr, &info_)))
					return false;

				GRAFEEX_SET(states_, state::set);
				return true;
			}

			virtual bool hook() override{
				static unsigned long acl_entries[] = { 0 };
				if (!is_set() || is_hooked() || FAILED(::LhSetInclusiveACL(acl_entries, 1, &info_)))
					return false;

				GRAFEEX_SET(states_, state::hooked);
				return true;
			}

			virtual bool unhook() override{
				if (!is_hooked() || FAILED(::LhUninstallHook(&info_)))
					return false;

				::LhWaitForPendingRemovals();
				GRAFEEX_REMOVE(states_, state::set | state::hooked);

				return true;
			}

			virtual bool is_set() const override{
				return GRAFEEX_IS(states_, state::set);
			}

			virtual bool is_hooked() const override{
				return GRAFEEX_IS(states_, state::hooked);
			}
			
		private:
			info_type info_{};
			state states_ = state::nil;
		};

		template <hook_function_call_type call_type, class return_type, class... arg_types>
		class generic_hook;

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::nil, return_type, arg_types...> : public basic_hook<return_type(*)(arg_types...)>{
		public:
			typedef basic_hook<return_type(*)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::windows, return_type, arg_types...> : public basic_hook<return_type(WINAPI *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(WINAPI *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::std, return_type, arg_types...> : public basic_hook<return_type(__stdcall *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(__stdcall *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::fast, return_type, arg_types...> : public basic_hook<return_type(__fastcall *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(__fastcall *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::c, return_type, arg_types...> : public basic_hook<return_type(__cdecl *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(__cdecl *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::cpp, return_type, arg_types...> : public basic_hook<return_type(__thiscall *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(__thiscall *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		class generic_hook<hook_function_call_type::vector, return_type, arg_types...> : public basic_hook<return_type(__vectorcall *)(arg_types...)>{
		public:
			typedef basic_hook<return_type(__vectorcall *)(arg_types...)> base_type;

			template <typename... value_types>
			generic_hook(value_types... values)
				: base_type(values...){}
		};

		template <class return_type, class... arg_types>
		using default_hook = generic_hook<hook_function_call_type::nil, return_type, arg_types...>;

		template <class return_type, class... arg_types>
		using windows_hook = generic_hook<hook_function_call_type::windows, return_type, arg_types...>;

		template <class return_type, class... arg_types>
		using std_hook = generic_hook<hook_function_call_type::std, return_type, arg_types...>;

		template <class return_type, class... arg_types>
		using c_hook = generic_hook<hook_function_call_type::c, return_type, arg_types...>;

		template <class return_type, class... arg_types>
		using cpp_hook = generic_hook<hook_function_call_type::cpp, return_type, arg_types...>;

		template <class return_type, class... arg_types>
		using vector_hook = generic_hook<hook_function_call_type::vector, return_type, arg_types...>;
	}
}

#endif /* !GRAFEEX_HOOK_H */
