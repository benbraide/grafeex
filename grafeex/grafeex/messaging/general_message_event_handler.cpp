#include "general_message_event_handler.h"
#include "../application/application_object.h"

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

void grafeex::messaging::general_event_handler::on_active_change(activate_event &e){}

void grafeex::messaging::general_event_handler::on_activate(activate_event &e){}

void grafeex::messaging::general_event_handler::on_deactivate(activate_event &e){}

void grafeex::messaging::general_event_handler::on_enable_change(enable_event &e){}

void grafeex::messaging::general_event_handler::on_enable(enable_event &e){}

void grafeex::messaging::general_event_handler::on_disable(enable_event &e){}

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
	e.handle();
	return true;
}

void grafeex::messaging::general_event_handler::on_paint(paint_event &e){}

void grafeex::messaging::general_event_handler::on_nc_paint(nc_paint_event &e){}

void grafeex::messaging::general_event_handler::on_paint_client(client_paint_event &e){}
