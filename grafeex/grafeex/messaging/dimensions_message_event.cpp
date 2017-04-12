#include "dimensions_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::position_event::position_event(object &value)
	: message_event(value){}

grafeex::messaging::position_event::~position_event(){}

grafeex::messaging::message_event &grafeex::messaging::position_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_position_change(*this);
	return *this;
}

grafeex::messaging::position_event::info_type &grafeex::messaging::position_event::info() const{
	return *object_->info().lparam<info_type *>();
}

grafeex::messaging::changing_position_event::changing_position_event(object &value)
	: position_event(value){}

grafeex::messaging::changing_position_event::~changing_position_event(){}

grafeex::messaging::message_event &grafeex::messaging::changing_position_event::dispatch(){
	if (position_event::dispatch().is_propagating())
		*this << object_->target()->on_position_changing(*this);
	return *this;
}

bool grafeex::messaging::changing_position_event::is_changing() const{
	return true;
}

grafeex::messaging::changed_position_event::changed_position_event(object &value)
	: position_event(value){}

grafeex::messaging::changed_position_event::~changed_position_event(){}

grafeex::messaging::message_event &grafeex::messaging::changed_position_event::dispatch(){
	if (position_event::dispatch().is_propagating())
		object_->target()->on_position_changed(*this);

	auto flags = info().flags;
	if (!GRAFEEX_IS(flags, SWP_NOSIZE))
		object_->target()->sized_();

	if (!GRAFEEX_IS(flags, SWP_NOMOVE))
		object_->target()->moved_();

	return *this;
}

bool grafeex::messaging::changed_position_event::is_changing() const{
	return false;
}

grafeex::messaging::movement_event::movement_event(object &value)
	: message_event(value){}

grafeex::messaging::movement_event::~movement_event(){}

grafeex::messaging::message_event &grafeex::messaging::movement_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_movement_change(*this);
	return *this;
}

grafeex::messaging::changing_movement_event::changing_movement_event(object &value)
	: movement_event(value), info_(value.info().lparam<info_type::value_type>()){}

grafeex::messaging::changing_movement_event::~changing_movement_event(){}

grafeex::messaging::message_event &grafeex::messaging::changing_movement_event::dispatch(){
	if (movement_event::dispatch().is_propagating())
		*this << object_->target()->on_movement_changing(*this);
	return *this;
}

bool grafeex::messaging::changing_movement_event::is_changing() const{
	return true;
}

grafeex::messaging::changing_movement_event::info_type &grafeex::messaging::changing_movement_event::dimensions(){
	return info_;
}

grafeex::messaging::changed_movement_event::changed_movement_event(object &value)
	: movement_event(value){}

grafeex::messaging::changed_movement_event::~changed_movement_event(){}

grafeex::messaging::message_event &grafeex::messaging::changed_movement_event::dispatch(){
	if (movement_event::dispatch().is_propagating())
		object_->target()->on_movement_changed(*this);
	return *this;
}

bool grafeex::messaging::changed_movement_event::is_changing() const{
	return false;
}

grafeex::messaging::size_event::size_event(object &value)
	: message_event(value){}

grafeex::messaging::size_event::~size_event(){}

grafeex::messaging::message_event &grafeex::messaging::size_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_size_change(*this);
	return *this;
}

grafeex::messaging::changing_size_event::changing_size_event(object &value)
	: size_event(value), info_(value.info().lparam<info_type::value_type>()){}

grafeex::messaging::changing_size_event::~changing_size_event(){}

grafeex::messaging::message_event &grafeex::messaging::changing_size_event::dispatch(){
	if (size_event::dispatch().is_propagating())
		*this << object_->target()->on_size_changing(*this);
	return *this;
}

bool grafeex::messaging::changing_size_event::is_changing() const{
	return true;
}

grafeex::messaging::changing_size_event::info_type &grafeex::messaging::changing_size_event::drag_rect(){
	return info_;
}

grafeex::messaging::changing_size_event::edge_type grafeex::messaging::changing_size_event::edge() const{
	return static_cast<edge_type>(object_->info().wparam<int>());
}

grafeex::messaging::changed_size_event::changed_size_event(object &value)
	: size_event(value){}

grafeex::messaging::changed_size_event::~changed_size_event(){}

grafeex::messaging::message_event &grafeex::messaging::changed_size_event::dispatch(){
	if (size_event::dispatch().is_propagating())
		object_->target()->on_size_changed(*this);

	if (is_propagating()){
		if (maximized())
			object_->target()->on_maximized(*this);
		else if (minimized())
			object_->target()->on_minimized(*this);
	}

	return *this;
}

bool grafeex::messaging::changed_size_event::is_changing() const{
	return false;
}

bool grafeex::messaging::changed_size_event::minimized() const{
	return (object_->info().wparam() == SIZE_MINIMIZED);
}

bool grafeex::messaging::changed_size_event::maximized() const{
	return (object_->info().wparam() == SIZE_MAXIMIZED);
}

bool grafeex::messaging::changed_size_event::other_window_restored() const{
	return (object_->info().wparam() == SIZE_MAXSHOW);
}

bool grafeex::messaging::changed_size_event::other_window_maximized() const{
	return (object_->info().wparam() == SIZE_MAXHIDE);
}

grafeex::messaging::min_max_event::min_max_event(object &value)
	: message_event(value){}

grafeex::messaging::min_max_event::~min_max_event(){}

grafeex::messaging::message_event &grafeex::messaging::min_max_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_get_min_max_info(*this);
	return *this;
}

grafeex::messaging::min_max_event::info_type &grafeex::messaging::min_max_event::info() const{
	return *object_->info().lparam<info_type *>();
}

grafeex::messaging::calculate_size_event::calculate_size_event(object &value)
	: message_event(value), non_valid_info_(value.info().lparam<non_valid_info_type::value_type>()){}

grafeex::messaging::calculate_size_event::~calculate_size_event(){}

grafeex::messaging::message_event &grafeex::messaging::calculate_size_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_calculate_size(*this);
	return *this;
}

bool grafeex::messaging::calculate_size_event::indicate_valid_part() const{
	return (object_->info().wparam<bool_type>() != FALSE);
}

grafeex::messaging::calculate_size_event::valid_info_type &grafeex::messaging::calculate_size_event::valid_info() const{
	return *object_->info().lparam<valid_info_type *>();
}

grafeex::messaging::calculate_size_event::non_valid_info_type &grafeex::messaging::calculate_size_event::non_valid_info(){
	return non_valid_info_;
}

grafeex::messaging::size_move_event::size_move_event(object &value)
	: message_event(value){}

grafeex::messaging::size_move_event::~size_move_event(){}

grafeex::messaging::message_event &grafeex::messaging::size_move_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_size_move(*this);
	return *this;
}

grafeex::messaging::enter_size_move_event::enter_size_move_event(object &value)
	: size_move_event(value){}

grafeex::messaging::enter_size_move_event::~enter_size_move_event(){}

grafeex::messaging::message_event &grafeex::messaging::enter_size_move_event::dispatch(){
	if (size_move_event::dispatch().is_propagating())
		object_->target()->on_enter_size_move(*this);
	return *this;
}

bool grafeex::messaging::enter_size_move_event::is_entered() const{
	return true;
}

grafeex::messaging::exit_size_move_event::exit_size_move_event(object &value)
	: size_move_event(value){}

grafeex::messaging::exit_size_move_event::~exit_size_move_event(){}

grafeex::messaging::message_event &grafeex::messaging::exit_size_move_event::dispatch(){
	if (size_move_event::dispatch().is_propagating())
		object_->target()->on_exit_size_move(*this);
	return *this;
}

bool grafeex::messaging::exit_size_move_event::is_entered() const{
	return false;
}

grafeex::messaging::query_open_event::query_open_event(object &value)
	: message_event(value){}

grafeex::messaging::query_open_event::~query_open_event(){}

grafeex::messaging::message_event &grafeex::messaging::query_open_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_query_open(*this);
	return *this;
}

grafeex::messaging::query_drag_icon_event::query_drag_icon_event(object &value)
	: message_event(value){}

grafeex::messaging::query_drag_icon_event::~query_drag_icon_event(){}

grafeex::messaging::message_event &grafeex::messaging::query_drag_icon_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_query_drag_icon(*this);
	return *this;
}
