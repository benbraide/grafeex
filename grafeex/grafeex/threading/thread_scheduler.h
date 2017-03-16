#pragma once

#ifndef GRAFEEX_THREAD_SCHEDULER_H
#define GRAFEEX_THREAD_SCHEDULER_H

#include <mutex>
#include <functional>
#include <list>
#include <map>

#include "thread_id.h"

namespace grafeex{
	namespace threading{
		class scheduler{
		public:
			typedef std::recursive_mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;
			
			typedef std::function<void()> task_type;
			typedef std::list<task_type> list_type;
			typedef std::map<int, list_type> task_list_type;

			scheduler();

			void add(task_type task, int priority = 0);

			void execute();

			void execute_all();

			bool has_tasks() const;

		protected:
			id id_;
			task_list_type task_list_;
			lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_SCHEDULER_H */
