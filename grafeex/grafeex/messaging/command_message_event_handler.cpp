#include "command_message_event_handler.h"
#include "message_event_forwarder.h"

grafeex::messaging::command_event_handler::~command_event_handler(){}

grafeex::messaging::command_event_handler::forwarder_list_type grafeex::messaging::command_event_handler::forwarder_list_;

grafeex::messaging::static_command_event_handler::~static_command_event_handler(){}

void grafeex::messaging::static_command_event_handler::create_forwarder_list(){
	GMEH_UNIFORM_SCMD_DISPATCH(STN_DISABLE, disable);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_ENABLE, enable);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_CLICKED, clicked);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_DBLCLK, dbl_clicked);
}

void grafeex::messaging::static_command_event_handler::on_static_disable(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_static_enable(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_static_clicked(command_event &e){}

void grafeex::messaging::static_command_event_handler::on_static_dbl_clicked(command_event &e){}

grafeex::messaging::button_command_event_handler::~button_command_event_handler(){}

void grafeex::messaging::button_command_event_handler::create_forwarder_list(){
	GMEH_UNIFORM_BCMD_DISPATCH(STN_DISABLE, kill_focus);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_ENABLE, set_focus);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_CLICKED, clicked);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_DBLCLK, dbl_clicked);
}

void grafeex::messaging::button_command_event_handler::on_button_kill_focus(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_button_set_focus(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_button_clicked(command_event &e){}

void grafeex::messaging::button_command_event_handler::on_button_dbl_clicked(command_event &e){}
