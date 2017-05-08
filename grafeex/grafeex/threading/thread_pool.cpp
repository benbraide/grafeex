#include "thread_pool.h"

grafeex::threading::pool::pool()
	: min_(0), max_(0), free_count_(0), thread_count_(0), destruct_(false){}

grafeex::threading::pool::pool(size_type min_size, size_type max_size)
	: min_(min_size), max_(max_size), free_count_(0), thread_count_(0), destruct_(false){}

grafeex::threading::pool::~pool(){
	lock_.lock();
	{//Stop processing
		destruct_ = true;
		min_ = max_ = 0;
		condition_.notify_all();
	}
	
	lock_.unlock();
	for (auto i = 0; !threads_.empty() && i < (GTP_POLL_TIMEOUT / GTP_POLL_SLEEP); ++i)
		::Sleep(GTP_POLL_SLEEP);//Poll for threads termination
}

void grafeex::threading::pool::stop(){
	update_sizes(0, 0);
}

void grafeex::threading::pool::update_sizes(size_type min_size, size_type max_size){
	guard_type guard(lock_);
	min_ = max_ = 0;
	condition_.notify_all();
}

bool grafeex::threading::pool::add(task_type task, bool is_persistent){
	guard_type guard(lock_);
	if (destruct_ || max_ == 0u)
		return false;

	if (is_persistent)
		return add_persistent_(task);

	if (free_count_ > 0u || thread_count_ >= max_){//Wake one or more threads
		tasks_.push_back(task);
		condition_.notify_all();
	}
	else{//Add new thread
		do_run_(task, &pool::run_);
		++thread_count_;
	}

	return true;
}

grafeex::threading::pool::size_type grafeex::threading::pool::min_size() const{
	return min_;
}

grafeex::threading::pool::size_type grafeex::threading::pool::max_size() const{
	return max_;
}

bool grafeex::threading::pool::has_tasks() const{
	return !tasks_.empty();
}

bool grafeex::threading::pool::add_persistent_(task_type task){
	do_run_(task, &pool::run_persistent_);
	return true;
}

void grafeex::threading::pool::do_run_(task_type task, run_method_type method){
	auto empty_thread = threads_.emplace(threads_.end());//Emplace an empty thread
	thread_type thread([this, empty_thread, task, method](){
		(this->*method)(empty_thread, task);
	});

	*empty_thread = std::move(thread);//Move into empty
}

void grafeex::threading::pool::run_(thread_iterator_type thread, task_type task){
	task();//Execute task

	unique_guard_type guard(lock_);
	while (!destruct_ && max_ > 0u){
		while (!destruct_ && !tasks_.empty()){
			task = *tasks_.begin();
			tasks_.pop_front();//Remove task from list

			condition_.notify_all();
			guard.unlock();

			task();//Execute task
			guard.lock();
		}

		if (!destruct_ && thread_count_ <= min_){//Wait for next task
			++free_count_;
			condition_.wait(guard, [this]{
				return (destruct_ || max_ == 0u || !tasks_.empty());
			});

			--free_count_;
			if (thread_count_ > min_)
				break;//End thread
		}
		else//End thread
			break;
	}

	thread->detach();
	threads_.erase(thread);
	--thread_count_;
}

void grafeex::threading::pool::run_persistent_(thread_iterator_type thread, task_type task){
	task();//Execute task
	lock_.lock();

	thread->detach();
	threads_.erase(thread);

	lock_.unlock();
}
