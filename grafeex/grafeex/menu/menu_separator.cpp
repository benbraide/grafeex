#include "menu_separator.h"

grafeex::menu::separator::separator(){}

grafeex::menu::separator::separator(gui_object_type &parent){
	create(parent);
}

grafeex::menu::separator::separator(const sibling_type &sibling){
	create(sibling);
}

grafeex::menu::separator::~separator(){
	destroy();
}

grafeex::menu::item &grafeex::menu::separator::select(){
	return *this;
}

grafeex::menu::item &grafeex::menu::separator::enable(bool value){
	return *this;
}

grafeex::menu::item &grafeex::menu::separator::gray(){
	return *this;
}

grafeex::menu::item &grafeex::menu::separator::check(bool value){
	return *this;
}

grafeex::menu::item &grafeex::menu::separator::set_as_default(){
	return *this;
}

bool grafeex::menu::separator::is_action() const{
	return false;
}

bool grafeex::menu::separator::is_separator() const{
	return true;
}

bool grafeex::menu::separator::create(gui_object_type &parent){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(dynamic_cast<tree *>(parent_)->get_child_index_absolute(*this));
}

bool grafeex::menu::separator::create(const sibling_type &sibling){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(dynamic_cast<tree *>(parent_)->get_child_index_absolute(*this));
}

bool grafeex::menu::separator::create_(index_type index, const std::wstring &value){
	return create_(index);
}

bool grafeex::menu::separator::create_(index_type index){
	uint_type types = MFT_SEPARATOR;
	if (is_new_line()){
		if (is_bordered())
			GRAFEEX_SET(types, MFT_MENUBARBREAK);
		else
			GRAFEEX_SET(types, MFT_MENUBREAK);
	}

	if (is_owner_drawn())//Owner drawn item
		GRAFEEX_SET(types, MFT_OWNERDRAW);

	auto tree_parent = dynamic_cast<tree *>(parent_);
	uint_type mask = MIIM_FTYPE | MIIM_ID | MIIM_DATA;

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
	};

	if (::InsertMenuItemW(tree_parent->native_value(), static_cast<uint_type>(index), TRUE, &info) == FALSE)//Failed to insert item
		dynamic_cast<tree_type *>(parent_)->remove(*this);//Remove from parent

	return (parent_ != nullptr);
}
