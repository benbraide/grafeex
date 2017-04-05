#include "menu_message_event.h"
#include "../window/window_object.h"
#include "../collections/menu_collection.h"
#include "../menu/menu_check_item.h"

grafeex::messaging::context_menu_event::context_menu_event(object &value)
	: message_event(value){}

grafeex::messaging::context_menu_event::~context_menu_event(){}

grafeex::messaging::message_event &grafeex::messaging::context_menu_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_context_menu(*this);

	auto default_is_prevented = false;
	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		dynamic_cast<window::object::event_tunnel *>(get_event_())->context_menu_event_.fire(e);
		default_is_prevented = e.default_is_prevented();
	}

	if (!default_is_prevented){
		if (menu_ != nullptr){//Show menu
			dynamic_cast<menu::object *>(menu_.get())->track(*object_->target(), mouse_position());
			skip();
		}
	}
	else//Skip default
		skip();

	return *this;
}

grafeex::messaging::message_event::window_type *grafeex::messaging::context_menu_event::target() const{
	return hwnd_type(object_->info().wparam<native_hwnd_type>()).get_data<window_type *>();
}

grafeex::messaging::context_menu_event::menu_type &grafeex::messaging::context_menu_event::menu(){
	if (menu_ == nullptr){//Create menu
		auto menu = std::make_shared<collections::menu_popup>();
		menu->create();
		menu_ = menu;
	}

	return *menu_;
}

grafeex::messaging::context_menu_event::point_type grafeex::messaging::context_menu_event::mouse_position() const{
	return object_->info().mouse_position();
}

grafeex::messaging::menu_init_event::menu_init_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_init_event::~menu_init_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_init_event::dispatch(){
	auto target = menu();
	if (target != nullptr)//Call handler on menu
		target->on_menu_init(*this);

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_init(*this);

	return *this;
}

grafeex::messaging::menu_init_event::menu_type *grafeex::messaging::menu_init_event::menu() const{
	return menu_wrapper_type(object_->info().wparam<menu_handle_type>()).data<menu_type *>();
}

grafeex::messaging::menu_popup_init_event::menu_popup_init_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_popup_init_event::~menu_popup_init_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_popup_init_event::dispatch(){
	auto target = menu();
	if (target != nullptr)//Call handler on menu
		target->on_menu_popup_init(*this);

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_popup_init(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		if (target != nullptr)
			dynamic_cast<menu::object::event_tunnel *>(get_event_(target))->init_event_.fire(e);

		if (e.is_propagating())
			dynamic_cast<window::object::event_tunnel *>(get_event_())->menu_init_event_.fire(e);
	}

	return *this;
}

grafeex::messaging::menu_popup_init_event::menu_type *grafeex::messaging::menu_popup_init_event::menu() const{
	return menu_wrapper_type(object_->info().wparam<menu_handle_type>()).data<menu_type *>();
}

bool grafeex::messaging::menu_popup_init_event::is_window() const{
	return (object_->info().high_lparam<bool_type>() != FALSE);
}

grafeex::messaging::menu_popup_uninit_event::menu_popup_uninit_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_popup_uninit_event::~menu_popup_uninit_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_popup_uninit_event::dispatch(){
	auto target = menu();
	if (target != nullptr)//Call handler on menu
		target->on_menu_popup_uninit(*this);

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_popup_uninit(*this);

	return *this;
}

grafeex::messaging::menu_popup_uninit_event::menu_type *grafeex::messaging::menu_popup_uninit_event::menu() const{
	return menu_wrapper_type(object_->info().wparam<menu_handle_type>()).data<menu_type *>();
}

bool grafeex::messaging::menu_popup_uninit_event::is_window() const{
	return (object_->info().high_lparam() == MF_SYSMENU);
}

grafeex::messaging::menu_next_event::menu_next_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_next_event::~menu_next_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_next_event::dispatch(){
	auto target = menu();
	if (target != nullptr)//Call handler on menu
		target->on_menu_next(*this);

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_next(*this);

	return *this;
}

grafeex::messaging::menu_next_event::menu_type *grafeex::messaging::menu_next_event::menu() const{
	auto current = this->current();
	return (current == nullptr) ? nullptr : dynamic_cast<menu_type *>(current->parent());
}

grafeex::messaging::menu_next_event::menu_type *grafeex::messaging::menu_next_event::current() const{
	auto info = object_->info().lparam<info_type *>();
	return menu_wrapper_type(info->hmenuIn).data<menu_type *>();
}

grafeex::messaging::menu_next_event &grafeex::messaging::menu_next_event::next(menu_handle_type value){
	object_->info().lparam<info_type *>()->hmenuNext = value;
	return *this;
}

grafeex::messaging::menu_next_event::menu_type *grafeex::messaging::menu_next_event::next() const{
	auto info = object_->info().lparam<info_type *>();
	return menu_wrapper_type(info->hmenuNext).data<menu_type *>();
}

grafeex::messaging::menu_next_event &grafeex::messaging::menu_next_event::message_target(hwnd_native_type value){
	object_->info().lparam<info_type *>()->hwndNext = value;
	return *this;
}

grafeex::messaging::message_event::window_type *grafeex::messaging::menu_next_event::message_target() const{
	auto info = object_->info().lparam<info_type *>();
	return hwnd_type(info->hwndNext).get_data<window_type *>();
}

unsigned short grafeex::messaging::menu_next_event::key_code() const{
	return object_->info().wparam<unsigned short>();
}

bool grafeex::messaging::menu_next_event::is_left() const{
	return (key_code() == VK_LEFT);
}

grafeex::messaging::menu_rbutton_up_event::menu_rbutton_up_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_rbutton_up_event::~menu_rbutton_up_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_rbutton_up_event::dispatch(){
	typedef menu::object::track_option track_option_type;

	auto target_item = item();
	if (target_item != nullptr)//Call handler on item
		target_item->on_rbutton_up(*this);

	if (is_propagating()){
		auto target = menu();
		if (target != nullptr)//Call handler on menu
			target->on_menu_rbutton_up(*this);
	}

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_rbutton_up(*this);

	if (menu_ != nullptr){//Show menu
		dynamic_cast<menu::object *>(menu_.get())->track(*object_->target(), mouse_position(), track_option_type::recursive);
		skip();
	}

	return *this;
}

grafeex::messaging::menu_rbutton_up_event::menu_type *grafeex::messaging::menu_rbutton_up_event::menu() const{
	return menu_wrapper_type(object_->info().lparam<menu_handle_type>()).data<menu_type *>();
}

grafeex::messaging::menu_rbutton_up_event::menu_item_type *grafeex::messaging::menu_rbutton_up_event::item() const{
	auto menu = this->menu();
	if (menu == nullptr)
		return nullptr;

	return dynamic_cast<menu_item_type *>(menu->get_child_absolute(object_->info().wparam<menu_type::index_type>()));
}

grafeex::messaging::menu_rbutton_up_event::menu_collection_type &grafeex::messaging::menu_rbutton_up_event::context_menu(){
	if (menu_ == nullptr){//Create menu
		auto menu = std::make_shared<collections::menu_popup>();
		menu->create();
		menu_ = menu;
	}

	return *menu_;
}

grafeex::messaging::menu_rbutton_up_event::point_type grafeex::messaging::menu_rbutton_up_event::mouse_position() const{
	return object_->info().mouse_position();
}

grafeex::messaging::menu_command_event::menu_command_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_command_event::~menu_command_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_command_event::dispatch(){
	menu::check_item *check_item = nullptr;
	auto target_item = item();

	if (target_item != nullptr){//Call handler on item
		target_item->on_select(*this);
		check_item = dynamic_cast<menu::check_item *>(target_item);
	}

	auto target = menu();
	if (is_propagating() && target != nullptr)//Call handler on menu
		target->on_menu_select(*this);
	
	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_select(*this);

	auto default_is_prevented = false;
	events::object e(*object_->target(), *this);

	if (!event_is_disabled()){//Raise event
		if (target_item != nullptr)
			dynamic_cast<menu::item::event_tunnel *>(get_event_(target_item))->select_event_.fire(e);

		if (e.is_propagating() && target != nullptr)
			dynamic_cast<menu::object::event_tunnel *>(get_event_(target))->select_event_.fire(e);

		if (e.is_propagating())
			dynamic_cast<window::object::event_tunnel *>(get_event_())->menu_select_event_.fire(e);

		default_is_prevented = e.default_is_prevented();
	}

	if (!default_is_prevented && !object_->is_skipped() && target_item != nullptr){
		auto was_checked = target_item->is_checked();
		if (target_item->is_inside_group())
			target_item->check();
		else if (check_item != nullptr)
			check_item->toggle();

		auto is_checked = target_item->is_checked();
		if (check_item != nullptr && was_checked != is_checked){
			if (is_propagating()){
				if (is_checked)
					check_item->on_checked(*this);
				else//Unchecked
					check_item->on_unchecked(*this);
			}

			if (e.is_propagating()){
				if (check_item->is_checked())
					dynamic_cast<menu::check_item::event_tunnel *>(get_event_(target_item))->checked_event_.fire(e);
				else//Unchecked
					dynamic_cast<menu::check_item::event_tunnel *>(get_event_(target_item))->unchecked_event_.fire(e);
			}
		}
	}

	return *this;
}

grafeex::messaging::menu_command_event::menu_type *grafeex::messaging::menu_command_event::menu() const{
	return menu_wrapper_type(object_->info().lparam<menu_handle_type>()).data<menu_type *>();
}

grafeex::messaging::menu_command_event::menu_item_type *grafeex::messaging::menu_command_event::item() const{
	auto menu = this->menu();
	if (menu == nullptr)
		return nullptr;

	return dynamic_cast<menu_item_type *>(menu->get_child_absolute(object_->info().wparam<menu_type::index_type>()));
}

grafeex::messaging::menu_select_event::menu_select_event(object &value)
	: message_event(value){}

grafeex::messaging::menu_select_event::~menu_select_event(){}

grafeex::messaging::message_event &grafeex::messaging::menu_select_event::dispatch(){
	if (!GRAFEEX_IS(object_->info().high_wparam(), MF_MOUSESELECT)){
		message_event::dispatch();
		return *this;
	}

	auto target_item = item();
	if (target_item != nullptr)//Call handler on item
		target_item->on_highlight(*this);

	auto target = menu();
	if (is_propagating() && target != nullptr)//Call handler on menu
		target->on_menu_highlight(*this);

	if (is_propagating() && message_event::dispatch().is_propagating())
		object_->target()->on_menu_highlight(*this);

	if (!event_is_disabled()){//Raise event
		events::object e(*object_->target(), *this);
		if (target_item != nullptr)
			dynamic_cast<menu::item::event_tunnel *>(get_event_(target_item))->highlight_event_.fire(e);

		if (e.is_propagating() && target != nullptr)
			dynamic_cast<menu::object::event_tunnel *>(get_event_(target))->highlight_event_.fire(e);

		if (e.is_propagating())
			dynamic_cast<window::object::event_tunnel *>(get_event_())->menu_highlight_event_.fire(e);
	}

	return *this;
}

grafeex::messaging::menu_select_event::menu_type *grafeex::messaging::menu_select_event::menu() const{
	return menu_wrapper_type(object_->info().lparam<menu_handle_type>()).data<menu_type *>();
}

grafeex::messaging::menu_select_event::menu_item_type *grafeex::messaging::menu_select_event::item() const{
	auto menu = this->menu();
	if (menu == nullptr)
		return nullptr;

	if (GRAFEEX_IS(object_->info().high_wparam(), MF_POPUP))//Search by index
		return dynamic_cast<menu_item_type *>(menu->get_child_absolute(object_->info().low_wparam<menu_type::index_type>()));

	return dynamic_cast<menu_item_type *>(menu->find_child(object_->info().low_wparam<menu_type::id_type>()));
}

bool grafeex::messaging::menu_select_event::is_window() const{
	return GRAFEEX_IS(object_->info().high_wparam(), MF_SYSMENU);
}
