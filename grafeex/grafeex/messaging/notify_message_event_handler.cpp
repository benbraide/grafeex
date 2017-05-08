#include "notify_message_event_handler.h"
#include "message_event_forwarder.h"

grafeex::messaging::notify_event_handler::~notify_event_handler() = default;

grafeex::messaging::button_notify_event_handler::~button_notify_event_handler() = default;

grafeex::messaging::notify_event_handler::dword_type grafeex::messaging::button_notify_event_handler::on_draw_notify(custom_draw_event &e){
	return static_cast<dword_type>(e.handle().get_object().value());
}

void grafeex::messaging::button_notify_event_handler::on_dropdown_notify(notify_event &e){}

void grafeex::messaging::button_notify_event_handler::on_highlight_change_notify(notify_event &e){
	switch (e.get_object().info().lparam<info_type *>()->dwFlags){
	case HICF_ENTERING:
		on_enter_notify(e);
		break;
	default:
		on_leave_notify(e);
		break;
	}
}

void grafeex::messaging::button_notify_event_handler::on_enter_notify(notify_event &e){}

void grafeex::messaging::button_notify_event_handler::on_leave_notify(notify_event &e){}

grafeex::messaging::tool_tip_notify_event_handler::~tool_tip_notify_event_handler() = default;

grafeex::messaging::notify_event_handler::dword_type grafeex::messaging::tool_tip_notify_event_handler::on_draw_notify(custom_draw_event &e){
	return static_cast<dword_type>(e.handle().get_object().value());
}

bool grafeex::messaging::tool_tip_notify_event_handler::on_show_notify(notify_event &e){
	return false;
}

void grafeex::messaging::tool_tip_notify_event_handler::on_hide_notify(notify_event &e){}

void grafeex::messaging::tool_tip_notify_event_handler::on_link_click_notify(notify_event &e){}

grafeex::messaging::tab_notify_event_handler::~tab_notify_event_handler() = default;

void grafeex::messaging::tab_notify_event_handler::on_click_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_dbl_click_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_right_click_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_right_dbl_click_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_capture_release_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_focus_change_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_key_down_notify(notify_event &e){}

void grafeex::messaging::tab_notify_event_handler::on_selection_change_notify(notify_event &e){}

bool grafeex::messaging::tab_notify_event_handler::on_selection_changing_notify(notify_event &e){
	return false;
}

grafeex::messaging::tool_bar_notify_event_handler::~tool_bar_notify_event_handler() = default;

grafeex::messaging::notify_event_handler::dword_type grafeex::messaging::tool_bar_notify_event_handler::on_draw_notify(custom_draw_event &e){
	return static_cast<dword_type>(e.handle().get_object().value());
}

void grafeex::messaging::tool_bar_notify_event_handler::on_click_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_dbl_click_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_right_click_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_right_dbl_click_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_capture_release_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_key_down_notify(notify_event &e){}

bool grafeex::messaging::tool_bar_notify_event_handler::on_initialize_customize_notify(notify_event &e){
	return true;
}

grafeex::messaging::notify_event_handler::dword_type grafeex::messaging::tool_bar_notify_event_handler::on_reset_notify(notify_event &e){
	return 0;
}

void grafeex::messaging::tool_bar_notify_event_handler::on_begin_adjust_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_end_adjust_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_begin_drag_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_end_drag_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_drag_out_notify(notify_event &e){}

bool grafeex::messaging::tool_bar_notify_event_handler::on_drag_over_notify(notify_event &e){
	return true;
}

void grafeex::messaging::tool_bar_notify_event_handler::on_deleting_button_notify(notify_event &e){}

bool grafeex::messaging::tool_bar_notify_event_handler::on_query_delete_notify(notify_event &e){
	return true;
}

bool grafeex::messaging::tool_bar_notify_event_handler::on_query_insert_notify(notify_event &e){
	return true;
}

grafeex::messaging::tool_bar_notify_event_handler::drop_down_type grafeex::messaging::tool_bar_notify_event_handler::on_drop_down_notify(notify_event &e){
	return drop_down_type::no_default;
}

bool grafeex::messaging::tool_bar_notify_event_handler::on_hot_item_change_notify(notify_event &e){
	return false;
}

bool grafeex::messaging::tool_bar_notify_event_handler::on_get_button_info_notify(notify_event &e){
	return false;
}

void grafeex::messaging::tool_bar_notify_event_handler::on_change_notify(notify_event &e){}

void grafeex::messaging::tool_bar_notify_event_handler::on_customize_help_notify(notify_event &e){}
