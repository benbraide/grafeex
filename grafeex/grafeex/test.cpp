#include "wrappers/hwnd_wrapper.h"
#include "wrappers/wnd_class_wrapper.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	grafeex::structures::point p;
	grafeex::structures::size s;

	grafeex::structures::rect r;
	grafeex::structures::ref_rect rr;

	grafeex::wrappers::wnd_class wc(L"ben", 0, nullptr);

	return 0;
}
