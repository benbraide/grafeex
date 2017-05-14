#include "modal_dialog_window.h"

grafeex::window::modal_dialog::modal_dialog(){
	reset_persistent_styles_();
}

grafeex::window::modal_dialog::modal_dialog(object_type &owner, const std::wstring &caption, const size_type &size, callback_type callback){
	reset_persistent_styles_();
	run(owner, caption, size, callback);
}

grafeex::window::modal_dialog::~modal_dialog(){
	destroy();
}

bool grafeex::window::modal_dialog::is_modal() const{
	return true;
}

int grafeex::window::modal_dialog::run(object_type &owner, const std::wstring &caption, const size_type &size, callback_type callback){
	if (!create_(owner, caption, size))
		return -1;

	if (callback != nullptr)
		callback(*this);

	return run_();
}

void grafeex::window::modal_dialog::reset_persistent_styles_(){
	persistent_styles_.basic = (WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION);
	persistent_styles_.extended = (WS_EX_DLGMODALFRAME | WS_EX_STATICEDGE);
}

int grafeex::window::modal_dialog::run_(){
	auto value = dialog::run_();
	destroy();
	return value;
}
