#include "shared_menu.h"
#include "menu_separator.h"
#include "../window/window_object.h"

grafeex::menu::shared::shared(const hwnd_type &target, option options)
	: object((options == option::system) ? ::GetSystemMenu(target, FALSE) : ::GetMenu(target)){
	if (options == option::system && value_ != nullptr)
		populate_items_();
}

grafeex::menu::shared::shared(window_type &target, option options)
	: object((options == option::system) ? ::GetSystemMenu(target, FALSE) : ::GetMenu(target)){
	if (options == option::system && value_ != nullptr)
		populate_items_();
}

grafeex::menu::shared::~shared() = default;

void grafeex::menu::shared::remove_(object::child_type &child){
	object::remove_(child);
	for (auto iter = list_.begin(); iter != list_.end(); ++iter){
		if (iter->get() == &child){
			list_.erase(iter);
			break;
		}
	}
}

void grafeex::menu::shared::populate_items_(){
	item_type item;
	auto count = value_.count();

	for (auto i = 0; i < count; ++i){
		item::info_type info{ sizeof(item::info_type), MIIM_FTYPE | MIIM_ID };
		if (::GetMenuItemInfoW(value_, i, TRUE, &info) != FALSE){
			if (GRAFEEX_IS(info.fType, MFT_SEPARATOR))
				item = std::make_shared<separator>();
			else//Item
				item = std::make_shared<menu::item>();

			item->parent_ = this;
			if (info.wID != 0u)
				item->id_ = static_cast<id_type>(info.wID);

			info.fMask = MIIM_DATA;
			info.dwItemData = reinterpret_cast<menu::item::ulong_ptr_type>(item.get());
			::SetMenuItemInfoW(value_, i, TRUE, &info);

			add(*item);
			list_.push_back(item);
		}
	}
}
