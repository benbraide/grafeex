#include "menu_bar.h"
#include "../window/window_object.h"

grafeex::menu::bar::bar()
	: object(nullptr), owner_(nullptr){}

grafeex::menu::bar::bar(window_type &owner)
	: object(nullptr), owner_(nullptr){
	create(owner);
}

grafeex::menu::bar::~bar(){
	destroy();
}

bool grafeex::menu::bar::create(){
	if (is_created() || (value_.set_native_value(::CreateMenu())) == nullptr)
		return false;

	if (!init_()){
		value_.destroy();
		return false;
	}

	return true;
}

bool grafeex::menu::bar::create(window_type &owner){
	if (!create())
		return false;

	if (!update_owner_(&owner)){
		value_.destroy();
		return false;
	}

	return true;
}

bool grafeex::menu::bar::destroy(){
	if (value_ != nullptr){
		if (owner_ != nullptr && !update_owner_(nullptr))
			return false;

		return value_.destroy();
	}

	return (value_ == nullptr);
}

bool grafeex::menu::bar::is_created() const{
	return (value_ != nullptr);
}

grafeex::menu::bar &grafeex::menu::bar::remove_owner(){
	update_owner_(nullptr);
	return *this;
}

grafeex::menu::bar &grafeex::menu::bar::owner(window_type &owner){
	if (owner_ == nullptr || update_owner_(nullptr))
		update_owner_(&owner);
	return *this;
}

grafeex::menu::bar::window_type *grafeex::menu::bar::owner() const{
	return owner_;
}

bool grafeex::menu::bar::redraw(){
	return (owner_ == nullptr) ? false : (::DrawMenuBar(*owner_) != FALSE);
}

bool grafeex::menu::bar::update_owner_(window_type *owner){
	auto remove = (owner == nullptr);
	if (remove == (owner_ == nullptr))
		return false;//Nothing to update

	if (remove){
		if (::SetMenu(*owner_, nullptr) == FALSE)
			return false;
		owner_ = nullptr;
	}
	else{//Set
		if (::SetMenu(*owner, value_) == FALSE)
			return false;
		owner_ = owner;
	}

	return true;
}
