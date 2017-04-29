#include "notify_message_event_handler.h"
#include "message_event_forwarder.h"

grafeex::messaging::notify_event_handler::~notify_event_handler() = default;

grafeex::messaging::notify_event_handler::dword_type grafeex::messaging::notify_event_handler::on_control_draw(custom_draw_event &e){
	return static_cast<dword_type>(e.handle().get_object().value());
}

grafeex::messaging::button_notify_event_handler::~button_notify_event_handler() = default;

void grafeex::messaging::button_notify_event_handler::create_forwarder_list(){
	GAPP_NOT_DISPATCH(NM_CUSTOMDRAW, custom_draw_event);
	GNEH_UNIFORM_BNOT_DISPATCH(BCN_DROPDOWN, dropdown);
	GNEH_UNIFORM_BNOT_DISPATCH(BCN_HOTITEMCHANGE, highlight_change);
}

void grafeex::messaging::button_notify_event_handler::on_button_dropdown(object &e){}

void grafeex::messaging::button_notify_event_handler::on_button_highlight_change(object &e){
	if (e.info().lparam<info_type *>()->dwFlags == HICF_ENTERING)
		on_button_enter(e);
	else//Leave
		on_button_leave(e);
}

void grafeex::messaging::button_notify_event_handler::on_button_enter(object &e){}

void grafeex::messaging::button_notify_event_handler::on_button_leave(object &e){}

grafeex::messaging::notify_event_handler::dispatcher_list_type grafeex::messaging::button_notify_event_handler::notify_forwarder_list_;
