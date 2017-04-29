#include "general_message_event_handler.h"
#include "../window/dialog_window.h"
#include "../controls/control_object.h"

grafeex::messaging::general_event_handler::~general_event_handler() = default;

void grafeex::messaging::general_event_handler::on_event(message_event &e){}

void grafeex::messaging::general_event_handler::on_null(null_event &e){}

void grafeex::messaging::general_event_handler::on_unhandled(unhandled_event &e){}

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

grafeex::messaging::general_event_handler::ma_return_type grafeex::messaging::general_event_handler::on_mouse_activate(mouse_activate_event &e){
	return ma_return_type::activate;
}

void grafeex::messaging::general_event_handler::on_child_activate(child_activate_event &e){}

void grafeex::messaging::general_event_handler::on_cancel_mode(cancel_mode_event &e){}

void grafeex::messaging::general_event_handler::on_enable_change(enable_event &e){}

void grafeex::messaging::general_event_handler::on_enable(enable_event &e){}

void grafeex::messaging::general_event_handler::on_disable(enable_event &e){}

void grafeex::messaging::general_event_handler::on_focus_change(focus_change_event &e){}

void grafeex::messaging::general_event_handler::on_set_focus(set_focus_event &e){}

void grafeex::messaging::general_event_handler::on_kill_focus(kill_focus_event &e){}

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
	return reinterpret_cast<icon_type>(e.handle().get_object().value());
}

grafeex::messaging::general_event_handler::hit_target_type grafeex::messaging::general_event_handler::on_hit_test(hit_test_event &e){
	return static_cast<hit_target_type>(e.handle().get_object().value());
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
	if (dynamic_cast<window::controls::object *>(this) == nullptr){
		e.skip();//Prevent default
		auto &renderer = e.renderer(true);
		erase_background_(renderer, wrappers::hdc(e.device()).clip_rect(), e.background_brush());
		return true;
	}

	return false;
}

void grafeex::messaging::general_event_handler::on_paint(paint_event &e){}

void grafeex::messaging::general_event_handler::on_nc_paint(nc_paint_event &e){}

void grafeex::messaging::general_event_handler::on_paint_client(client_paint_event &e){
	if (dynamic_cast<window::controls::object *>(this) == nullptr && (e.has_begun() || e.begin()) && e.erase_background()){
		auto &renderer = e.renderer(true);
		erase_background_(renderer, wrappers::hdc(e.device()).clip_rect(), e.background_brush());
	}
}

void grafeex::messaging::general_event_handler::on_print_client(print_client_event &e){
	if (dynamic_cast<window::controls::object *>(this) == nullptr && e.erase_background()){
		auto &renderer = e.renderer(true);
		erase_background_(renderer, wrappers::hdc(e.device()).clip_rect(), e.background_brush());
	}
}

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

void grafeex::messaging::general_event_handler::on_capture_changed(capture_changed_event &e){}

void grafeex::messaging::general_event_handler::on_timer(timer_event &e){}

void grafeex::messaging::general_event_handler::on_command(command_event &e){}

void grafeex::messaging::general_event_handler::on_accelerator(command_event &e){}

void grafeex::messaging::general_event_handler::on_notify(notify_event &e){}

void grafeex::messaging::general_event_handler::on_set_font(set_font_event &e){}

grafeex::messaging::general_event_handler::font_type grafeex::messaging::general_event_handler::on_get_font(get_font_event &e){
	return reinterpret_cast<font_type>(e.handle().get_object().value());
}

void grafeex::messaging::general_event_handler::on_set_text(set_text_event &e){}

grafeex::messaging::general_event_handler::lresult_type grafeex::messaging::general_event_handler::on_get_text(get_text_event &e){
	return e.handle().get_object().value();
}

grafeex::messaging::general_event_handler::lresult_type grafeex::messaging::general_event_handler::on_get_text_length(get_text_length_event &e){
	return e.handle().get_object().value();
}

void grafeex::messaging::general_event_handler::on_drawing_error(hresult_type err, bool is_device){}

void grafeex::messaging::general_event_handler::on_recreate_drawing_resources(bool is_device){}

void grafeex::messaging::general_event_handler::erase_background_(render_type &renderer, const structures::rect &clip_rect, brush_type &brush){
	auto window_self = dynamic_cast<window::object *>(this);
	if (window_self == nullptr)
		return;//Non-window

	auto &view = window_self->view();
	if (!view.has_background_color()){//Use default color
		if (dynamic_cast<window::dialog *>(this) == nullptr)
			view.background_color(structures::system_color::get(structures::system_color::index_type::window));
		else//Dialog window
			view.background_color(structures::system_color::get(structures::system_color::index_type::button_face));
	}

	renderer.Clear(view.background_color());
}
