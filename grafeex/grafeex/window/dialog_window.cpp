#include "dialog_window.h"
#include "../structures/system_color_structure.h"

grafeex::window::dialog::dialog()
	: base_type(::DefDlgProcW), result_(0){}

grafeex::window::dialog::~dialog(){
	destroy();
}

bool grafeex::window::dialog::is_dialog() const{
	return true;
}

bool grafeex::window::dialog::is_modal() const{
	return (loop_ != nullptr);
}

int grafeex::window::dialog::run(object_type &owner, const std::wstring &caption, const size_type &size){
	if (!create_(owner, caption, size))
		return -1;

	return run_();
}

int grafeex::window::dialog::run(bool update_styles){
	if (parent_ == nullptr || !is_created() || is_modal())
		return -1;

	if (update_styles)
		style().apply_modal();

	return run_();
}

bool grafeex::window::dialog::end(int code){
	if (is_created()){
		loop_ = nullptr;
		result_ = code;
	}

	return true;
}

bool grafeex::window::dialog::create_(object_type &owner, const std::wstring &caption, const size_type &size){
	if (is_created())
		return false;

	insert_into_parent_(owner);
	return base_type::create_(caption, point_type{}, size);
}

int grafeex::window::dialog::run_(){
	auto owner_size = parent_->size();
	auto size = this->size();

	move(point_type{ (owner_size.width() - size.width()) / 2, (owner_size.height() - size.height()) / 2 });
	view().show();

	loop_ = std::make_shared<threading::modal_loop>();
	loop_->run(*this);

	return result_;
}
