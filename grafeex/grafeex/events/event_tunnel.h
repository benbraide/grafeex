#pragma once

#ifndef GRAFEEX_EVENT_TUNNEL_H
#define GRAFEEX_EVENT_TUNNEL_H

#include "event_object.h"
#include "event_listeners.h"

namespace grafeex{
	namespace events{
		class tunnel_interface{
		public:
			virtual ~tunnel_interface() = default;

			virtual tunnel_interface &remove(const entry &entry) = 0;
		};

		template <class return_type, class object_type = object>
		class tunnel : public tunnel_interface{
		public:
			typedef return_type return_type;
			typedef object_type object_type;

			typedef listeners<tunnel, return_type, object_type &> listeners_type;

			typedef typename listeners_type::group_type group_type;
			typedef typename listeners_type::entry_type entry_type;
			typedef typename listeners_type::guard_type guard_type;

			typedef typename listeners_type::callback_type callback_type;
			typedef typename listeners_type::no_args_callback_type no_args_callback_type;

			virtual ~tunnel() = default;

			template <typename... value_types>
			entry_type add(std::function<return_type(value_types &...)> callback){
				return listeners_.add(callback);
			}

			virtual tunnel &remove(const entry_type &entry) override{
				listeners_.remove(entry);
				return *this;
			}

			bool empty() const{
				return listeners_.empty();
			}

			group_type group() const{
				return listeners_.group_;
			}

			template <typename T = return_type>
			std::enable_if_t<std::is_same<T, void>::value, T> fire(object_type &e){
				guard_type guard(listeners_.lock_);
				for (auto &item : listeners_.list_){
					item.second(e);
					if (!e.is_propagating())
						break;
				}
			}

			template <typename T = return_type>
			std::enable_if_t<!std::is_same<T, void>::value, T> fire(object_type &e, T default_value = T()){
				guard_type guard(listeners_.lock_);
				for (auto &item : listeners_.list_){
					default_value = item.second(e);
					if (!e.is_propagating())
						break;
				}

				return default_value;
			}

		private:
			listeners_type listeners_;
		};
	}
}

#endif /* !GRAFEEX_EVENT_TUNNEL_H */
