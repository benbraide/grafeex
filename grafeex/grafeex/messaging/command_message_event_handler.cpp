#include "command_message_event_handler.h"
#include "message_event_forwarder.h"

grafeex::messaging::command_event_handler::~command_event_handler() = default;

grafeex::messaging::static_command_event_handler::~static_command_event_handler() = default;

void grafeex::messaging::static_command_event_handler::on_disable_command(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_enable_command(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_click_command(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_dbl_click_command(command_event &e){}

grafeex::messaging::button_command_event_handler::~button_command_event_handler() = default;

void grafeex::messaging::button_command_event_handler::on_kill_focus_command(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_set_focus_command(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_click_command(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_dbl_click_command(command_event &e){}
