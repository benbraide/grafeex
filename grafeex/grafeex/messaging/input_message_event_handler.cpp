#include "input_message_event_handler.h"

grafeex::messaging::input_event_handler::input_event_handler()
	: mouse_state_(*this){}

grafeex::messaging::input_event_handler::~input_event_handler() = default;

grafeex::messaging::input_event_handler::mouse_state_type &grafeex::messaging::input_event_handler::mouse_state(){
	return mouse_state_;
}

void grafeex::messaging::input_event_handler::on_input(input_event &e){}

void grafeex::messaging::input_event_handler::on_key(key_event &e){}

void grafeex::messaging::input_event_handler::on_key_down(key_down_event &e){}

void grafeex::messaging::input_event_handler::on_key_up(key_up_event &e){}

void grafeex::messaging::input_event_handler::on_char(char_event &e){}

void grafeex::messaging::input_event_handler::on_dead_char(dead_char_event &e){}

void grafeex::messaging::input_event_handler::on_normal_key_down(normal_key_down_event &e){}

void grafeex::messaging::input_event_handler::on_normal_key_up(normal_key_up_event &e){}

void grafeex::messaging::input_event_handler::on_normal_char(normal_char_event &e){}

void grafeex::messaging::input_event_handler::on_normal_dead_char(normal_dead_char_event &e){}

void grafeex::messaging::input_event_handler::on_system_key_down(system_key_down_event &e){}

void grafeex::messaging::input_event_handler::on_system_key_up(system_key_up_event &e){}

void grafeex::messaging::input_event_handler::on_system_char(system_char_event &e){}

void grafeex::messaging::input_event_handler::on_system_dead_char(system_dead_char_event &e){}

void grafeex::messaging::input_event_handler::on_mouse(mouse_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_leave(){}

void grafeex::messaging::input_event_handler::on_mouse_client_leave(){}

void grafeex::messaging::input_event_handler::on_mouse_enter(mouse_move_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_enter(mouse_nc_move_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_enter(mouse_client_move_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_move(mouse_move_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_move(mouse_nc_move_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_move(mouse_client_move_event &e){}

grafeex::messaging::input_event_handler::dword_type grafeex::messaging::input_event_handler::on_mouse_hover_request(const point_type &mouse_position){
	return 0;
}

void grafeex::messaging::input_event_handler::on_mouse_hover(const point_type &mouse_position){}

void grafeex::messaging::input_event_handler::on_mouse_button_down(mouse_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_left_button_down(mouse_left_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_left_button_down(mouse_nc_left_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_left_button_down(mouse_client_left_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_middle_button_down(mouse_middle_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_middle_button_down(mouse_nc_middle_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_middle_button_down(mouse_client_middle_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_right_button_down(mouse_right_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_right_button_down(mouse_nc_right_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_right_button_down(mouse_client_right_button_down_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_button_up(mouse_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_left_button_up(mouse_left_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_left_button_up(mouse_nc_left_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_left_button_up(mouse_client_left_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_middle_button_up(mouse_middle_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_middle_button_up(mouse_nc_middle_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_middle_button_up(mouse_client_middle_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_right_button_up(mouse_right_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_right_button_up(mouse_nc_right_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_right_button_up(mouse_client_right_button_up_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_button_dbl_click(mouse_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_left_button_dbl_click(mouse_left_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_left_button_dbl_click(mouse_nc_left_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_left_button_dbl_click(mouse_client_left_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_middle_button_dbl_click(mouse_middle_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_middle_button_dbl_click(mouse_nc_middle_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_middle_button_dbl_click(mouse_client_middle_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_right_button_dbl_click(mouse_right_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_nc_right_button_dbl_click(mouse_nc_right_button_dbl_click_event &e){}

void grafeex::messaging::input_event_handler::on_mouse_client_right_button_dbl_click(mouse_client_right_button_dbl_click_event &e){}

bool grafeex::messaging::input_event_handler::on_mouse_begin_drag(const drag_info &info){
	return false;
}

void grafeex::messaging::input_event_handler::on_mouse_end_drag(const drag_info &info){}

void grafeex::messaging::input_event_handler::on_mouse_drag_out(const drag_info &info){}

void grafeex::messaging::input_event_handler::on_mouse_drag(const drag_info &info){}

void grafeex::messaging::input_event_handler::on_mouse_left_drag(const drag_info &info){}

void grafeex::messaging::input_event_handler::on_mouse_middle_drag(const drag_info &info){}

void grafeex::messaging::input_event_handler::on_mouse_right_drag(const drag_info &info){}

bool grafeex::messaging::input_event_handler::on_mouse_wheel(mouse_wheel_event &e){
	return false;
}

bool grafeex::messaging::input_event_handler::on_mouse_vertical_wheel(mouse_vertical_wheel_event &e){
	return false;
}

bool grafeex::messaging::input_event_handler::on_mouse_horizontal_wheel(mouse_horizontal_wheel_event &e){
	return false;
}
