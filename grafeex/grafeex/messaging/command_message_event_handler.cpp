#include "command_message_event_handler.h"
#include "message_event_forwarder.h"

grafeex::messaging::command_event_handler::~command_event_handler() = default;

grafeex::messaging::static_command_event_handler::~static_command_event_handler() = default;

void grafeex::messaging::static_command_event_handler::create_forwarder_list(){
	GMEH_UNIFORM_SCMD_DISPATCH(STN_DISABLE, disable);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_ENABLE, enable);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_CLICKED, clicked);
	GMEH_UNIFORM_SCMD_DISPATCH(STN_DBLCLK, dbl_clicked);
}

void grafeex::messaging::static_command_event_handler::on_static_disable(object &e){}

void grafeex::messaging::static_command_event_handler::on_static_enable(object &e){}

void grafeex::messaging::static_command_event_handler::on_static_clicked(object &e){}

void grafeex::messaging::static_command_event_handler::on_static_dbl_clicked(object &e){}

grafeex::messaging::command_event_handler::dispatcher_list_type grafeex::messaging::static_command_event_handler::command_forwarder_list_;

grafeex::messaging::button_command_event_handler::~button_command_event_handler() = default;

void grafeex::messaging::button_command_event_handler::create_forwarder_list(){
	GMEH_UNIFORM_BCMD_DISPATCH(STN_DISABLE, kill_focus);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_ENABLE, set_focus);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_CLICKED, clicked);
	GMEH_UNIFORM_BCMD_DISPATCH(STN_DBLCLK, dbl_clicked);
}

void grafeex::messaging::button_command_event_handler::on_button_kill_focus(object &e){}

void grafeex::messaging::button_command_event_handler::on_button_set_focus(object &e){}

void grafeex::messaging::button_command_event_handler::on_button_clicked(object &e){}

void grafeex::messaging::button_command_event_handler::on_button_dbl_clicked(object &e){}

grafeex::messaging::command_event_handler::dispatcher_list_type grafeex::messaging::button_command_event_handler::command_forwarder_list_;
