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

grafeex::messaging::tool_tip_notify_event_handler::~tool_tip_notify_event_handler() = default;

void grafeex::messaging::tool_tip_notify_event_handler::create_forwarder_list(){
	GAPP_NOT_DISPATCH(NM_CUSTOMDRAW, custom_draw_event);
	GAPP_NOT_DISPATCH(TTN_GETDISPINFOW, tool_tip_get_text_event);
	GNEH_UNIFORM_TTNOT_DISPATCH(TTN_SHOW, show);
	GNEH_UNIFORM_TTNOT_DISPATCH(TTN_POP, hide);
	GNEH_UNIFORM_TTNOT_DISPATCH(TTN_LINKCLICK, link_click);
}

void grafeex::messaging::tool_tip_notify_event_handler::on_tool_tip_show(object &e){}

void grafeex::messaging::tool_tip_notify_event_handler::on_tool_tip_hide(object &e){}

void grafeex::messaging::tool_tip_notify_event_handler::on_tool_tip_link_click(object &e){}

grafeex::messaging::notify_event_handler::dispatcher_list_type grafeex::messaging::tool_tip_notify_event_handler::notify_forwarder_list_;

grafeex::messaging::tab_notify_event_handler::~tab_notify_event_handler() = default;

void grafeex::messaging::tab_notify_event_handler::create_forwarder_list(){
	GNEH_UNIFORM_TABNOT_DISPATCH(NM_CLICK, click);
	GNEH_UNIFORM_TABNOT_DISPATCH(NM_DBLCLK, dbl_click);
	GNEH_UNIFORM_TABNOT_DISPATCH(NM_RCLICK, right_click);
	GNEH_UNIFORM_TABNOT_DISPATCH(NM_RDBLCLK, right_dbl_click);
	GNEH_UNIFORM_TABNOT_DISPATCH(NM_RELEASEDCAPTURE, released_capture);
	GNEH_UNIFORM_TABNOT_DISPATCH(TCN_FOCUSCHANGE, focus_change);
	GNEH_UNIFORM_TABNOT_DISPATCH(TCN_KEYDOWN, key_down);
	GNEH_UNIFORM_TABNOT_DISPATCH(TCN_SELCHANGE, selection_change);
	GNEH_UNIFORM_TABNOT_DISPATCH(TCN_SELCHANGING, selection_changing);
}

void grafeex::messaging::tab_notify_event_handler::on_tab_click(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_dbl_click(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_right_click(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_right_dbl_click(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_released_capture(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_focus_change(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_key_down(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_selection_change(object &e){}

void grafeex::messaging::tab_notify_event_handler::on_tab_selection_changing(object &e){}

grafeex::messaging::notify_event_handler::dispatcher_list_type grafeex::messaging::tab_notify_event_handler::notify_forwarder_list_;
