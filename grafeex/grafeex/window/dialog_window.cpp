#include "dialog_window.h"
#include "../structures/system_color_structure.h"

grafeex::window::dialog::dialog()
	: base_type(nullptr, nullptr, ::DefDlgProcW), owner_(nullptr){}

grafeex::window::dialog::~dialog(){
	destroy();
}

bool grafeex::window::dialog::is_dialog() const{
	return true;
}

bool grafeex::window::dialog::is_modal() const{
	return (owner_ != nullptr);
}

bool grafeex::window::dialog::do_modal(object &owner, bool center, bool update_styles){
	if (parent_ != nullptr || is_modal())
		return false;

	(owner_ = &owner)->view().disable();
	if (update_styles)
		style().apply_modal();

	if (center){//Center inside owner
		auto owner_size = owner.size();
		auto size = this->size();
		move(owner.offset() + point_type{ (owner_size.width() - size.width()) / 2, (owner_size.height() - size.height()) / 2 });
	}

	view().show();
	return true;
}

bool grafeex::window::dialog::cancel_modal(){
	if (!is_modal())
		return false;

	owner_->view().enable();
	owner_ = nullptr;

	return true;
}

grafeex::window::object *grafeex::window::dialog::get_owner() const{
	return owner_;
}
