#include "window/frame_window.h"
#include "window/top_level_window.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	grafeex::application::object app;

	grafeex::window::top_level fw(L"Test Window", grafeex::structures::point{ 10 }, { 500, 400 });
	fw.view().show();

	return app.run();
}
