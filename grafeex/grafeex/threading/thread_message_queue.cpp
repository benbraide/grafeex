#include "thread_message_queue.h"

grafeex::threading::message_queue::message_queue()
	: event_(L""){}

bool grafeex::threading::message_queue::get(msg_type &msg, const hwnd_type &target, const filter_range_type &filter_range){
	return (::GetMessageW(msg, target, filter_range.first, filter_range.second) != FALSE);
}

bool grafeex::threading::message_queue::peek(msg_type &msg, peek_type type, const hwnd_type &target, const filter_range_type &filter_range){
	return (::PeekMessageW(msg, target, filter_range.first, filter_range.second, static_cast<uint_type>(type)) != FALSE);
}

bool grafeex::threading::message_queue::wake_wait(){
	return event_.set();
}

grafeex::threading::message_queue::point_type grafeex::threading::message_queue::get_last_mouse_position(){
	return GRAFEEX_MAKE_MOUSE_POSITION(::GetMessagePos());
}

long grafeex::threading::message_queue::get_last_time(){
	return ::GetMessageTime();
}

bool grafeex::threading::message_queue::is_sent(){
	return (::InSendMessage() != FALSE);
}

grafeex::threading::message_queue::sent_type grafeex::threading::message_queue::get_sent_type(){
	return static_cast<sent_type>(::InSendMessageEx(nullptr));
}

bool grafeex::threading::message_queue::reply(result_type value){
	return (::ReplyMessage(value) != FALSE);
}

void grafeex::threading::message_queue::post_quit(int exit_code){
	::PostQuitMessage(exit_code);
}
