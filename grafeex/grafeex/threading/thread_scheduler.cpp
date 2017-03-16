#include "thread_scheduler.h"

grafeex::threading::scheduler::scheduler()
	: id_(get_current_id()){}

void grafeex::threading::scheduler::add(task_type task, int priority){
	guard_type guard(lock_);
	if (get_current_id() == id_)
		task();//Same thread -- execute

	task_list_[-priority].emplace_back(task);//Higher priority moves front
}

void grafeex::threading::scheduler::execute(){
	guard_type guard(lock_);
	if (task_list_.empty() || get_current_id() != id_)
		return;//Empty list or different thread -- reject

	auto list = task_list_.begin();
	(*list->second.begin())();//Execute

	if (list->second.size() == 1u)
		task_list_.erase(list);
	else//Remove from list
		list->second.pop_front();
}

void grafeex::threading::scheduler::execute_all(){
	guard_type guard(lock_);
	if (get_current_id() != id_)
		return;//Different thread -- reject

	for (auto &list : task_list_){
		for (auto &task : list.second){
			task();
		}
	}

	task_list_.clear();
}

bool grafeex::threading::scheduler::has_tasks() const{
	return !task_list_.empty();
}
