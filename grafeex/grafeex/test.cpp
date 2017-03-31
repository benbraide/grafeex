#include "window/frame_window.h"
#include "window/top_level_window.h"
#include "menu/menu_bar.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	grafeex::application::object app;

	grafeex::window::top_level fw(L"Test Window", grafeex::structures::point{ 10 }, { 500, 400 });
	fw.view().show();

	grafeex::menu::bar mb(fw);//Create menu bar and assign to window

	//Create menu items
	grafeex::menu::item i1(mb, L"First");
	grafeex::menu::item i2(mb, L"Second");
	grafeex::menu::item i3(mb, L"Last");
	grafeex::menu::item i4(grafeex::gui::object_sibling(i2, grafeex::gui::object_sibling::sibling_value_type::previous), L"Inserted");

	mb.redraw();//Update menu view

	return app.run();
}
