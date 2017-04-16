#include "mouse_state.h"
#include "../window/window_object.h"

grafeex::messaging::mouse_state::mouse_state(input_event_handler &owner)
	: states_(state::nil){
	object_info_ = object_info{ &owner };
	button_info_ = button_info{};
	drag_info_ = drag_info{ size_type{ ::GetSystemMetrics(SM_CXDRAG), ::GetSystemMetrics(SM_CYDRAG) } };
}

grafeex::messaging::mouse_state::~mouse_state() = default;

grafeex::messaging::input_event_handler *grafeex::messaging::mouse_state::next_object(const point_type &position){
	auto tree_self = dynamic_cast<gui::object_tree *>(object_info_.owner);
	return (tree_self == nullptr) ? nullptr : dynamic_cast<input_event_handler *>(tree_self->get_deepest_hit_target(position));
}

grafeex::messaging::input_event_handler *grafeex::messaging::mouse_state::moused(){
	return object_info_.moused;
}

void grafeex::messaging::mouse_state::leave(mouse_leave_event &e){
	timer_.stop();
	GRAFEEX_REMOVE(states_, state::tracking);
	if (!object_info_.object_owner->dimensions(false).contains(e.position()))//Window departure
		leave_(e);
}

void grafeex::messaging::mouse_state::leave(mouse_client_leave_event &e){
	timer_.stop();
	GRAFEEX_REMOVE(states_, state::inside_client | state::tracking);

	if (!object_info_.object_owner->dimensions(false).contains(e.position())){//Window departure
		mouse_leave_event ev(const_cast<object &>(e.get_object()));
		leave_(ev);
	}
}

void grafeex::messaging::mouse_state::move(mouse_nc_move_event &e){
	timer_.stop();
	if (!GRAFEEX_IS(states_, state::inside)){//Window entry
		track_(false);

		mouse_nc_move_event ev(const_cast<object &>(e.get_object()));
		dispatch_on_enter_(ev);

		if (object_info_.parent != nullptr)//Alert parent state
			object_info_.parent->mouse_state_.child_enter_(*this, ev);

		states_ = state::inside;
		button_info_.states = mouse_key_state_type::nil;
	}

	dispatch_generic_(e);
	if (e.is_propagating())
		object_info_.owner->on_mouse_move(e);

	if (e.is_propagating())
		object_info_.owner->on_mouse_nc_move(e);

	if (object_info_.parent != nullptr){//Pipe event to parent
		if (object_info_.parent->mouse_state_.object_info_.moused != object_info_.owner){
			if (object_info_.parent->mouse_state_.object_info_.moused != nullptr)
				object_info_.parent->mouse_state_.object_info_.moused->mouse_state_.recursive_leave_();
			object_info_.parent->mouse_state_.object_info_.moused = object_info_.owner;
		}
		
		mouse_client_move_event ev(const_cast<object &>(e.get_object()));
		object_info_.parent->mouse_state_.move(ev);
	}
}

void grafeex::messaging::mouse_state::move(mouse_client_move_event &e){
	timer_.stop();

	auto drag_begun = false;
	auto mouse_position = e.position();

	if (!GRAFEEX_IS(states_, state::inside_client)){//Client entry
		if (!GRAFEEX_IS(states_, state::inside)){//Window entry
			mouse_nc_move_event ev(const_cast<object &>(e.get_object()));
			dispatch_on_enter_(ev);

			if (object_info_.parent != nullptr)//Alert parent state
				object_info_.parent->mouse_state_.child_enter_(*this, ev);

			states_ = state::inside;
			button_info_.states = mouse_key_state_type::nil;
		}

		track_(true);
		mouse_client_move_event ev(const_cast<object &>(e.get_object()));
		dispatch_on_enter_(ev);

		GRAFEEX_SET(states_, state::inside_client);
	}
	else//Check drag
		drag_begun = begin_drag_(mouse_position);

	dispatch_generic_(e);
	if (e.is_propagating())
		object_info_.owner->on_mouse_move(e);

	if (e.is_propagating())
		object_info_.owner->on_mouse_client_move(e);

	if (!drag_begun){
		auto hover_delay = object_info_.owner->on_mouse_hover_request(mouse_position);
		if (hover_delay != static_cast<dword_type>(0)){//Schedule hover
			timer_.start(std::chrono::milliseconds(hover_delay), [this, mouse_position](timer_type &){
				object_info_.owner->on_mouse_hover(mouse_position);
			});
		}
	}
	else{//Drag
		auto delta = (mouse_position - button_info_.position);
		drag_info_e drag_info{
			drag_info_.states,
			button_info_.position,
			size_type{ delta.x(), delta.y() }
		};

		if (!GRAFEEX_IS(states_, state::drag_rejected))
			dispatch_on_drag_(drag_info);
	}

	if (object_info_.parent != nullptr){//Pipe event to parent
		if (object_info_.parent->mouse_state_.object_info_.moused != object_info_.owner){
			if (object_info_.parent->mouse_state_.object_info_.moused != nullptr)
				object_info_.parent->mouse_state_.object_info_.moused->mouse_state_.recursive_leave_();
			object_info_.parent->mouse_state_.object_info_.moused = object_info_.owner;
		}

		mouse_client_move_event ev(const_cast<object &>(e.get_object()));
		object_info_.parent->mouse_state_.move(ev);
	}
}

void grafeex::messaging::mouse_state::down(mouse_nc_left_button_down_event &e){
	GMMS_FF(down, left, nc, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::down(mouse_nc_middle_button_down_event &e){
	GMMS_FF(down, middle, nc, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::down(mouse_nc_right_button_down_event &e){
	GMMS_FF(down, right, nc, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::down(mouse_client_left_button_down_event &e){
	GMMS_FF(down, left, client, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::down(mouse_client_middle_button_down_event &e){
	GMMS_FF(down, middle, client, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::down(mouse_client_right_button_down_event &e){
	GMMS_FF(down, right, client, 0);
	pipe_on_button_down_(e);
}

void grafeex::messaging::mouse_state::up(mouse_nc_left_button_up_event &e){
	GMMS_FF(up, left, nc, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::up(mouse_nc_middle_button_up_event &e){
	GMMS_FF(up, middle, nc, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::up(mouse_nc_right_button_up_event &e){
	GMMS_FF(up, right, nc, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::up(mouse_client_left_button_up_event &e){
	GMMS_FF(up, left, client, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::up(mouse_client_middle_button_up_event &e){
	GMMS_FF(up, middle, client, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::up(mouse_client_right_button_up_event &e){
	GMMS_FF(up, right, client, 1);
	pipe_on_button_up_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_nc_left_button_dbl_click_event &e){
	GMMS_FF(dbl_click, left, nc, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_nc_middle_button_dbl_click_event &e){
	GMMS_FF(dbl_click, middle, nc, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_nc_right_button_dbl_click_event &e){
	GMMS_FF(dbl_click, right, nc, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_client_left_button_dbl_click_event &e){
	GMMS_FF(dbl_click, left, client, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_client_middle_button_dbl_click_event &e){
	GMMS_FF(dbl_click, middle, client, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::dbl_click(mouse_client_right_button_dbl_click_event &e){
	GMMS_FF(dbl_click, right, client, 2);
	pipe_on_button_dbl_click_(e);
}

void grafeex::messaging::mouse_state::wheel(mouse_vertical_wheel_event &e){
	timer_.stop();
	dispatch_generic_(e);

	auto handled = false;
	if (e.is_propagating())
		handled = object_info_.owner->on_mouse_wheel(e);

	if (e.is_propagating())
		handled = object_info_.owner->on_mouse_vertical_wheel(e);

	if (!handled && object_info_.parent != nullptr){//Pipe event to parent
		mouse_vertical_wheel_event ev(const_cast<object &>(e.get_object()));
		object_info_.parent->mouse_state_.wheel(ev);
	}
}

void grafeex::messaging::mouse_state::wheel(mouse_horizontal_wheel_event &e){
	timer_.stop();
	dispatch_generic_(e);

	auto handled = false;
	if (e.is_propagating())
		handled = object_info_.owner->on_mouse_wheel(e);

	if (e.is_propagating())
		handled = object_info_.owner->on_mouse_horizontal_wheel(e);

	if (!handled && object_info_.parent != nullptr){//Pipe event to parent
		mouse_horizontal_wheel_event ev(const_cast<object &>(e.get_object()));
		object_info_.parent->mouse_state_.wheel(ev);
	}
}

void grafeex::messaging::mouse_state::recursive_leave_(){
	if (object_info_.moused != nullptr){//Pipe to moused child
		object_info_.moused->mouse_state_.recursive_leave_();
		object_info_.moused = nullptr;
	}

	if (GRAFEEX_IS(states_, state::dragging) && !GRAFEEX_IS(states_, state::drag_rejected))//Drag out
		object_info_.owner->on_mouse_drag_out(drag_info_e{ drag_info_.states, button_info_.position });

	if (GRAFEEX_IS(states_, state::inside_client))//Client departure
		object_info_.owner->on_mouse_client_leave();

	states_ = state::nil;
	object_info_.owner->on_mouse_leave();
}

void grafeex::messaging::mouse_state::leave_(mouse_leave_event &e){
	dispatch_generic_(e);

	auto is_propagating = e.is_propagating();
	if (is_propagating && GRAFEEX_IS(states_, state::dragging) && !GRAFEEX_IS(states_, state::drag_rejected))//Drag out
		object_info_.owner->on_mouse_drag_out(drag_info_e{ drag_info_.states, button_info_.position });

	if (is_propagating && GRAFEEX_IS(states_, state::inside_client))//Client departure
		object_info_.owner->on_mouse_client_leave();

	states_ = state::nil;
	if (is_propagating)
		object_info_.owner->on_mouse_leave();

	if (object_info_.parent != nullptr)//Alert parent state
		object_info_.parent->mouse_state_.child_leave_(*this, e);
}

void grafeex::messaging::mouse_state::child_leave_(mouse_state &child, mouse_leave_event &e){
	GRAFEEX_REMOVE(states_, state::child);
	if (!object_info_.object_owner->dimensions(false).contains(e.position())){//Window departure
		mouse_leave_event ev(const_cast<object &>(e.get_object()));
		leave_(ev);
	}
	else//Track client leave
		track_(true);
}

void grafeex::messaging::mouse_state::child_enter_(mouse_state &child, mouse_nc_move_event &e){
	GRAFEEX_SET(states_, state::inside_client | state::child);
}

bool grafeex::messaging::mouse_state::begin_drag_(const point_type &mouse_position){
	if (GRAFEEX_IS(states_, state::dragging))
		return true;//Previously rejected

	if (!GRAFEEX_IS(states_, state::button_down) || drag_handled_())
		return false;//No button down OR Drag handled by child object

	auto delta = (mouse_position - button_info_.position);
	size_type abs_delta{
		(delta.x() < 0) ? -delta.x() : delta.x(),
		(delta.y() < 0) ? -delta.y() : delta.y()
	};

	if (abs_delta.width() < drag_info_.threshold.width() && abs_delta.height() < drag_info_.threshold.height())
		return false;//Within the drag threshold

	drag_info_.states = button_info_.states;
	GRAFEEX_SET(states_, state::dragging);

	if (!object_info_.owner->on_mouse_begin_drag(drag_info_e{ button_info_.states, button_info_.position,
		size_type{ delta.x(), delta.y() } })){//Rejected
		GRAFEEX_SET(states_, state::drag_rejected);
	}

	return true;
}

bool grafeex::messaging::mouse_state::drag_handled_(){
	if (GRAFEEX_IS(states_, state::dragging))
		return true;

	return (object_info_.focused == nullptr) ? false : object_info_.focused->mouse_state_.drag_handled_();
}

void grafeex::messaging::mouse_state::track_(bool client){
	if (GRAFEEX_IS_ANY(states_, state::child | state::tracking))
		return;//No tracking

	auto window_owner = dynamic_cast<window::object *>(object_info_.owner);
	if (window_owner != nullptr){
		GRAFEEX_SET(states_, state::tracking);
		track_info_type track_info{ sizeof(track_info_type), TME_LEAVE | (client ? 0u : TME_NONCLIENT), *window_owner, 0 };
		::TrackMouseEvent(&track_info);//Notify when mouse leaves window
	}
}

void grafeex::messaging::mouse_state::dispatch_generic_(mouse_event &e){
	if (object_info_.general_event_owner != nullptr)
		object_info_.general_event_owner->on_event(e);

	if (e.is_propagating())
		object_info_.owner->on_input(e);

	if (e.is_propagating())
		object_info_.owner->on_mouse(e);
}

void grafeex::messaging::mouse_state::dispatch_on_enter_(mouse_nc_move_event &e){
	dispatch_generic_(e);
	if (e.is_propagating())
		object_info_.owner->on_mouse_enter(e);

	if (e.is_propagating())
		object_info_.owner->on_mouse_nc_enter(e);
}

void grafeex::messaging::mouse_state::dispatch_on_enter_(mouse_client_move_event &e){
	dispatch_generic_(e);
	if (e.is_propagating())
		object_info_.owner->on_mouse_enter(e);

	if (e.is_propagating())
		object_info_.owner->on_mouse_client_enter(e);
}

void grafeex::messaging::mouse_state::dispatch_on_drag_(const drag_info_e &info){
	object_info_.owner->on_mouse_drag(info);
	switch (button_info_.states){
	case mouse_key_state_type::left_button:
		object_info_.owner->on_mouse_left_drag(info);
		break;
	case mouse_key_state_type::middle_button:
		object_info_.owner->on_mouse_middle_drag(info);
		break;
	case mouse_key_state_type::right_button:
		object_info_.owner->on_mouse_right_drag(info);
		break;
	default:
		break;
	}
}

void grafeex::messaging::mouse_state::update_moused_(input_event_handler *target){
	object_info_.moused = target;
}
