#include "thread_id.h"

grafeex::threading::id::id(){}

grafeex::threading::id::id(value_type value)
	: base_type(value){}

grafeex::threading::id grafeex::threading::get_current_id(){
	return id(::GetCurrentThreadId());
}
