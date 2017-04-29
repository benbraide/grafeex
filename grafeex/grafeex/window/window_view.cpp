#include "window_view.h"
#include "window_object.h"

grafeex::window::view::view(object &object)
	: object_(&object){}

grafeex::window::view::~view() = default;

grafeex::window::view &grafeex::window::view::enable(){
	object_->value_.enable(true);
	return *this;
}

grafeex::window::view &grafeex::window::view::disable(){
	object_->value_.enable(false);
	return *this;
}

bool grafeex::window::view::enabled() const{
	return object_->value_.is_enabled();
}

grafeex::window::view &grafeex::window::view::focus(){
	focus_();
	if (!object_->is_dialog()){
		auto dialog_parent = object_->get_dialog_parent_();
		if (dialog_parent != nullptr)
			application::object::instance->active_dialog_ = dialog_parent;
	}
	else//Object is dialog
		application::object::instance->active_dialog_ = object_;

	return *this;
}

grafeex::window::view &grafeex::window::view::blur(){
	auto tree_parent = dynamic_cast<gui::object_tree *>(object_->parent());
	if (tree_parent != nullptr && tree_parent->focused_child_ == object_)
		tree_parent->focused_child_ = nullptr;

	if (application::object::instance->active_dialog_ != nullptr && application::object::instance->active_dialog_ != object_){
		if (application::object::instance->active_dialog_ == object_->get_dialog_parent_())
			application::object::instance->active_dialog_ = nullptr;
	}
	else if (application::object::instance->active_dialog_ != nullptr)//Object is dialog
		application::object::instance->active_dialog_ = nullptr;

	return *this;
}

bool grafeex::window::view::focused() const{
	auto tree_parent = dynamic_cast<gui::object_tree *>(object_->parent());
	if (tree_parent == nullptr)//No parent
		return (object_->value_ == ::GetForegroundWindow());

	if (tree_parent->focused_child_ != object_)
		return false;

	auto window_parent = dynamic_cast<object *>(tree_parent);
	if (window_parent == nullptr)
		return window_parent->view().focused();

	return false;
}

grafeex::window::view &grafeex::window::view::show(show_mode mode){
	object_->value_.show(mode);
	return *this;
}

grafeex::window::view &grafeex::window::view::hide(){
	object_->value_.show(show_mode::hide);
	return *this;
}

bool grafeex::window::view::visisble() const{
	return object_->value_.is_visible();
}

grafeex::window::view &grafeex::window::view::maximize(){
	object_->value_.show(show_mode::maximize);
	return *this;
}

bool grafeex::window::view::maximized() const{
	return object_->value_.is_maximized();
}

grafeex::window::view &grafeex::window::view::minimize(){
	object_->value_.show(show_mode::minimize);
	return *this;
}

bool grafeex::window::view::minimized() const{
	return object_->value_.is_minimized();
}

grafeex::window::view &grafeex::window::view::restore(){
	object_->value_.show(show_mode::restore);
	return *this;
}

grafeex::window::view &grafeex::window::view::caption(const std::wstring &value){
	object_->value_.set_text(value);
	return *this;
}

grafeex::window::view &grafeex::window::view::clear_background_color(){
	if (background_color_ != nullptr){
		background_color_ = nullptr;
		if (object_->renderer_ != nullptr)
			object_->renderer_->get().set_background_color(color_type());

		if (object_->hdc_renderer_ != nullptr)
			object_->hdc_renderer_->get().set_background_color(color_type());
	}

	return *this;
}

const std::wstring &grafeex::window::view::caption() const{
	return object_->text_;
}

grafeex::window::view &grafeex::window::view::background_color(const color_type &value, bool repaint){
	return background_color(::D2D1::ColorF(value.relative_red(), value.relative_green(), value.relative_blue(), value.relative_alpha()), repaint);
}

grafeex::window::view &grafeex::window::view::background_color(const d2d_color_type &value, bool repaint){
	background_color_ = std::make_shared<d2d_color_type>(value);
	if (object_->value_ != nullptr){
		if (object_->renderer_ != nullptr)
			object_->renderer_->get().set_background_color(value);

		if (object_->hdc_renderer_ != nullptr)
			object_->hdc_renderer_->get().set_background_color(value);

		if (repaint)//Repaint client area
			object_->value_.invalidate();
	}

	return *this;
}

grafeex::window::view::d2d_color_type grafeex::window::view::background_color() const{
	return (background_color_ == nullptr) ? d2d_color_type{} : *background_color_;
}

bool grafeex::window::view::has_background_color() const{
	return (background_color_ != nullptr);
}

void grafeex::window::view::focus_(){
	focus_only_();
	if (object_->focused_child_ == nullptr)
		return;

	auto window_object = dynamic_cast<object *>(object_->focused_child_);
	if (window_object == nullptr){//Non-window object
		//TODO: Set focus
	}
	else//Window object
		window_object->view().focus_();
}

void grafeex::window::view::focus_only_(){
	auto tree_parent = dynamic_cast<gui::object_tree *>(object_->parent());
	if (tree_parent != nullptr)
		tree_parent->focused_child_ = object_;

	auto window_parent = dynamic_cast<object *>(tree_parent);
	if (window_parent == nullptr){//Non-window parent
		//TODO: Set focus
	}
	else//Window parent
		window_parent->view().focus_only_();
}
