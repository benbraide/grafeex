#include "common/random_bool.h"
#include "window/frame_window.h"
#include "window/top_level_window.h"
#include "menu/menu_bar.h"
#include "collections/menu_collection.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	grafeex::application::object app;

	grafeex::window::top_level fw(L"Test Window", grafeex::structures::point{ 10 }, { 500, 400 });
	fw.view().show();

	auto count = 0;
	grafeex::common::random_bool rand;
	fw.events().close([&rand, &count](){
		std::string s = "Window closing...";
		return (rand.generate() || ++count >= 4);
	});

	grafeex::menu::bar mb(fw);//Create menu bar and assign to window

	//Create menu items
	grafeex::menu::item i1(mb, L"First");
	grafeex::menu::item i2(mb, L"Second");
	grafeex::menu::item i3(mb, L"Last");
	grafeex::menu::item i4(grafeex::gui::object_sibling(i2, grafeex::gui::object_sibling::sibling_value_type::next), L"Inserted");
	grafeex::menu::item i5(mb, L"Drop");

	grafeex::collections::menu_popup drop(i5);

	drop.item(L"first", [](){});
	drop.item(L"second", [](){});
	drop.item(L"inserted", [](){}, 1);
	drop.separator();
	drop.sub(L"sub", [](grafeex::collections::menu_interface &sub){
		sub.item(L"_first", [](){});
		sub.separator();
		sub.item(L"_last", [](){});
	});
	drop.separator();
	drop.group([](grafeex::collections::menu_interface &group){
		group.item(L"radio_1", [](){});
		group.item(L"radio_2", [](){});
		group.item(L"radio_3", [](){});
	});
	drop.separator();
	drop.item(L"last", [](){});

	mb.redraw();//Update menu view

	return app.run();
}
