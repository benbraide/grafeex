#include "window_object.h"

grafeex::window::object::object(procedure_type previous_procedure)
	: previous_procedure_(previous_procedure){}

grafeex::window::object::~object(){
	destroy();
}

grafeex::window::object &grafeex::window::object::dimensions(const rect_type &value, bool inner){
	return *this;
}

grafeex::window::object::rect_type grafeex::window::object::dimensions(bool inner) const{
	return inner ? value_.get_client_rect() : value_.get_rect();
}

grafeex::window::object &grafeex::window::object::drag(const size_type &value){
	return *this;
}

grafeex::window::object::point_type grafeex::window::object::compute_alignment(alignment_type value, const size_type &delta) const{
	if (parent_ == nullptr)
		return point_type{};

	return (offset() + (compute_alignment_delta(parent_->size(), size(), value) + delta));
}

grafeex::window::object::point_type grafeex::window::object::convert_to_screen(const point_type &value) const{
	return value_.client_to_screen(value);
}

grafeex::window::object::rect_type grafeex::window::object::convert_to_screen(const rect_type &value) const{
	return value_.client_to_screen(value);
}

grafeex::window::object::point_type grafeex::window::object::convert_from_screen(const point_type &value) const{
	return value_.screen_to_client(value);
}

grafeex::window::object::rect_type grafeex::window::object::convert_from_screen(const rect_type &value) const{
	return value_.screen_to_client(value);
}

grafeex::window::object::object_type::object_type grafeex::window::object::type() const{
	return object_type::object_type::windowed;
}

bool grafeex::window::object::destroy(){
	if (value_ == nullptr)
		return true;

	value_.set_menu(nullptr);//Prevent destruction of attached menu
	return value_.destroy();
}

bool grafeex::window::object::is_created() const{
	return (value_ != nullptr);
}

grafeex::window::object::dword_type grafeex::window::object::filter_style(dword_type value, bool is_extended) const{
	auto black_listed = GRAFEEX_REMOVE_V(black_listed_styles(is_extended), white_listed_styles(is_extended));
	return GRAFEEX_REMOVE_V(value, black_listed);
}

grafeex::window::object::dword_type grafeex::window::object::white_listed_styles(bool is_extended) const{
	return (is_extended ? 0 : (CS_DBLCLKS | CS_DROPSHADOW | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_TABSTOP | WS_DISABLED | WS_VISIBLE));
}

grafeex::window::object::dword_type grafeex::window::object::black_listed_styles(bool is_extended) const{
	return (is_extended ? WS_EX_LEFTSCROLLBAR : (WS_HSCROLL | WS_VSCROLL));
}

bool grafeex::window::object::is_dialog() const{
	return false;
}

void grafeex::window::object::add_(child_type &child){
	//TODO: Implement
}

void grafeex::window::object::remove_(child_type &child){
	//TODO: Implement
}

bool grafeex::window::object::create_(const std::wstring &caption, const point_type &offset, const size_type &size, dword_type styles,
	dword_type extended_styles, const wchar_t *class_name){
	point_type computed_offset;
	if (parent_ != nullptr){
		GRAFEEX_SET(styles, WS_CHILD);//Set child flag
		if (offset.is_absolute())//Convert absolute to relative
			computed_offset = parent_->convert_from_screen(offset);
		else//Relative offset
			computed_offset = offset;
	}
	else//Relative offset
		computed_offset = offset;

	GRAFEEX_SET(styles, filter_style(persistent_styles_.basic, false));
	GRAFEEX_SET(extended_styles, filter_style(persistent_styles_.extended, true));

	size_type computed_size;
	if (size.is_inner()){//Convert inner to outer
		auto bounding_rect = hwnd_type::adjust_rect(rect_type{ computed_offset, size }, styles, extended_styles, false);
		computed_offset = bounding_rect.top_left();
		computed_size = bounding_rect.size();
	}

	return create_(create_info_type{
		nullptr,											//Params
		nullptr,											//Instance
		nullptr,											//Menu
		get_parent_handle_(),								//Parent
		computed_size.height(),								//Height
		computed_size.width(),								//Width
		computed_offset.y(),								//y-offset
		computed_offset.x(),								//x-offset
		static_cast<long>(styles),							//Styles
		(text_ = caption).c_str(),							//Window name
		class_name,											//Class name
		extended_styles										//Extended styles
	});
}

bool grafeex::window::object::create_(const create_info_type &info){
	return ((value_ = app_instance->create(*this, info)) != nullptr);
}

grafeex::window::object::hwnd_type grafeex::window::object::get_parent_handle_(){
	auto window_parent = get_window_parent_();
	return (window_parent == nullptr) ? nullptr : window_parent->value_;
}

grafeex::window::object *grafeex::window::object::get_window_parent_(){
	auto parent = parent_;
	object *window_parent = nullptr;

	while (parent != nullptr && (window_parent = dynamic_cast<object *>(parent)) == nullptr)
		parent = parent->parent();

	return window_parent;
}

void grafeex::window::object::initialize_(){}

void grafeex::window::object::uninitialize_(){
	value_ = nullptr;//Reset

	auto tree_parent = dynamic_cast<tree_type *>(parent_);
	if (tree_parent != nullptr)//Remove from parent
		tree_parent->remove(*this);
}

grafeex::window::object::app_type *&grafeex::window::object::app_instance = grafeex::window::object::app_type::instance;
