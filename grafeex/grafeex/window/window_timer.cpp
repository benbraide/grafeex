#include "window_timer.h"
#include "window_object.h"

grafeex::window::timer::timer()
	: owner_(nullptr), id_(reinterpret_cast<uint_ptr_type>(this)), duration_(0){}

grafeex::window::timer::timer(object &owner, uint_type duration)
	: owner_(nullptr), id_(reinterpret_cast<uint_ptr_type>(this)), duration_(0){
	create(owner, duration);
}

grafeex::window::timer::~timer(){
	destroy();
}

bool grafeex::window::timer::create(object &owner, uint_type duration){
	if (is_created() || application::object::instance->set_timer(owner, id_, duration) == static_cast<uint_ptr_type>(0))
		return false;

	owner_ = &owner;
	duration_ = duration;
	application::object::instance->cache_timer(id_, *this);

	return true;
}

bool grafeex::window::timer::destroy(){
	if (!is_created() || !application::object::instance->kill_timer(*owner_, id_))
		return false;

	application::object::instance->remove_timer(id_);
	owner_ = nullptr;
	duration_ = 0;

	return true;
}

bool grafeex::window::timer::is_created() const{
	return (owner_ != nullptr);
}

grafeex::window::object *grafeex::window::timer::owner() const{
	return owner_;
}

grafeex::window::timer::uint_ptr_type grafeex::window::timer::id() const{
	return id_;
}

grafeex::window::timer::uint_type grafeex::window::timer::duration() const{
	return duration_;
}
