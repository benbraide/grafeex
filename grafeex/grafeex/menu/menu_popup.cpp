#include "menu_popup.h"

grafeex::menu::popup::popup()
	: object(nullptr), owner_(nullptr){}

grafeex::menu::popup::popup(item &owner)
	: object(nullptr), owner_(nullptr){
	create(owner);
}

grafeex::menu::popup::~popup(){
	destroy();
}

bool grafeex::menu::popup::track(const hwnd_type &owner, const point_type &offset, track_option options){
	return (::TrackPopupMenuEx(value_, static_cast<uint_type>(options), offset.x(), offset.y(), owner, nullptr) != FALSE);
}

bool grafeex::menu::popup::create(){
	if (is_created() || (value_.set_native_value(::CreatePopupMenu())) == nullptr)
		return false;

	if (!init_()){
		value_.destroy();
		return false;
	}

	return true;
}

bool grafeex::menu::popup::create(item &owner){
	if (!create())
		return false;

	if (!update_owner_(&owner)){
		value_.destroy();
		return false;
	}

	return true;
}

bool grafeex::menu::popup::destroy(){
	if (value_ != nullptr){
		if (owner_ != nullptr && !update_owner_(nullptr))
			return false;

		return value_.destroy();
	}

	return (value_ == nullptr);
}

bool grafeex::menu::popup::is_created() const{
	return (value_ != nullptr);
}

grafeex::menu::popup &grafeex::menu::popup::remove_owner(){
	update_owner_(nullptr);
	return *this;
}

grafeex::menu::popup &grafeex::menu::popup::owner(item &owner){
	if (owner_ == nullptr || update_owner_(nullptr))
		update_owner_(&owner);
	return *this;
}

grafeex::menu::item *grafeex::menu::popup::owner() const{
	return owner_;
}

bool grafeex::menu::popup::update_owner_(item *owner){
	auto remove = (owner == nullptr);
	if (remove == (owner_ == nullptr))
		return false;//Nothing to update
	
	item::info_type info{
		sizeof(item::info_type),					//Size
		MIIM_SUBMENU,								//Flags
		0,											//Types
		0,											//States
		0,											//Id
		remove ? nullptr : value_.get_native_value()//Sub-menu
	};

	if (::SetMenuItemInfoW(dynamic_cast<tree *>(owner_->parent())->native_value(),
		static_cast<uint_type>(owner_->get_item_index_in_parent()), TRUE, &info) == FALSE){
		return false;
	}

	if (remove){
		parent_ = nullptr;
		owner_->sub_ = nullptr;
		owner_ = nullptr;
	}
	else{//Update parent
		parent_ = (owner_ = owner)->parent();
		owner_->sub_ = this;
	}

	return true;
}
