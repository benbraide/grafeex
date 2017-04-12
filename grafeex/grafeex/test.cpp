#include "common/random_bool.h"
#include "common/hook.h"
#include "window/frame_window.h"
#include "window/top_level_window.h"
#include "window/modal_dialog_window.h"
#include "menu/menu_bar.h"
#include "menu/menu_check_item.h"
#include "collections/menu_collection.h"

int WINAPI wWinMain(::HINSTANCE app_instance, ::HINSTANCE, ::LPWSTR cmd_line, int show_type){
	typedef grafeex::window::object::d2d_point_type d2d_point_type;
	typedef grafeex::window::object::d2d_size_type d2d_size_type;

	typedef grafeex::structures::float_size float_size_type;
	typedef grafeex::structures::rect_origin_type alignment_type;

	grafeex::application::object app;

	grafeex::window::top_level fw(L"Test Window", d2d_point_type{ 10.0f, 10.0f }, d2d_size_type{ 500.0f, 400.0f });
	fw.view().show();

	grafeex::window::dialog_frame dfm(fw, L"Modal Dialog", grafeex::structures::point{ 10 }, { 300, 200 });
	dfm.attributes().fill_parent(float_size_type{ 0.5f, 1.0f });
	dfm.attributes().align(true, alignment_type::top | alignment_type::right);
	dfm.view().show();
	//dfm.do_modal(fw);

	auto count = 0;
	grafeex::common::random_bool rand;
	fw.events().close([&rand, &count](){
		std::string s = "Window closing...";
		return (rand.generate() || ++count >= 4);
	});

	grafeex::common::random_int rand_int;
	std::thread([&fw, &rand_int]{
		typedef ::BYTE byte_type;
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
