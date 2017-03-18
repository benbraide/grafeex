#pragma once

#ifndef GRAFEEX_APPLICATION_OBJECT_H
#define GRAFEEX_APPLICATION_OBJECT_H

#include <atomic>
#include <memory>
#include <list>
#include <unordered_map>

#include "../common/random_string.h"
#include "../wrappers/wnd_class_wrapper.h"
#include "../threading/thread_object.h"

#include "../messaging/message_event_dispatcher.h"
#include "../messaging/scope_message_event.h"
#include "../messaging/close_message_event.h"
#include "../messaging/state_message_event.h"
#include "../messaging/style_message_event.h"
#include "../messaging/visibility_message_event.h"
#include "../messaging/painting_message_event.h"

namespace grafeex{
	namespace window{
		class object;
	}

	namespace application{
		class object : public threading::object{
		public:
			typedef ::INT_PTR dialog_return_type;
			typedef ::HHOOK hook_type;
			typedef ::CBT_CREATEWND create_hook_info_type;

			typedef ::LRESULT result_type;
			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;

			typedef ::UINT uint_type;
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;

			typedef std::list<wrappers::hwnd> hwnd_list_type;
			typedef std::shared_ptr<messaging::event_dispatcher_base> dispatcher_type;
			typedef std::unordered_map<uint_type, dispatcher_type> dispatcher_list_type;

			typedef structures::point point_type;
			typedef window::object window_type;
			typedef wrappers::wnd_class wnd_class_type;
			typedef wrappers::hwnd hwnd_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef hwnd_type::create_info_type create_info_type;
			typedef threading::object base_type;

			struct stored_message_info_type{
				bool is_active;
				dword_type time;
				point_type mouse_position;
			};

			template <typename... types>
			object(types... class_args)
				: instance_(nullptr), recent_owner_(nullptr){
				typedef std::wstring::size_type size_type;

				class_.set(class_args...);
				if ((instance_ = class_.instance()) == nullptr)
					class_.instance(instance_ = ::GetModuleHandleW(nullptr));

				common::random_string random_string;
				if (class_.name().empty())//Use a random string
					class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));

				if (class_.create()){//Create dialog class
					::GetClassInfoExW(nullptr, L"#32770", dialog_class_);
					dialog_class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));
					dialog_class_.instance(instance_);
					dialog_class_.create();
				}

				create_dispatchers_();
				instance = this;
			}

			virtual ~object();

			virtual void quit(int exit_code = 0);

			virtual hwnd_type create(window_type &owner, const create_info_type &info);

			//virtual hwnd_type create(window_type &owner, const gui::dialog_info &info, bool modal = false);

			virtual instance_type get_instance() const;

			template <typename return_type>
			return_type execute(std::function<return_type()> method, int priority = 0){
				return execute_(std::integral_constant<bool, std::is_same<return_type, void>::value>(), method, priority);
			}

			void schedule(std::function<void()> method, int priority = 0){
				scheduler_.add(method, priority);
			}

			static result_type CALLBACK entry(hwnd_type::value_type window_handle, uint_type msg, wparam_type wparam, lparam_type lparam);

			template <typename object_type, typename return_type, typename function_type, typename... value_types>
			return_type call(function_type method, object_type &object, const value_types &... values){
				return (object.*method)(values...);
			}

			template <typename object_type, typename return_type, typename function_type, typename... value_types>
			return_type call_val_args(function_type method, object_type &object, value_types... values){
				return (object.*method)(values...);
			}

			stored_message_info_type stored_message_info = {};
			static object *instance;

		protected:
			virtual bool is_filtered_message_() const override;

			virtual void dispatch_() override;

			virtual bool is_stopped_() const override;

			virtual bool is_dialog_message_();

			virtual hwnd_type create_(window_type &owner, const create_info_type &info);

			//virtual hwnd_type create_(window_type &owner, const gui::dialog_info &info, bool modal = false);

			template <typename return_type>
			return_type execute_(std::false_type, std::function<return_type()> method, int priority){
				return_type value;
				if (threading::get_current_id() != id_){
					threading::event_object ready(L"");
					scheduler_.add([&]{
						value = method();
						ready.set();
					}, priority);

					queue_.wake_wait();//Release message loop
					ready.wait();
				}
				else//Same thread
					value = method();

				return value;
			}

			template <typename return_type>
			return_type execute_(std::true_type, std::function<return_type()> method, int priority){
				if (threading::get_current_id() != id_){
					threading::event_object ready(L"");
					scheduler_.add([&]{
						method();
						ready.set();
					}, priority);

					queue_.wake_wait();//Release message loop
					ready.wait();
				}
				else//Same thread
					method();
			}

			virtual void create_dispatchers_();

			static result_type CALLBACK hook_(int code, wparam_type wparam, lparam_type lparam);

			wnd_class_type class_, dialog_class_;
			hwnd_list_type top_level_windows_;
			hwnd_type active_dialog_;
			instance_type instance_;
			dispatcher_list_type dispatcher_list_;
			void *recent_owner_;
		};
	}
}

#endif /* !GRAFEEX_APPLICATION_OBJECT_H */
