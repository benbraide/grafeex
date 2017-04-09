#include "general_message_event_handler.h"
#include "../window/window_object.h"

grafeex::messaging::general_event_handler::~general_event_handler(){}

void grafeex::messaging::general_event_handler::on_unhandled_event(message_event &e){}

void grafeex::messaging::general_event_handler::on_event(message_event &e){}

bool grafeex::messaging::general_event_handler::on_scope(scope_event &e){
	return true;
}

bool grafeex::messaging::general_event_handler::on_create(create_event &e){
	return true;
}

bool grafeex::messaging::general_event_handler::on_nc_create(nc_create_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_destroy(destroy_event &e){}

void grafeex::messaging::general_event_handler::on_nc_destroy(nc_destroy_event &e){}

bool grafeex::messaging::general_event_handler::on_close(close_event &e){
	return true;
}

bool grafeex::messaging::general_event_handler::on_nc_active_change(nc_activate_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_nc_activate(nc_activate_event &e){}

bool grafeex::messaging::general_event_handler::on_nc_deactivate(nc_activate_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_active_change(activate_event &e){}

void grafeex::messaging::general_event_handler::on_activate(activate_event &e){}

void grafeex::messaging::general_event_handler::on_deactivate(activate_event &e){}

void grafeex::messaging::general_event_handler::on_child_activate(child_activate_event &e){}

void grafeex::messaging::general_event_handler::on_cancel_mode(cancel_mode_event &e){}

void grafeex::messaging::general_event_handler::on_enable_change(enable_event &e){}

void grafeex::messaging::general_event_handler::on_enable(enable_event &e){}

void grafeex::messaging::general_event_handler::on_disable(enable_event &e){}

bool grafeex::messaging::general_event_handler::on_position_change(position_event &e){
	return false;
}

bool grafeex::messaging::general_event_handler::on_position_changing(changing_position_event &e){
	return false;
}

void grafeex::messaging::general_event_handler::on_position_changed(changed_position_event &e){}

bool grafeex::messaging::general_event_handler::on_movement_change(movement_event &e){
	return false;
}

bool grafeex::messaging::general_event_handler::on_movement_changing(changing_movement_event &e){
	return false;
}

void grafeex::messaging::general_event_handler::on_movement_changed(changed_movement_event &e){}

bool grafeex::messaging::general_event_handler::on_size_change(size_event &e){
	return false;
}

bool grafeex::messaging::general_event_handler::on_size_changing(changing_size_event &e){
	return false;
}

void grafeex::messaging::general_event_handler::on_size_changed(changed_size_event &e){}

void grafeex::messaging::general_event_handler::on_minimized(changed_size_event &e){}

void grafeex::messaging::general_event_handler::on_maximized(changed_size_event &e){}

void grafeex::messaging::general_event_handler::on_get_min_max_info(min_max_event &e){}

grafeex::messaging::general_event_handler::dword_type grafeex::messaging::general_event_handler::on_calculate_size(calculate_size_event &e){
	return 0;
}

void grafeex::messaging::general_event_handler::on_size_move(size_move_event &e){}

void grafeex::messaging::general_event_handler::on_enter_size_move(enter_size_move_event &e){}

void grafeex::messaging::general_event_handler::on_exit_size_move(exit_size_move_event &e){}

bool grafeex::messaging::general_event_handler::on_query_open(query_open_event &e){
	return true;
}

grafeex::messaging::general_event_handler::icon_type grafeex::messaging::general_event_handler::on_query_drag_icon(query_drag_icon_event &e){
	return nullptr;
}

bool grafeex::messaging::general_event_handler::on_style_change(style_event &e){
	return true;
}

bool grafeex::messaging::general_event_handler::on_style_changing(changing_style_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_style_changed(changed_style_event &e){}

bool grafeex::messaging::general_event_handler::on_basic_style_changing(changing_style_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_basic_style_changed(changed_style_event &e){}

bool grafeex::messaging::general_event_handler::on_extended_style_changing(changing_style_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_extended_style_changed(changed_style_event &e){}

void grafeex::messaging::general_event_handler::on_visibility_change(visibility_event &e){}

void grafeex::messaging::general_event_handler::on_show(visibility_event &e){}

void grafeex::messaging::general_event_handler::on_hide(visibility_event &e){}

bool grafeex::messaging::general_event_handler::on_erase_background(erase_background_event &e){
	e.skip();
	auto &view = this->view();
	if (view.has_background_color()){
		auto &renderer = this->renderer();
		renderer->BeginDraw();
		renderer->Clear(view.background_color());
		renderer->EndDraw();
	}

	return true;
}

void grafeex::messaging::general_event_handler::on_paint(paint_event &e){}

void grafeex::messaging::general_event_handler::on_nc_paint(nc_paint_event &e){}

void grafeex::messaging::general_event_handler::on_paint_client(client_paint_event &e){}

void grafeex::messaging::general_event_handler::on_print_client(print_client_event &e){}

void grafeex::messaging::general_event_handler::on_print(print_event &e){}

void grafeex::messaging::general_event_handler::on_theme_changed(theme_changed_event &e){}

void grafeex::messaging::general_event_handler::on_user_changed(user_changed_event &e){}

bool grafeex::messaging::general_event_handler::on_input_language_changed(input_language_changed_event &e){
	return false;
}

bool grafeex::messaging::general_event_handler::on_input_language_change_request(input_language_change_request_event &e){
	return true;
}

void grafeex::messaging::general_event_handler::on_display_changed(display_changed_event &e){}
