#include "gui_object_collection.h"
#include "tab_collection.h"
#include "tool_tip_collection.h"

#include "../window/frame_window.h"
#include "../controls/default_button_control.h"
#include "../controls/default_split_button_control.h"
#include "../controls/check_control.h"
#include "../controls/radio_control_group.h"
#include "../controls/radio_control.h"
#include "../controls/label_control.h"

grafeex::collections::gui_object::gui_object(gui_object_type &owner)
	: owner_(&owner){}

grafeex::collections::gui_object::~gui_object() = default;

grafeex::collections::gui_object &grafeex::collections::gui_object::frame_window(GCGUIO_WIN_ARGS_IMPL1(frame_type)){
	return window<frame_type>(GCGUIO_FWD_WIN_ARGS2);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::frame_dialog(GCGUIO_WIN_ARGS_IMPL1(dialog_frame_type)){
	return window<dialog_frame_type>(GCGUIO_FWD_WIN_ARGS2);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::button_control(GCGUIO_BTN_ARGS_IMPL(button)){
	return GCGUIO_CREATE_CTRL(button);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::default_button_control(GCGUIO_BTN_ARGS_IMPL(default_button)){
	return GCGUIO_CREATE_CTRL(default_button);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::split_button_control(GCGUIO_BTN_ARGS_IMPL(split_button)){
	return GCGUIO_CREATE_CTRL(split_button);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::default_split_button_control(GCGUIO_BTN_ARGS_IMPL(default_split_button)){
	return GCGUIO_CREATE_CTRL(default_split_button);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::check_control(GCGUIO_BTN_ARGS_IMPL(check)){
	return GCGUIO_CREATE_CTRL(check);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::radio_control_group(GCGUIO_CTRL_CALLBACK_ARG(radio_group)){
	return insert_(std::make_shared<grafeex::window::controls::radio_group>(*owner_), callback);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::radio_control(GCGUIO_BTN_ARGS_IMPL(radio)){
	return GCGUIO_CREATE_CTRL(radio);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::label_control(GCGUIO_LBL_ARGS_IMPL(label)){
	return insert_(std::make_shared<grafeex::window::controls::label>(GCGUIO_FWD_LBL_ARGS), callback);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::tool_tip_control(GCGUIO_CALLBACK_ARG(tool_tip)){
	return insert_(std::make_shared<tool_tip>(*owner_), callback);
}

grafeex::collections::gui_object &grafeex::collections::gui_object::tab_control(GCGUIO_CALLBACK_ARG(tab_type)){
	return insert_(std::make_shared<tab_type>(*owner_), callback);
}

grafeex::collections::gui_object::gui_object_type *grafeex::collections::gui_object::get_item(std_size_type index) const{
	return (index < list_.size()) ? std::next(list_.begin(), index)->get() : nullptr;
}

grafeex::collections::gui_object::gui_object_type *grafeex::collections::gui_object::get_first_item() const{
	return (list_.empty() ? nullptr : list_.begin()->get());
}

grafeex::collections::gui_object::gui_object_type *grafeex::collections::gui_object::get_last_item() const{
	return (list_.empty() ? nullptr : list_.rbegin()->get());
}

grafeex::collections::gui_object::std_size_type grafeex::collections::gui_object::count() const{
	return list_.size();
}

bool grafeex::collections::gui_object::empty() const{
	return list_.empty();
}

void grafeex::collections::gui_object::remove_(typename base_type::child_type &child){
	base_type::remove_(child);
	for (auto iter = list_.begin(); iter != list_.end(); ++iter){
		if (iter->get() == &child){
			list_.erase(iter);
			break;
		}
	}
}
