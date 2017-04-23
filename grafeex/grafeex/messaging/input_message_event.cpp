#include "input_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::input_event::input_event(object &value)
	: message_event(value){}

grafeex::messaging::input_event::~input_event() = default;

grafeex::messaging::message_event &grafeex::messaging::input_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		object_->target()->on_input(*this);
	return *this;
}

grafeex::messaging::input_event::key_state_type grafeex::messaging::input_event::key_states() const{
	return retrieve_key_states();
}

bool grafeex::messaging::input_event::cache_key_states(){
	return (::GetKeyboardState(keyboard_state) != FALSE);
}

grafeex::messaging::input_event::key_state_type grafeex::messaging::input_event::retrieve_key_states(){
	static const key_map_info_list_type key_map_info_list{
		key_map_info{ VK_LSHIFT, key_state_type::left_shift, false },
		key_map_info{ VK_RSHIFT, key_state_type::right_shift, false },
		key_map_info{ VK_LCONTROL, key_state_type::left_ctrl, false },
		key_map_info{ VK_RCONTROL, key_state_type::right_ctrl, false },
		key_map_info{ VK_LMENU, key_state_type::left_alt, false },
		key_map_info{ VK_RMENU, key_state_type::right_alt, false },
		key_map_info{ VK_LWIN, key_state_type::left_win, false },
		key_map_info{ VK_RWIN, key_state_type::right_win, false },
		key_map_info{ VK_CAPITAL, key_state_type::caps, true },
		key_map_info{ VK_NUMLOCK, key_state_type::numpad, true },
		key_map_info{ VK_SCROLL, key_state_type::scroll, true },
		key_map_info{ VK_INSERT, key_state_type::insert, true },
	};

	if (!cache_key_states())
		return key_state_type::nil;

	auto states = key_state_type::nil;
	for (auto &info : key_map_info_list){
		if (info.toggle){
			if ((keyboard_state[info.key] & 1) != 0)
				GRAFEEX_SET(states, info.value);
		}
		else if (keyboard_state[info.key] < 0)
			GRAFEEX_SET(states, info.value);
	}

	return states;
}

grafeex::messaging::input_event::byte_type grafeex::messaging::input_event::keyboard_state[0x100];

grafeex::messaging::key_event::key_event(object &value)
	: input_event(value), states_(state::nil){
	code_ = value.info().wparam<unsigned short>();

	auto lp_value = value.info().lparam();
	repeat_count_ = *reinterpret_cast<short *>(&lp_value);
	scan_code_ = static_cast<short>((reinterpret_cast<byte_type *>(&lp_value))[2]);

	std::bitset<sizeof(object::result_type) * 8> lparam_bits(value.info().lparam());
	if (lparam_bits.test(24))//Extended
		GRAFEEX_SET(states_, state::is_extended);

	if (lparam_bits.test(29))//Alt
		GRAFEEX_SET(states_, state::alt_down);

	if (lparam_bits.test(30))//Was down
		GRAFEEX_SET(states_, state::was_down);

	if (lparam_bits.test(31))//Being released
		GRAFEEX_SET(states_, state::being_released);
}

grafeex::messaging::key_event::~key_event() = default;

grafeex::messaging::message_event &grafeex::messaging::key_event::dispatch(){
	if (input_event::dispatch().is_propagating())
		object_->target()->on_key(*this);
	return *this;
}

bool grafeex::messaging::key_event::is_mouse() const{
	return false;
}

bool grafeex::messaging::key_event::is_system() const{
	return GRAFEEX_IS(states_, state::is_system);
}

bool grafeex::messaging::key_event::is_extended() const{
	return GRAFEEX_IS(states_, state::is_extended);
}

bool grafeex::messaging::key_event::was_down() const{
	return GRAFEEX_IS(states_, state::was_down);
}

bool grafeex::messaging::key_event::is_being_released() const{
	return GRAFEEX_IS(states_, state::being_released);
}

bool grafeex::messaging::key_event::alt_key_down() const{
	return GRAFEEX_IS(states_, state::alt_down);
}

bool grafeex::messaging::key_event::is_down() const{
	return GRAFEEX_IS(states_, state::down);
}

bool grafeex::messaging::key_event::is_up() const{
	return GRAFEEX_IS(states_, state::up);
}

bool grafeex::messaging::key_event::is_char() const{
	return GRAFEEX_IS(states_, state::pressed);
}

bool grafeex::messaging::key_event::is_dead() const{
	return GRAFEEX_IS(states_, state::dead);
}

unsigned short grafeex::messaging::key_event::code() const{
	return code_;
}

short grafeex::messaging::key_event::scan_code() const{
	return scan_code_;
}

short grafeex::messaging::key_event::repeat_count() const{
	return repeat_count_;
}

grafeex::messaging::key_event::state grafeex::messaging::key_event::states() const{
	return states_;
}

grafeex::messaging::key_down_event::key_down_event(object &value)
	: key_event(value){
	GRAFEEX_SET(states_, state::down);
}

grafeex::messaging::key_down_event::~key_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::key_down_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_key_down(*this);
	return *this;
}

grafeex::messaging::key_up_event::key_up_event(object &value)
	: key_event(value){
	GRAFEEX_SET(states_, state::up);
}

grafeex::messaging::key_up_event::~key_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::key_up_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_key_up(*this);
	return *this;
}

grafeex::messaging::char_event::char_event(object &value)
	: key_event(value){
	GRAFEEX_SET(states_, state::pressed);
}

grafeex::messaging::char_event::~char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_char(*this);
	return *this;
}

grafeex::messaging::dead_char_event::dead_char_event(object &value)
	: key_event(value){
	GRAFEEX_SET(states_, state::dead);
}

grafeex::messaging::dead_char_event::~dead_char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::dead_char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_dead_char(*this);
	return *this;
}

grafeex::messaging::normal_key_down_event::normal_key_down_event(object &value)
	: key_down_event(value){}

grafeex::messaging::normal_key_down_event::~normal_key_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::normal_key_down_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_normal_key_down(*this);
	return *this;
}

grafeex::messaging::normal_key_up_event::normal_key_up_event(object &value)
	: key_up_event(value){}

grafeex::messaging::normal_key_up_event::~normal_key_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::normal_key_up_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_normal_key_up(*this);
	return *this;
}

grafeex::messaging::normal_char_event::normal_char_event(object &value)
	: char_event(value){}

grafeex::messaging::normal_char_event::~normal_char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::normal_char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_normal_char(*this);
	return *this;
}

grafeex::messaging::normal_dead_char_event::normal_dead_char_event(object &value)
	: dead_char_event(value){}

grafeex::messaging::normal_dead_char_event::~normal_dead_char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::normal_dead_char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_normal_dead_char(*this);
	return *this;
}

grafeex::messaging::system_key_down_event::system_key_down_event(object &value)
	: key_down_event(value){
	GRAFEEX_SET(states_, state::is_system);
}

grafeex::messaging::system_key_down_event::~system_key_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::system_key_down_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_system_key_down(*this);
	return *this;
}

grafeex::messaging::system_key_up_event::system_key_up_event(object &value)
	: key_up_event(value){
	GRAFEEX_SET(states_, state::is_system);
}

grafeex::messaging::system_key_up_event::~system_key_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::system_key_up_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_system_key_up(*this);
	return *this;
}

grafeex::messaging::system_char_event::system_char_event(object &value)
	: char_event(value){
	GRAFEEX_SET(states_, state::is_system);
}

grafeex::messaging::system_char_event::~system_char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::system_char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_system_char(*this);
	return *this;
}

grafeex::messaging::system_dead_char_event::system_dead_char_event(object &value)
	: dead_char_event(value){
	GRAFEEX_SET(states_, state::is_system);
}

grafeex::messaging::system_dead_char_event::~system_dead_char_event() = default;

grafeex::messaging::message_event &grafeex::messaging::system_dead_char_event::dispatch(){
	if (key_event::dispatch().is_propagating())
		object_->target()->on_system_dead_char(*this);
	return *this;
}

grafeex::messaging::mouse_event::mouse_event(object &value)
	: input_event(value){}

grafeex::messaging::mouse_event::~mouse_event() = default;

bool grafeex::messaging::mouse_event::is_mouse() const{
	return true;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_event::hit_target() const{
	return hit_target_type::client;
}

grafeex::messaging::mouse_event::point_type grafeex::messaging::mouse_event::position() const{
	return object_->info().mouse_position();
}

grafeex::messaging::mouse_leave_event::mouse_leave_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_leave_event::~mouse_leave_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_leave_event::dispatch(){
	object_->target()->mouse_state().leave(*this);
	return *this;
}

grafeex::messaging::mouse_client_leave_event::mouse_client_leave_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_client_leave_event::~mouse_client_leave_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_leave_event::dispatch(){
	object_->target()->mouse_state().leave(*this);
	return *this;
}

grafeex::messaging::mouse_move_event::mouse_move_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_move_event::~mouse_move_event() = default;

grafeex::messaging::mouse_nc_move_event::mouse_nc_move_event(object &value)
	: mouse_move_event(value){}

grafeex::messaging::mouse_nc_move_event::~mouse_nc_move_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_move_event::dispatch(){
	object_->target()->mouse_state().move(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_move_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_client_move_event::mouse_client_move_event(object &value)
	: mouse_move_event(value){}

grafeex::messaging::mouse_client_move_event::~mouse_client_move_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_move_event::dispatch(){
	auto target = object_->target()->mouse_state().next_object(position());
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().move(*this);
	return *this;
}

grafeex::messaging::mouse_button_down_event::mouse_button_down_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_button_down_event::~mouse_button_down_event() = default;

grafeex::messaging::mouse_button_up_event::mouse_button_up_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_button_up_event::~mouse_button_up_event() = default;

grafeex::messaging::mouse_button_dbl_click_event::mouse_button_dbl_click_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_button_dbl_click_event::~mouse_button_dbl_click_event() = default;

grafeex::messaging::mouse_left_button_down_event::mouse_left_button_down_event(object &value)
	: mouse_button_down_event(value){}

grafeex::messaging::mouse_left_button_down_event::~mouse_left_button_down_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_left_button_down_event::button() const{
	return mouse_key_state_type::left_button;
}

grafeex::messaging::mouse_middle_button_down_event::mouse_middle_button_down_event(object &value)
	: mouse_button_down_event(value){}

grafeex::messaging::mouse_middle_button_down_event::~mouse_middle_button_down_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_middle_button_down_event::button() const{
	return mouse_key_state_type::middle_button;
}

grafeex::messaging::mouse_right_button_down_event::mouse_right_button_down_event(object &value)
	: mouse_button_down_event(value){}

grafeex::messaging::mouse_right_button_down_event::~mouse_right_button_down_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_right_button_down_event::button() const{
	return mouse_key_state_type::right_button;
}

grafeex::messaging::mouse_left_button_up_event::mouse_left_button_up_event(object &value)
	: mouse_button_up_event(value){}

grafeex::messaging::mouse_left_button_up_event::~mouse_left_button_up_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_left_button_up_event::button() const{
	return mouse_key_state_type::left_button;
}

grafeex::messaging::mouse_middle_button_up_event::mouse_middle_button_up_event(object &value)
	: mouse_button_up_event(value){}

grafeex::messaging::mouse_middle_button_up_event::~mouse_middle_button_up_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_middle_button_up_event::button() const{
	return mouse_key_state_type::middle_button;
}

grafeex::messaging::mouse_right_button_up_event::mouse_right_button_up_event(object &value)
	: mouse_button_up_event(value){}

grafeex::messaging::mouse_right_button_up_event::~mouse_right_button_up_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_right_button_up_event::button() const{
	return mouse_key_state_type::right_button;
}

grafeex::messaging::mouse_left_button_dbl_click_event::mouse_left_button_dbl_click_event(object &value)
	: mouse_button_dbl_click_event(value){}

grafeex::messaging::mouse_left_button_dbl_click_event::~mouse_left_button_dbl_click_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_left_button_dbl_click_event::button() const{
	return mouse_key_state_type::left_button;
}

grafeex::messaging::mouse_middle_button_dbl_click_event::mouse_middle_button_dbl_click_event(object &value)
	: mouse_button_dbl_click_event(value){}

grafeex::messaging::mouse_middle_button_dbl_click_event::~mouse_middle_button_dbl_click_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_middle_button_dbl_click_event::button() const{
	return mouse_key_state_type::middle_button;
}

grafeex::messaging::mouse_right_button_dbl_click_event::mouse_right_button_dbl_click_event(object &value)
	: mouse_button_dbl_click_event(value){}

grafeex::messaging::mouse_right_button_dbl_click_event::~mouse_right_button_dbl_click_event() = default;

grafeex::messaging::mouse_event::mouse_key_state_type grafeex::messaging::mouse_right_button_dbl_click_event::button() const{
	return mouse_key_state_type::right_button;
}

grafeex::messaging::mouse_nc_left_button_down_event::mouse_nc_left_button_down_event(object &value)
	: mouse_left_button_down_event(value){}

grafeex::messaging::mouse_nc_left_button_down_event::~mouse_nc_left_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_left_button_down_event::dispatch(){
	object_->target()->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_left_button_down_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_middle_button_down_event::mouse_nc_middle_button_down_event(object &value)
	: mouse_middle_button_down_event(value){}

grafeex::messaging::mouse_nc_middle_button_down_event::~mouse_nc_middle_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_middle_button_down_event::dispatch(){
	object_->target()->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_middle_button_down_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_right_button_down_event::mouse_nc_right_button_down_event(object &value)
	: mouse_right_button_down_event(value){}

grafeex::messaging::mouse_nc_right_button_down_event::~mouse_nc_right_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_right_button_down_event::dispatch(){
	object_->target()->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_right_button_down_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_left_button_up_event::mouse_nc_left_button_up_event(object &value)
	: mouse_left_button_up_event(value){}

grafeex::messaging::mouse_nc_left_button_up_event::~mouse_nc_left_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_left_button_up_event::dispatch(){
	object_->target()->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_left_button_up_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_middle_button_up_event::mouse_nc_middle_button_up_event(object &value)
	: mouse_middle_button_up_event(value){}

grafeex::messaging::mouse_nc_middle_button_up_event::~mouse_nc_middle_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_middle_button_up_event::dispatch(){
	object_->target()->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_middle_button_up_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_right_button_up_event::mouse_nc_right_button_up_event(object &value)
	: mouse_right_button_up_event(value){}

grafeex::messaging::mouse_nc_right_button_up_event::~mouse_nc_right_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_right_button_up_event::dispatch(){
	object_->target()->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_right_button_up_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_left_button_dbl_click_event::mouse_nc_left_button_dbl_click_event(object &value)
	: mouse_left_button_dbl_click_event(value){}

grafeex::messaging::mouse_nc_left_button_dbl_click_event::~mouse_nc_left_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_left_button_dbl_click_event::dispatch(){
	object_->target()->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_left_button_dbl_click_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_middle_button_dbl_click_event::mouse_nc_middle_button_dbl_click_event(object &value)
	: mouse_middle_button_dbl_click_event(value){}

grafeex::messaging::mouse_nc_middle_button_dbl_click_event::~mouse_nc_middle_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_middle_button_dbl_click_event::dispatch(){
	object_->target()->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_middle_button_dbl_click_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_nc_right_button_dbl_click_event::mouse_nc_right_button_dbl_click_event(object &value)
	: mouse_right_button_dbl_click_event(value){}

grafeex::messaging::mouse_nc_right_button_dbl_click_event::~mouse_nc_right_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_nc_right_button_dbl_click_event::dispatch(){
	object_->target()->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_event::hit_target_type grafeex::messaging::mouse_nc_right_button_dbl_click_event::hit_target() const{
	return static_cast<hit_target_type>(object_->info().wparam<int>());
}

grafeex::messaging::mouse_client_left_button_down_event::mouse_client_left_button_down_event(object &value)
	: mouse_left_button_down_event(value){}

grafeex::messaging::mouse_client_left_button_down_event::~mouse_client_left_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_left_button_down_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_client_middle_button_down_event::mouse_client_middle_button_down_event(object &value)
	: mouse_middle_button_down_event(value){}

grafeex::messaging::mouse_client_middle_button_down_event::~mouse_client_middle_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_middle_button_down_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_client_right_button_down_event::mouse_client_right_button_down_event(object &value)
	: mouse_right_button_down_event(value){}

grafeex::messaging::mouse_client_right_button_down_event::~mouse_client_right_button_down_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_right_button_down_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().down(*this);
	return *this;
}

grafeex::messaging::mouse_client_left_button_up_event::mouse_client_left_button_up_event(object &value)
	: mouse_left_button_up_event(value){}

grafeex::messaging::mouse_client_left_button_up_event::~mouse_client_left_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_left_button_up_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_client_middle_button_up_event::mouse_client_middle_button_up_event(object &value)
	: mouse_middle_button_up_event(value){}

grafeex::messaging::mouse_client_middle_button_up_event::~mouse_client_middle_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_middle_button_up_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_client_right_button_up_event::mouse_client_right_button_up_event(object &value)
	: mouse_right_button_up_event(value){}

grafeex::messaging::mouse_client_right_button_up_event::~mouse_client_right_button_up_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_right_button_up_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().up(*this);
	return *this;
}

grafeex::messaging::mouse_client_left_button_dbl_click_event::mouse_client_left_button_dbl_click_event(object &value)
	: mouse_left_button_dbl_click_event(value){}

grafeex::messaging::mouse_client_left_button_dbl_click_event::~mouse_client_left_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_left_button_dbl_click_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_client_middle_button_dbl_click_event::mouse_client_middle_button_dbl_click_event(object &value)
	: mouse_middle_button_dbl_click_event(value){}

grafeex::messaging::mouse_client_middle_button_dbl_click_event::~mouse_client_middle_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_middle_button_dbl_click_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_client_right_button_dbl_click_event::mouse_client_right_button_dbl_click_event(object &value)
	: mouse_right_button_dbl_click_event(value){}

grafeex::messaging::mouse_client_right_button_dbl_click_event::~mouse_client_right_button_dbl_click_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_client_right_button_dbl_click_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().dbl_click(*this);
	return *this;
}

grafeex::messaging::mouse_wheel_event::mouse_wheel_event(object &value)
	: mouse_event(value){}

grafeex::messaging::mouse_wheel_event::~mouse_wheel_event() = default;

short grafeex::messaging::mouse_wheel_event::delta() const{
	return static_cast<short>(object_->info().high_wparam<int>() / WHEEL_DELTA);
}

grafeex::messaging::mouse_vertical_wheel_event::mouse_vertical_wheel_event(object &value)
	: mouse_wheel_event(value){}

grafeex::messaging::mouse_vertical_wheel_event::~mouse_vertical_wheel_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_vertical_wheel_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().wheel(*this);
	return *this;
}

bool grafeex::messaging::mouse_vertical_wheel_event::is_vertical() const{
	return true;
}

grafeex::messaging::mouse_horizontal_wheel_event::mouse_horizontal_wheel_event(object &value)
	: mouse_wheel_event(value){}

grafeex::messaging::mouse_horizontal_wheel_event::~mouse_horizontal_wheel_event() = default;

grafeex::messaging::message_event &grafeex::messaging::mouse_horizontal_wheel_event::dispatch(){
	auto target = object_->target()->mouse_state().moused();
	if (target == nullptr)
		target = object_->target();

	target->mouse_state().wheel(*this);
	return *this;
}

bool grafeex::messaging::mouse_horizontal_wheel_event::is_vertical() const{
	return false;
}
