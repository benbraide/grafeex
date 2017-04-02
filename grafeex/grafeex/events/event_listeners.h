#pragma once

#ifndef GRAFEEX_EVENT_LISTENERS_H
#define GRAFEEX_EVENT_LISTENERS_H

#include <mutex>
#include <functional>

#include "../common/random_number.h"
#include "event_entry.h"

namespace grafeex{
	namespace events{
		template <class owner_type, class return_type, class... value_types>
		class listeners{
		public:
			typedef owner_type owner_type;
			typedef return_type return_type;

			typedef entry entry_type;
			typedef entry_hasher hasher_type;

			typedef std::function<return_type(value_types...)> callback_type;
			typedef std::function<return_type()> no_args_callback_type;

			typedef std::recursive_mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;

			typedef std::unordered_map<entry_type, callback_type, hasher_type> list_type;

			typedef entry::group_type group_type;
			typedef entry::value_type value_type;

			typedef common::basic_random_number<value_type> random_engine_type;

			listeners()
				: group_(reinterpret_cast<group_type>(this)){}

			entry_type add(callback_type callback){
				guard_type guard(lock_);

				entry_type entry(group_, id_generator_.generate(1, std::numeric_limits<value_type>::max()));
				while (list_.find(entry) != list_.end())//Ensure id is unique
					entry.value_ = id_generator_.generate(1, std::numeric_limits<value_type>::max());

				list_[entry] = callback;
				return entry;
			}

			template <typename T = return_type>
			std::enable_if_t<!std::is_same<std::function<T()>, callback_type>::value, entry_type> add(no_args_callback_type callback){
				return add_(callback);
			}

			listeners &remove(const entry_type &entry){
				guard_type guard(lock_);
				list_.erase(entry);
				return *this;
			}

			bool empty() const{
				return list_.empty();
			}

		private:
			friend owner_type;

			template <typename T = return_type>
			std::enable_if_t<std::is_same<T, void>::value, entry_type> add_(no_args_callback_type callback){
				return add([callback](value_types...){
					callback();
				});
			}

			template <typename T = return_type>
			std::enable_if_t<!std::is_same<T, void>::value, entry_type> add_(no_args_callback_type callback){
				return add([callback](value_types...) -> return_type{
					return callback();
				});
			}

			group_type group_;
			list_type list_;
			random_engine_type id_generator_;
			lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_EVENT_LISTENERS_H */
