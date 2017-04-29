#include "common/random_bool.h"
#include "common/hook.h"
#include "window/frame_window.h"
#include "window/top_level_window.h"
#include "window/modal_dialog_window.h"
#include "menu/menu_bar.h"
#include "menu/menu_check_item.h"
#include "collections/menu_collection.h"
#include "controls/default_button_control.h"
#include "controls/default_split_button_control.h"
#include "controls/default_command_link_control.h"
#include "controls/check_control.h"
#include "controls/radio_control.h"
#include "controls/radio_control_group.h"
#include "controls/label_control.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	typedef grafeex::window::object::d2d_point_type d2d_point_type;
	typedef grafeex::window::object::d2d_size_type d2d_size_type;

	typedef grafeex::structures::point point_type;
	typedef grafeex::structures::size size_type;

	typedef grafeex::structures::float_size float_size_type;
	typedef grafeex::structures::rect_origin_type alignment_type;

	grafeex::application::object app;

	grafeex::window::top_level fw(L"Test Window", d2d_point_type{ 10.0f, 10.0f }, d2d_size_type{ 500.0f, 400.0f });
	fw.view().show();

	grafeex::window::dialog_frame dfm(fw, L"Modal Dialog", point_type{ 10 }, size_type{ 300, 200 });
	dfm.attributes().fill_parent(float_size_type{ 0.5f, 1.0f });
	dfm.attributes().align(true, alignment_type::top | alignment_type::right);
	dfm.view().show();
	//dfm.do_modal(fw);

	grafeex::window::controls::button btn(dfm, L"Button Test", point_type{ 10 });
	grafeex::window::controls::default_button dbtn(dfm, L"DefButton Test", point_type{ 10, 40 });
	grafeex::window::controls::split_button sbtn(dfm, L"SplitButton Test", point_type{ 10, 70 });
	grafeex::window::controls::default_split_button dsbtn(dfm, L"DefSplitButton Test", point_type{ 10, 100 });
	grafeex::window::controls::check chk(dfm, L"Check Test", point_type{ 10, 130 });

	grafeex::window::controls::radio_group rgrp(dfm);
	grafeex::window::controls::radio rad_0(rgrp, L"Radio Test 0", point_type{ 10, 150 });
	grafeex::window::controls::radio rad_1(rgrp, L"Radio Test 1", point_type{ 10, 170 });
	grafeex::window::controls::radio rad_2(rgrp, L"Radio Test 2", point_type{ 10, 190 });

	grafeex::window::controls::label lbl(dfm, L"Label Text", point_type{ 10, 210 });

	auto count = 0;
	grafeex::common::random_bool rand;
	fw.events().close([&rand, &count](){
		std::string s = "Window closing...";
		return (rand.generate() || ++count >= 4);
	});

	grafeex::common::random_int rand_int;
	std::thread([&fw, &rand_int, &btn, &chk]{
		typedef ::BYTE byte_type;
		typedef ::HFONT font_type;

		::Sleep(5000);
		btn.label(L"Label Changed");

		::Sleep(5000);
		btn.view().font(L"Georgia");
		chk.view().font(L"Georgia");

		while (true){
			::Sleep(5000);

			auto red = static_cast<byte_type>(rand_int.generate(0, 255));
			auto green = static_cast<byte_type>(rand_int.generate(0, 255));
			auto blue = static_cast<byte_type>(rand_int.generate(0, 255));

			fw.view().background_color(grafeex::structures::color(red, green, blue));
		}
	}).detach();

	auto &mb = fw.menu();//Create menu bar and assign to window
	auto &sys = fw.system_menu();

	//Create menu items
	grafeex::menu::item i1(mb, L"First");
	grafeex::menu::item i2(mb, L"Second");
	grafeex::menu::item i3(mb, L"Last");
	grafeex::menu::item i4(grafeex::gui::object_sibling(i2, grafeex::gui::object_sibling::sibling_value_type::next), L"Inserted");
	grafeex::menu::item i5(mb, L"Drop");

	fw.events().context_menu([](grafeex::events::object &e){
		auto &drop = dynamic_cast<grafeex::messaging::context_menu_event *>(e.message_object())->menu();

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
	});
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
	drop.check(L"check", [](){});
	drop.separator();
	drop.item(L"last", [](){});

	mb.redraw();//Update menu view

	return app.run();
}
