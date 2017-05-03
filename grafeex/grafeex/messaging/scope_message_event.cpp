#include "scope_message_event.h"
#include "../window/dialog_window.h"
#include "../controls/control_object.h"

grafeex::messaging::scope_event::scope_event(object &value)
	: message_event(value){}

grafeex::messaging::scope_event::~scope_event() = default;

grafeex::messaging::message_event &grafeex::messaging::scope_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_scope(*this);
	return *this;
}

grafeex::messaging::nc_create_event::nc_create_event(object &value)
	: scope_event(value){}

grafeex::messaging::nc_create_event::~nc_create_event() = default;

grafeex::messaging::message_event &grafeex::messaging::nc_create_event::dispatch(){
	object_->target()->value_ = object_->info().owner();
	object_->target()->initialize_();

	if (scope_event::dispatch().is_propagating())
		*this << object_->target()->on_nc_create(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		*this << dynamic_cast<window::object::event_tunnel *>(get_event_())->create_event_.fire(e, object_->value() != FALSE);
		if (e.default_is_prevented())
			*this << false;
	}

	return *this;
}

bool grafeex::messaging::nc_create_event::is_create() const{
	return true;
}

bool grafeex::messaging::nc_create_event::is_client() const{
	return false;
}

grafeex::messaging::create_event::create_event(object &value)
	: scope_event(value){}

grafeex::messaging::create_event::~create_event() = default;

grafeex::messaging::message_event &grafeex::messaging::create_event::dispatch(){
	auto target = object_->target();

	target->system_menu_ = std::make_shared<menu::shared>(object_->info().owner(), menu::shared::option::system);
	target->system_menu_->init_();

	if (target->parent() == nullptr && dynamic_cast<window::controls::object *>(target) == nullptr){//Add to top level list
		application::object::instance->lock_.lock();
		application::object::instance->top_level_windows_.push_back(object_->info().owner());
		application::object::instance->lock_.unlock();
	}

	if (scope_event::dispatch().is_propagating())
		*this << target->on_create(*this);

	return *this;
}

bool grafeex::messaging::create_event::is_create() const{
	return true;
}

bool grafeex::messaging::create_event::is_client() const{
	return true;
}

grafeex::messaging::message_event::result_type grafeex::messaging::create_event::value_from_bool_(bool value){
	return (value ? 0 : -1);
}

grafeex::messaging::nc_destroy_event::nc_destroy_event(object &value)
	: scope_event(value){}

grafeex::messaging::nc_destroy_event::~nc_destroy_event() = default;

grafeex::messaging::message_event &grafeex::messaging::nc_destroy_event::dispatch(){
	auto target = object_->target();
	if (scope_event::dispatch().is_propagating())
		target->on_nc_destroy(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*target, *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->destroy_event_.fire(e);
	}

	target->uninitialize_();
	target->unsync_();
	target->reset_persistent_styles_();

	target->system_menu_ = nullptr;
	target->menu_ = nullptr;//Destroy menu
	target->value_ = nullptr;//Reset
	target->renderer_ = nullptr;//Release renderer
	target->mouse_state_.object_info_.parent = nullptr;

	auto tree_parent = dynamic_cast<gui::object_tree *>(target->parent());
	if (tree_parent != nullptr)//Remove from parent
		tree_parent->remove(*target);

	if (target->parent() == nullptr){
		application::object::instance->lock_.lock();

		auto &list = application::object::instance->top_level_windows_;
		auto entry = std::find(list.begin(), list.end(), object_->info().owner());
		if (entry != list.end())//Remove from top level list
			list.erase(entry);

		application::object::instance->lock_.unlock();
	}

	if (application::object::instance->active_dialog_ == target)
		application::object::instance->active_dialog_ = nullptr;

	return *this;
}

bool grafeex::messaging::nc_destroy_event::is_create() const{
	return false;
}

bool grafeex::messaging::nc_destroy_event::is_client() const{
	return false;
}

grafeex::messaging::destroy_event::destroy_event(object &value)
	: scope_event(value){}

grafeex::messaging::destroy_event::~destroy_event() = default;

grafeex::messaging::message_event &grafeex::messaging::destroy_event::dispatch(){
	if (scope_event::dispatch().is_propagating())
		object_->target()->on_destroy(*this);
	return *this;
}

bool grafeex::messaging::destroy_event::is_create() const{
	return false;
}

bool grafeex::messaging::destroy_event::is_client() const{
	return true;
}
