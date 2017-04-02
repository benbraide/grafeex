#include "menu_object.h"

grafeex::menu::object::event_tunnel::event_tunnel(){
	event_list_[select_event_.group()] = &select_event_;
}

grafeex::menu::object::event_tunnel::~event_tunnel(){}

grafeex::menu::object::object(native_type value)
	: value_(value){}

grafeex::menu::object::object(value_type value)
	: value_(value){}

grafeex::menu::object::~object(){}

grafeex::gui::object::object_type grafeex::menu::object::type() const{
	return object_type::menu;
}

grafeex::menu::object::event_tunnel &grafeex::menu::object::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
}

grafeex::menu::tree::native_type grafeex::menu::object::native_value() const{
	return value_;
}

grafeex::menu::object &grafeex::menu::object::traverse_children_absolute(traverser_type traverser){
	tree_type *tree_child;
	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree_type *>(child)) == nullptr)
			traverser(*child);//Pass to traverser
		else//Traverse tree
			tree_child->traverse_children(traverser);
	}

	return *this;
}

const grafeex::menu::object &grafeex::menu::object::traverse_children_absolute(const_traverser_type traverser) const{
	const tree_type *tree_child;
	for (auto child : children_){
		if ((tree_child = dynamic_cast<const tree_type *>(child)) == nullptr)
			traverser(*child);//Pass to traverser
		else//Traverse tree
			tree_child->traverse_children(traverser);
	}

	return *this;
}

const grafeex::menu::object::child_type *grafeex::menu::object::get_child_absolute(index_type index) const{
	return const_cast<object *>(this)->get_child_absolute(index);
}

grafeex::menu::object::child_type *grafeex::menu::object::get_child_absolute(index_type index){
	return find_child(::GetMenuItemID(value_, static_cast<uint_type>(index)));
}

grafeex::menu::object::index_type grafeex::menu::object::get_child_index_absolute(const child_type &child) const{
	tree *tree_child;
	index_type index = 0;

	for (auto item : children_){
		if (item == &child)
			return index;

		if ((tree_child = dynamic_cast<tree *>(item)) == nullptr)
			++index;
		else
			index += tree_child->get_children_count_absolute();
	}

	return static_cast<index_type>(-1);
}

grafeex::menu::object::index_type grafeex::menu::object::get_children_count_absolute() const{
	tree *tree_child;
	index_type count = 0;

	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree *>(child)) == nullptr)
			++count;
		else
			count += tree_child->get_children_count_absolute();
	}

	return count;
}

const grafeex::menu::object::child_type *grafeex::menu::object::find_child(id_type id) const{
	return const_cast<object *>(this)->find_child(id);
}

grafeex::menu::object::child_type *grafeex::menu::object::find_child(id_type id){
	tree *tree_child;
	child_type *found;

	for (auto child : children_){
		if ((tree_child = dynamic_cast<tree *>(child)) == nullptr){
			if (dynamic_cast<item *>(child)->id() == id)//Matching ids
				return child;
		}
		else if ((found = tree_child->find_child(id)) != nullptr)//Search tree
			return found;
	}

	return nullptr;
}

grafeex::menu::tree::id_type grafeex::menu::object::generate_id(){
	return random_engine_.generate(1, std::numeric_limits<id_type>::max());
}

bool grafeex::menu::object::track(const hwnd_type &owner, const point_type &offset, track_option options){
	return false;
}

bool grafeex::menu::object::set(const info_type &info){
	return value_.set(info);
}

bool grafeex::menu::object::styles(dword_type value, bool apply_to_submenus){
	return value_.styles(value, apply_to_submenus);
}

grafeex::menu::object::dword_type grafeex::menu::object::styles() const{
	return value_.styles();
}

bool grafeex::menu::object::max_height(uint_type value, bool apply_to_submenus){
	return value_.max_height(value, apply_to_submenus);
}

grafeex::menu::object::uint_type grafeex::menu::object::max_height() const{
	return value_.max_height();
}

bool grafeex::menu::object::background_brush(brush_type value, bool apply_to_submenus){
	return value_.background_brush(value, apply_to_submenus);
}

grafeex::menu::object::brush_type grafeex::menu::object::background_brush() const{
	return value_.background_brush();
}

bool grafeex::menu::object::context_help_id(dword_type value){
	return value_.context_help_id(value);
}

grafeex::menu::object::dword_type grafeex::menu::object::context_help_id() const{
	return value_.context_help_id();
}

grafeex::gui::generic_object::events_type grafeex::menu::object::get_events_(){
	return create_events_<event_tunnel>();
}

bool grafeex::menu::object::init_(){
	info_type info{
		sizeof(info_type),
		MIM_STYLE | MIM_MENUDATA
	};

	info.dwStyle = MNS_NOTIFYBYPOS;
	info.dwMenuData = reinterpret_cast<ulong_ptr_type>(this);

	return value_.set(info);
}

grafeex::menu::object::random_engine_type grafeex::menu::object::random_engine_;
