#include "tab_control.h"

grafeex::window::controls::tab::event_tunnel::event_tunnel(){
	event_list_[activate_event_.group()] = &activate_event_;
	event_list_[deactivate_event_.group()] = &deactivate_event_;
}

grafeex::window::controls::tab::event_tunnel::~event_tunnel() = default;

grafeex::window::controls::tab::tab()
	: object(control_type::tab){
	reset_persistent_styles_();
}

grafeex::window::controls::tab::tab(gui_object_type &parent)
	: object(control_type::tab){
	reset_persistent_styles_();
	create(parent);
}

grafeex::window::controls::tab::tab(const sibling_type &sibling)
	: object(control_type::tab){
	reset_persistent_styles_();
	create(sibling);
}

grafeex::window::controls::tab::~tab(){
	destroy();
}

grafeex::window::object::rect_type grafeex::window::controls::tab::dimensions(bool inner) const{
	if (!inner)
		return object::dimensions(false);

	auto value = object::dimensions(true);
	TabCtrl_AdjustRect(value_, FALSE, value);

	return value;
}

grafeex::window::controls::object::dword_type grafeex::window::controls::tab::white_listed_styles(bool is_extended) const{
	return (base_type::white_listed_styles(is_extended) | (is_extended ? 0ul : general_styles));
}

grafeex::window::controls::tab::style_type &grafeex::window::controls::tab::style(){
	return *dynamic_cast<style_type *>(get_style_().get());
}

grafeex::window::controls::tab::event_tunnel &grafeex::window::controls::tab::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
}

bool grafeex::window::controls::tab::create(gui_object_type &parent){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return object::create_(L"", point_type{}, size_type{});
}

bool grafeex::window::controls::tab::create(const sibling_type &sibling){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return object::create_(L"", point_type{}, size_type{});
}

grafeex::gui::object::gui_object_type *grafeex::window::controls::tab::current_item() const{
	auto current_index = TabCtrl_GetCurSel(value_.operator HWND());
	if (current_index == -1)
		return nullptr;

	item_info_type info{ TCIF_PARAM };
	if (TabCtrl_GetItem(value_.operator HWND(), current_index, &info) == FALSE)
		return false;

	return reinterpret_cast<gui_object_type *>(info.lParam);
}

void grafeex::window::controls::tab::on_selection_change_notify(messaging::notify_event &e){
	auto current = current_item();
	if (current != nullptr)
		dynamic_cast<tab_item_event_handler *>(current)->on_activate();

	grafeex::events::object ev(*this);
	events().activate_event_.fire(ev);

	dynamic_cast<window::object *>(current)->view().show();
}

bool grafeex::window::controls::tab::on_selection_changing_notify(messaging::notify_event &e){
	auto current = current_item();
	if (current == nullptr || !dynamic_cast<tab_item_event_handler *>(current)->on_deactivate()){
		grafeex::events::object ev(*this);
		if (!events().deactivate_event_.fire(ev, false)){
			dynamic_cast<window::object *>(current)->view().hide();
			return false;
		}
	}

	return true;//Disallow change
}

void grafeex::window::controls::tab::reset_persistent_styles_(){
	object::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, TCS_HOTTRACK);
}

void grafeex::window::controls::tab::created_(){
	object::created_();
	attributes().fill_parent(true);
	attributes().align(true, alignment_type::top | alignment_type::left);
}

grafeex::window::object::style_ptr_type grafeex::window::controls::tab::get_style_(){
	return create_style_<style_type>();
}

grafeex::gui::generic_object::events_type grafeex::window::controls::tab::get_events_(){
	return create_events_<event_tunnel>();
}
