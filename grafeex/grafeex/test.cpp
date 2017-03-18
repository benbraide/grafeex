#include "wrappers/hwnd_wrapper.h"
#include "wrappers/wnd_class_wrapper.h"
#include "threading/thread_id.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	grafeex::structures::point p;
	grafeex::structures::size s;

	grafeex::structures::rect r;
	grafeex::structures::ref_rect rr;

	grafeex::wrappers::wnd_class wc(L"ben", 0, nullptr);

	auto b = (grafeex::threading::get_current_id() == grafeex::threading::id());
	grafeex::threading::id::value_type v = grafeex::threading::get_current_id();

	return 0;
}
