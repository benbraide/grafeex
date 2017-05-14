#include "window_object.h"
#include "modal_dialog_window.h"

#include "../messaging/message_event_forwarder.h"
#include "../collections/tab_collection.h"

grafeex::window::object::event_tunnel::event_tunnel(){
	event_list_[menu_select_event_.group()] = &menu_select_event_;
	event_list_[menu_highlight_event_.group()] = &menu_highlight_event_;
	event_list_[menu_init_event_.group()] = &menu_init_event_;
	event_list_[context_menu_event_.group()] = &context_menu_event_;

	event_list_[create_event_.group()] = &create_event_;
	event_list_[destroy_event_.group()] = &destroy_event_;
	event_list_[close_event_.group()] = &close_event_;

	event_list_[size_event_.group()] = &size_event_;
	event_list_[maximize_event_.group()] = &maximize_event_;
	event_list_[minimize_event_.group()] = &minimize_event_;

	event_list_[show_event_.group()] = &show_event_;
	event_list_[hide_event_.group()] = &hide_event_;

	event_list_[erase_background_event_.group()] = &erase_background_event_;
	event_list_[paint_event_.group()] = &paint_event_;

	event_list_[timer_event_.group()] = &timer_event_;
}

grafeex::window::object::event_tunnel::~event_tunnel() = default;

grafeex::window::object::object(procedure_type previous_procedure)
	: previous_procedure_(previous_procedure), objects_(*this){
	relative_info_ = relative_info{ false };
	mouse_state_.object_info_.general_event_owner = this;
	mouse_state_.object_info_.object_owner = this;
}

grafeex::window::object::~object(){
	destroy();
}

grafeex::window::object &grafeex::window::object::dimensions(const rect_type &value, bool inner){
	typedef structures::enumerations::position_type position_type;
	if (inner){//Client rect
		auto adjusted_value = value_.adjust_rect(value);
		value_.position(adjusted_value.top_left(), adjusted_value.size(), position_type::no_z_order, nullptr);
	}
	else//Window rect
		value_.position(value.top_left(), value.size(), position_type::no_z_order, nullptr);

	return *this;
}

grafeex::window::object::rect_type grafeex::window::object::dimensions(bool inner) const{
	return inner ? value_.get_client_rect() : value_.get_rect();
}

grafeex::window::object &grafeex::window::object::drag(const size_type &value){
	return *this;
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

grafeex::window::object::event_tunnel &grafeex::window::object::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
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

grafeex::window::object::operator hwnd_type() const{
	return value_;
}

grafeex::window::object::operator native_value_type() const{
	return value_;
}

grafeex::window::object::d2d_float_point_type grafeex::window::object::convert_to_dip(const point_type &value){
	auto renderer_size = this->renderer()->GetSize();
	auto size = dimensions(true).size();
	if (size.width() <= 0 || size.height() <= 0)
		return d2d_float_point_type{ static_cast<float>(value.x()), static_cast<float>(value.y()) };

	d2d_float_size_type ratio{ (renderer_size.width / size.width()), (renderer_size.height / size.height()) };
	return d2d_float_point_type{ value.x() * ratio.width, value.y() * ratio.height };
}

grafeex::window::object::d2d_float_rect_type grafeex::window::object::convert_to_dip(const rect_type &value){
	auto renderer_size = this->renderer()->GetSize();
	auto size = dimensions(true).size();
	if (size.width() <= 0 || size.height() <= 0){
		return d2d_float_rect_type{ static_cast<float>(value.left()), static_cast<float>(value.top()),
			static_cast<float>(value.right()), static_cast<float>(value.bottom()) };
	}

	d2d_float_size_type ratio{ (renderer_size.width / size.width()), (renderer_size.height / size.height()) };
	return d2d_float_rect_type{ value.left() * ratio.width, value.top() * ratio.height,
		value.right() * ratio.width, value.bottom() * ratio.height };
}

grafeex::window::object::point_type grafeex::window::object::convert_from_dip(const d2d_float_point_type &value){
	typedef point_type::field_type field_type;

	auto renderer_size = this->renderer()->GetSize();
	if (renderer_size.width <= 0 || renderer_size.height <= 0)
		return point_type{ static_cast<field_type>(value.x), static_cast<field_type>(value.y) };

	auto size = dimensions(true).size();
	d2d_float_size_type ratio{ (size.width() / renderer_size.width), (size.height() / renderer_size.height) };

	return point_type{ static_cast<field_type>(value.x * ratio.width), static_cast<field_type>(value.y * ratio.height) };
}

grafeex::window::object::rect_type grafeex::window::object::convert_from_dip(const d2d_float_rect_type &value){
	typedef point_type::field_type field_type;

	auto renderer_size = this->renderer()->GetSize();
	if (renderer_size.width <= 0 || renderer_size.height <= 0){
		return rect_type{ static_cast<field_type>(value.left), static_cast<field_type>(value.top),
			static_cast<field_type>(value.right), static_cast<field_type>(value.bottom) };
	}

	auto size = dimensions(true).size();
	d2d_float_size_type ratio{ (size.width() / renderer_size.width), (size.height() / renderer_size.height) };

	return rect_type{ static_cast<field_type>(value.left * ratio.width), static_cast<field_type>(value.top * ratio.height),
		static_cast<field_type>(value.right * ratio.width), static_cast<field_type>(value.bottom * ratio.height) };
}

bool grafeex::window::object::is_dialog() const{
	return false;
}

bool grafeex::window::object::is_top_level() const{
	return false;
}

bool grafeex::window::object::is_ancestor(const object_type &target) const{
	auto parent = this->parent();
	while (parent != nullptr && parent != &target)
		parent = parent->parent();

	return (parent != nullptr);
}

bool grafeex::window::object::has_menu() const{
	return (menu_ != nullptr);
}

grafeex::window::object::menu_collection_type &grafeex::window::object::menu(){
	if (menu_ == nullptr)
		menu_ = std::make_shared<collections::menu_bar>(*this);
	return *menu_;
}

grafeex::window::object::shared_menu_collection_type &grafeex::window::object::system_menu(){
	if (system_menu_ == nullptr)
		system_menu_ = std::make_shared<collections::shared_menu>(*this, menu::shared::option::system);
	return *system_menu_;
}

grafeex::window::object::view_type &grafeex::window::object::view(){
	return *get_view_();
}

grafeex::window::object::style_type &grafeex::window::object::style(){
	return *get_style_();
}

grafeex::window::object::hwnd_render_type &grafeex::window::object::renderer(){
	return render_manager().get();
}

grafeex::window::object::render_manager_type &grafeex::window::object::render_manager(){
	if (renderer_ == nullptr){
		renderer_ = std::make_shared<render_manager_type>(app_instance->d2d_factory, true, value_, relative_info_.active);
		if (view_ != nullptr && view_->has_background_color())
			renderer_->get().set_background_color(view_->background_color());
	}

	return *renderer_;
}

grafeex::window::object::hdc_render_manager_type &grafeex::window::object::hdc_render_manager(){
	if (hdc_renderer_ == nullptr){
		hdc_renderer_ = std::make_shared<hdc_render_manager_type>(app_instance->d2d_factory, true);
		if (view_ != nullptr && view_->has_background_color())
			hdc_renderer_->get().set_background_color(view_->background_color());
	}

	return *hdc_renderer_;
}

grafeex::window::object::gui_object_collection_type &grafeex::window::object::objects(){
	return objects_;
}

grafeex::window::object::d2d_point_type grafeex::window::object::point_to_dip(const point_type &value){
	return d2d_point_type{ app_type::pixel_to_dip_x(value.x()), app_type::pixel_to_dip_y(value.y()) };
}

grafeex::window::object::d2d_size_type grafeex::window::object::size_to_dip(const size_type &value){
	return d2d_size_type{ app_type::pixel_to_dip_x(value.width()), app_type::pixel_to_dip_y(value.height()) };
}

grafeex::window::object::point_type grafeex::window::object::point_to_pixel(const d2d_point_type &value){
	return point_type{ app_type::dip_to_pixel_x(value.x), app_type::dip_to_pixel_y(value.y) };
}

grafeex::window::object::size_type grafeex::window::object::size_to_pixel(const d2d_size_type &value){
	return size_type{ app_type::dip_to_pixel_x(value.width), app_type::dip_to_pixel_y(value.height) };
}

void grafeex::window::object::on_recreate_drawing_resources(bool is_device){
	if (is_device)//Reset objects
		hdc_renderer_ = nullptr;
	else//Window
		renderer_ = nullptr;
}

grafeex::gui::generic_object::events_type grafeex::window::object::get_events_(){
	return create_events_<event_tunnel>();
}

void grafeex::window::object::sized_(){
	tree_type::sized_();
	if (renderer_ != nullptr){
		auto size = this->size(true);
		renderer_->get()->Resize(::D2D1::SizeU(size.width(), size.height()));
	}
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
		if (dynamic_cast<modal_dialog *>(this) == nullptr)
			GRAFEEX_SET(styles, WS_CHILD);//Set child flag

		if (dynamic_cast<dialog *>(this) != nullptr){
			auto window_parent = dynamic_cast<object *>(parent_);
			if (window_parent != nullptr && window_parent->is_dialog())
				GRAFEEX_SET(extended_styles, WS_EX_CONTROLPARENT);
		}

		if (offset.is_absolute())//Convert absolute to relative
			computed_offset = parent_->convert_from_screen(offset);
		else//Relative offset
			computed_offset = offset;
	}
	else//Relative offset
		computed_offset = offset;

	GRAFEEX_SET(styles, persistent_styles_.basic);
	GRAFEEX_SET(extended_styles, persistent_styles_.extended);

	size_type computed_size;
	if (size.is_inner()){//Convert inner to outer
		auto bounding_rect = hwnd_type::adjust_rect(rect_type{ computed_offset, size }, styles, extended_styles, false);
		computed_offset = bounding_rect.top_left();
		computed_size = bounding_rect.size();
	}
	else//Outer size
		computed_size = size;

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

bool grafeex::window::object::create_(const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size,
	dword_type styles, dword_type extended_styles, const wchar_t *class_name){
	relative_info_ = relative_info{ true, offset, size };
	return create_(caption, point_to_pixel(offset), size_to_pixel(size), styles, extended_styles, class_name);
}

bool grafeex::window::object::create_(const create_info_type &info){
	if ((value_ = app_instance->create(*this, info)) == nullptr){//Failed to create window
		system_menu_ = nullptr;
		if (parent_ != nullptr){//Remove from parent
			dynamic_cast<tree_type *>(parent_)->remove(*this);
			parent_ = nullptr;
		}

		return false;
	}
	else//Success
		created_();

	return true;
}

void grafeex::window::object::created_(){
	mouse_state_.object_info_.parent = dynamic_cast<input_event_handler *>(parent_);
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

	return (parent == nullptr) ? nullptr : window_parent;
}

grafeex::window::object *grafeex::window::object::get_dialog_parent_(){
	auto parent = parent_;
	object *dialog_parent = nullptr;

	while (parent != nullptr && ((dialog_parent = dynamic_cast<object *>(parent)) == nullptr || !dialog_parent->is_dialog()))
		parent = parent->parent();

	return (parent == nullptr) ? nullptr : dialog_parent;
}

void grafeex::window::object::initialize_(){}

void grafeex::window::object::uninitialize_(){}

void grafeex::window::object::reset_persistent_styles_(){
	persistent_styles_ = { WS_CLIPCHILDREN | WS_CLIPSIBLINGS };
}

grafeex::window::object::view_ptr_type grafeex::window::object::get_view_(){
	return create_view_<view_type>();
}

grafeex::window::object::style_ptr_type grafeex::window::object::get_style_(){
	return create_style_<style_type>();
}

grafeex::window::object::app_type *&grafeex::window::object::app_instance = grafeex::window::object::app_type::instance;
