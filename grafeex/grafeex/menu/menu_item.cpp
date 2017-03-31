#include "menu_item.h"
#include "menu_object.h"

grafeex::menu::item::item(option options)
	: parent_(nullptr), options_(options), sub_(nullptr){}

grafeex::menu::item::item(gui_object_type &parent, const std::wstring &value, option options)
	: parent_(nullptr), options_(options), sub_(nullptr){
	create(parent, value);
}

grafeex::menu::item::item(const sibling_type &sibling, const std::wstring &value, option options)
	: parent_(nullptr), options_(options), sub_(nullptr){
	create(sibling, value);
}

grafeex::menu::item::~item(){
	destroy();
}

grafeex::gui::object::object_type grafeex::menu::item::type() const{
	return gui::object::object_type::menu;
}

bool grafeex::menu::item::create(gui_object_type &parent, const std::wstring &value){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(dynamic_cast<tree *>(parent_)->get_child_index_absolute(*this), value);
}

bool grafeex::menu::item::create(const sibling_type &sibling, const std::wstring &value){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(dynamic_cast<tree *>(parent_)->get_child_index_absolute(*this), value);
}

bool grafeex::menu::item::destroy(){
	if (is_created() && ::RemoveMenu(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()),
		MF_BYPOSITION) != FALSE){//Destroy
		dynamic_cast<tree_type *>(parent_)->remove(*this);
		parent_ = nullptr;
	}

	return (parent_ == nullptr);
}

bool grafeex::menu::item::is_created() const{
	return (parent_ != nullptr);
}

grafeex::menu::object *grafeex::menu::item::get_sub_menu() const{
	return sub_;
}

grafeex::menu::item &grafeex::menu::item::select(){
	return *this;
}

grafeex::menu::item &grafeex::menu::item::enable(bool value){
	if (value)
		::EnableMenuItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION | MF_ENABLED);
	else
		::EnableMenuItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION | MF_DISABLED);

	return *this;
}

grafeex::menu::item &grafeex::menu::item::gray(){
	::EnableMenuItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION | MF_GRAYED);
	return *this;
}

grafeex::menu::item &grafeex::menu::item::check(bool value){
	auto group_parent = dynamic_cast<group *>(parent_);
	if (group_parent != nullptr){//Radio selection
		if (value){//Do selection
			auto offset = static_cast<uint_type>(group_parent->get_item_index_in_parent());
			::CheckMenuRadioItem(dynamic_cast<tree *>(parent_)->native_value(), offset, offset + static_cast<uint_type>(group_parent->get_children_count()),
				static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION);
		}
	}
	else if (value)
		::CheckMenuItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION | MF_CHECKED);
	else//Unchecked
		::CheckMenuItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION | MF_UNCHECKED);

	return *this;
}

grafeex::menu::item &grafeex::menu::item::set_as_default(){
	::SetMenuDefaultItem(dynamic_cast<tree *>(parent_)->native_value(), static_cast<uint_type>(get_item_index_in_parent()), TRUE);
	return *this;
}

grafeex::menu::item::id_type grafeex::menu::item::id() const{
	return id_;
}

grafeex::menu::item::uint_type grafeex::menu::item::get_states() const{
	return (parent_ == nullptr) ? 0u : ::GetMenuState(dynamic_cast<tree *>(parent_)->native_value(),
		static_cast<uint_type>(get_item_index_in_parent()), MF_BYPOSITION);
}

grafeex::menu::item::index_type grafeex::menu::item::get_item_index_in_parent() const{
	return dynamic_cast<tree *>(parent_)->get_child_index_absolute(*this);
}

bool grafeex::menu::item::is_action() const{
	return (sub_ == nullptr);
}

bool grafeex::menu::item::is_separator() const{
	return false;
}

bool grafeex::menu::item::is_inside_group() const{
	return (dynamic_cast<group *>(parent_) != nullptr);
}

bool grafeex::menu::item::is_disabled() const{
	return GRAFEEX_IS(get_states(), MFS_DISABLED);
}

bool grafeex::menu::item::is_grayed() const{
	return GRAFEEX_IS(get_states(), MFS_GRAYED);
}

bool grafeex::menu::item::is_checked() const{
	return GRAFEEX_IS(get_states(), MFS_CHECKED);
}

bool grafeex::menu::item::is_default() const{
	return (::GetMenuDefaultItem(dynamic_cast<tree *>(parent_)->native_value(), TRUE, GMDI_USEDISABLED) == get_item_index_in_parent());
}

bool grafeex::menu::item::is_new_line() const{
	return (options_ != option::nil);
}

bool grafeex::menu::item::is_bordered() const{
	return (options_ == option::bordered_new_line);
}

void grafeex::menu::item::insert_into_parent_(gui_object_type &parent){
	reinterpret_cast<tree_type *>(&parent)->add(*this);
}

void grafeex::menu::item::insert_into_parent_(const sibling_type &sibling){
	reinterpret_cast<tree_type *>(const_cast<sibling_type &>(sibling).parent())->add(*this, sibling);
}

bool grafeex::menu::item::create_(index_type index, const std::wstring &value){
	uint_type types = 0;
	if (is_new_line()){
		if (is_bordered())
			GRAFEEX_SET(types, MFT_MENUBARBREAK);
		else
			GRAFEEX_SET(types, MFT_MENUBREAK);
	}

	//if (!events().draw_.handlers().is_empty())
		//CWIN_SET(types, MFT_OWNERDRAW);

	uint_type mask = MIIM_STRING | MIIM_ID | MIIM_DATA;
	if (types != 0u)
		GRAFEEX_SET(mask, MIIM_FTYPE);

	auto tree_parent = dynamic_cast<tree *>(parent_);
	info_type info{
		sizeof(info_type),							//Size
		mask,										//Flags
		types,										//Types
		0,											//States
		id_ = tree_parent->generate_id(),			//Id
		nullptr,									//Sub-menu
		nullptr,									//Checked bitmap
		nullptr,									//Unchecked bitmap
		reinterpret_cast<ulong_ptr_type>(this),		//Data
		const_cast<wchar_t *>(value.c_str()),		//String
		static_cast<uint_type>(value.size()),		//String size
	};

	if (::InsertMenuItemW(tree_parent->native_value(), static_cast<uint_type>(index), TRUE, &info) == FALSE){//Failed to insert item
		dynamic_cast<tree_type *>(parent_)->remove(*this);//Remove from parent
		parent_ = nullptr;
	}

	return (parent_ != nullptr);
}
