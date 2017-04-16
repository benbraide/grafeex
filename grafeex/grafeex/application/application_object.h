#pragma once

#ifndef GRAFEEX_APPLICATION_OBJECT_H
#define GRAFEEX_APPLICATION_OBJECT_H

#define GAPP_MAKE_DISPATCHER(d) std::make_shared<messaging::event_dispatcher<messaging::d> >()
#define GAPP_DISPATCH(e, d) dispatcher_list_[e] = GAPP_MAKE_DISPATCHER(d)

#include <atomic>
#include <memory>
#include <list>
#include <unordered_map>

#include "../common/com.h"
#include "../common/random_string.h"

#include "../structures/dialog_template.h"
#include "../wrappers/wnd_class_wrapper.h"
#include "../threading/thread_modal_loop.h"

#include "../messaging/message_event_dispatcher.h"
#include "../messaging/scope_message_event.h"
#include "../messaging/close_message_event.h"
#include "../messaging/state_message_event.h"
#include "../messaging/style_message_event.h"
#include "../messaging/visibility_message_event.h"
#include "../messaging/painting_message_event.h"
#include "../messaging/menu_message_event.h"
#include "../messaging/dimensions_message_event.h"
#include "../messaging/system_message_event.h"
#include "../messaging/timer_message_event.h"
#include "../messaging/command_message_event.h"
#include "../messaging/notify_message_event.h"
#include "../messaging/input_message_event.h"

#include "../gdi/gdi_manager.h"
#include "../d2d/d2d_factory.h"

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
			typedef ::UINT_PTR unit_ptr_type;

			typedef std::list<wrappers::hwnd> hwnd_list_type;

			typedef std::shared_ptr<messaging::event_dispatcher_base> dispatcher_type;
			typedef std::unordered_map<uint_type, dispatcher_type> dispatcher_list_type;
			typedef std::unordered_map<unit_ptr_type, window::timer *> timer_cache_type;

			typedef std::recursive_mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::dialog_template dialog_template_type;

			typedef window::object window_type;
			typedef wrappers::wnd_class wnd_class_type;
			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::value_type hwnd_value_type;

			typedef wnd_class_type::procedure_type procedure_type;
			typedef wnd_class_type::instance_type instance_type;

			typedef hwnd_type::create_info_type create_info_type;
			typedef threading::object base_type;

			typedef common::com com_type;
			typedef d2d::factory factory_type;

			typedef ::D2D1_SIZE_F d2d_size_type;
			typedef ::D2D1_POINT_2F d2d_point_type;

			enum class gdi_manager_state : unsigned int{
				nil				= (0 << 0x0000),
				active			= (1 << 0x0000),
				monitoring		= (1 << 0x0001),
			};

			struct stored_message_info_type{
				bool is_active;
				dword_type time;
				point_type mouse_position;
			};

			template <typename... types>
			object(types... class_args)
				: instance_(nullptr), active_dialog_(nullptr), recent_owner_(nullptr){
				typedef std::wstring::size_type size_type;

				instance = this;
				class_.set(entry, class_args...);
				if ((instance_ = class_.instance()) == nullptr)
					class_.instance(instance_ = ::GetModuleHandleW(nullptr));

				common::random_string random_string;
				if (class_.name().empty())//Use a random string
					class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));

				if (class_.create()){//Create dialog class
					::GetClassInfoExW(nullptr, L"#32770", dialog_class_);
					dialog_class_.procedure(entry);
					dialog_class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));
					dialog_class_.instance(instance_);
					dialog_class_.create();
				}

				d2d_factory->GetDesktopDpi(&d2d_dpi_scale.x, &d2d_dpi_scale.y);
				d2d_dpi_scale.x /= 96.0f;
				d2d_dpi_scale.y /= 96.0f;

				init_();
			}

			virtual ~object();

			virtual void quit(int exit_code = 0);

			virtual hwnd_type create(window_type &owner, const create_info_type &info);

			virtual unit_ptr_type set_timer(window_type &owner, unit_ptr_type id, uint_type duration);

			virtual bool kill_timer(window_type &owner, unit_ptr_type id);

			virtual instance_type get_instance() const;

			template <typename return_type>
			return_type execute(std::function<return_type()> method, int priority = 0){
				return execute_(std::integral_constant<bool, std::is_same<return_type, void>::value>(), method, priority);
			}

			void schedule(std::function<void()> method, int priority = 0){
				scheduler_.add(method, priority);
			}

			void enable_gdi_manager(bool monitor = true);

			void disable_gdi_manager(bool monitor_only = false);

			bool gdi_manager_is_enabled() const;

			bool gdi_manager_is_monitoring() const;

			static result_type CALLBACK entry(hwnd_type::value_type window_handle, uint_type msg, wparam_type wparam, lparam_type lparam);

			template <typename object_type, typename return_type, typename function_type, typename... value_types>
			return_type call(function_type method, object_type &object, const value_types &... values){
				return (object.*method)(values...);
			}

			template <typename object_type, typename return_type, typename function_type, typename... value_types>
			return_type call_val_args(function_type method, object_type &object, value_types... values){
				return (object.*method)(values...);
			}

			template <typename value_type = int>
			static float pixel_to_dip_x(value_type value){
				return (static_cast<float>(value) / d2d_dpi_scale.x);
			}

			template <typename value_type = int>
			static float pixel_to_dip_y(value_type value){
				return (static_cast<float>(value) / d2d_dpi_scale.y);
			}

			template <typename value_type = int>
			static value_type dip_to_pixel_x(float value){
				return static_cast<value_type>(value * d2d_dpi_scale.x);
			}

			template <typename value_type = int>
			static value_type dip_to_pixel_y(float value){
				return static_cast<value_type>(value * d2d_dpi_scale.y);
			}

			stored_message_info_type stored_message_info = {};

			static object *instance;
			static factory_type d2d_factory;
			static d2d_point_type d2d_dpi_scale;

		protected:
			friend class threading::modal_loop;

			friend class messaging::create_event;
			friend class messaging::nc_destroy_event;
			friend class messaging::activate_event;
			friend class messaging::activate_app_event;
			friend class messaging::timer_event;
			friend class messaging::command_event;
			friend class messaging::notify_event;

			friend class window::timer;

			virtual bool is_filtered_message_() const override;

			virtual void dispatch_() override;

			virtual bool is_stopped_() const override;

			virtual bool is_dialog_message_();

			virtual result_type dispatch_(msg_type &msg, bool is_sent, window_type &target);

			virtual void init_();

			virtual hwnd_type create_(window_type &owner, const create_info_type &info);

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

			virtual void app_activate_(messaging::activate_app_event &e);

			static result_type CALLBACK hook_(int code, wparam_type wparam, lparam_type lparam);

			com_type com_;
			gdi_manager_state gdi_manager_states_;
			
			wnd_class_type class_;
			wnd_class_type dialog_class_;

			hwnd_list_type top_level_windows_;
			window_type *active_dialog_;
			instance_type instance_;

			dispatcher_type unhandled_dispatcher_;
			dispatcher_list_type dispatcher_list_;
			timer_cache_type timer_cache_;
			void *recent_owner_;

			mutable lock_type lock_;
		};

		GRAFEEX_MAKE_OPERATORS(object::gdi_manager_state)
	}
}

#endif /* !GRAFEEX_APPLICATION_OBJECT_H */
