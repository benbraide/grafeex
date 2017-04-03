#include "shared_menu.h"
#include "menu_separator.h"

grafeex::menu::shared::shared(const hwnd_type &target, option options)
	: object((options == option::system) ? ::GetSystemMenu(target, FALSE) : ::GetMenu(target)){
	if (options == option::system && value_ != nullptr)
		populate_items_();
}

grafeex::menu::shared::~shared(){}

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
