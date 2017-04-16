#include "menu_check_item.h"

grafeex::menu::check_item::event_tunnel::event_tunnel(){
	event_list_[checked_event_.group()] = &checked_event_;
	event_list_[unchecked_event_.group()] = &unchecked_event_;
}

grafeex::menu::check_item::event_tunnel::~event_tunnel() = default;

grafeex::menu::check_item::check_item(option options)
	: item(options){}

grafeex::menu::check_item::check_item(gui_object_type &parent, const std::wstring &value, option options){
	options_ = options;
	create(parent, value);
}

grafeex::menu::check_item::check_item(const sibling_type &sibling, const std::wstring &value, option options){
	options_ = options;
	create(sibling, value);
}

grafeex::menu::check_item::~check_item() = default;

grafeex::menu::check_item::event_tunnel &grafeex::menu::check_item::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
}

grafeex::menu::check_item &grafeex::menu::check_item::toggle(){
	check(!is_checked());
	return *this;
}

grafeex::gui::generic_object::events_type grafeex::menu::check_item::get_events_(){
	return create_events_<event_tunnel>();
}

void grafeex::menu::check_item::on_checked(messaging::menu_command_event &e){}

void grafeex::menu::check_item::on_unchecked(messaging::menu_command_event &e){}
