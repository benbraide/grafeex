#include "modal_dialog_window.h"

grafeex::window::modal_dialog::modal_dialog()
	: loop_(*this){
	reset_persistent_styles_();
}

grafeex::window::modal_dialog::modal_dialog(object_type &owner, const std::wstring &caption,
	const point_type &offset, const size_type &size)
	: loop_(*this){
	reset_persistent_styles_();
	run(owner, caption, offset, size);
}

grafeex::window::modal_dialog::modal_dialog(object_type &owner, const std::wstring &caption,
	const d2d_point_type &offset, const d2d_size_type &size)
	: loop_(*this){
	reset_persistent_styles_();
	run(owner, caption, offset, size);
}

grafeex::window::modal_dialog::~modal_dialog(){
	destroy();
}

int grafeex::window::modal_dialog::run(object_type &owner, const std::wstring &caption,
	const point_type &offset, const size_type &size){
	insert_into_parent_(owner);
	if (!create_(caption, offset, size))
		return -1;

	return run_();
}

int grafeex::window::modal_dialog::run(object_type &owner, const std::wstring &caption,
	const d2d_point_type &offset, const d2d_size_type &size){
	insert_into_parent_(owner);
	if (!create_(caption, offset, size))
		return -1;

	return run_();
}

bool grafeex::window::modal_dialog::end(int code){
	if (!loop_.running_)
		return false;

	loop_.stop();
	return_value_ = code;

	return true;
}

void grafeex::window::modal_dialog::reset_persistent_styles_(){
	persistent_styles_.basic = (WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION);
	persistent_styles_.extended = (WS_EX_DLGMODALFRAME | WS_EX_STATICEDGE);
}

int grafeex::window::modal_dialog::run_(){
	auto owner_size = parent_->size();
	auto this_size = this->size();
	point_type to{ (owner_size.width() - this_size.width()) / 2, (owner_size.height() - this_size.height()) / 2 };

	move(parent_->offset() + to);
	view().show();

	return_value_ = 0;
	loop_.run();

	return return_value_;
}
