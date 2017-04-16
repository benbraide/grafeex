#include "window_style.h"
#include "window_object.h"

grafeex::window::style::style(object &object)
	: object_(&object){
	update_info_ = update_info{ false, info_type{}, info_type{} };//Reset
}

grafeex::window::style::~style() = default;

grafeex::window::style &grafeex::window::style::begin(){
	update_info_.active = true;
	return *this;
}

grafeex::window::style &grafeex::window::style::end(){
	if (update_info_.active){
		write_changes_();
		update_info_ = update_info{ false, info_type{}, info_type{} };//Reset
	}

	return *this;
}

grafeex::window::style &grafeex::window::style::cancel(){
	update_info_ = update_info{ false, info_type{} };
	return *this;
}

bool grafeex::window::style::has_begun() const{
	return update_info_.active;
}

grafeex::window::style &grafeex::window::style::apply_basic(dword_type value, bool enabled){
	return update_(value, enabled, false);
}

grafeex::window::style &grafeex::window::style::apply_extended(dword_type value, bool enabled){
	return update_(value, enabled, true);
}

grafeex::window::style &grafeex::window::style::apply_modal(){
	auto active = update_info_.active;
	if (!active)
		begin();

	update_(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_OVERLAPPEDWINDOW, false, false);
	update_(WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION, true, false);
	update_(WS_EX_DLGMODALFRAME | WS_EX_STATICEDGE, true, true);

	if (!active)
		end();

	return *this;
}

grafeex::window::style &grafeex::window::style::dbl_click(bool enabled){
	return update_(CS_DBLCLKS, enabled, false);
}

bool grafeex::window::style::dbl_click() const{
	return has_(CS_DBLCLKS, false);
}

grafeex::window::style &grafeex::window::style::drop_shadow(bool enabled){
	return update_(CS_DROPSHADOW, enabled, false);
}

bool grafeex::window::style::drop_shadow() const{
	return has_(CS_DROPSHADOW, false);
}

grafeex::window::style &grafeex::window::style::horizontal_redraw(bool enabled){
	return update_(CS_HREDRAW, enabled, false);
}

bool grafeex::window::style::horizontal_redraw() const{
	return has_(CS_HREDRAW, false);
}

grafeex::window::style &grafeex::window::style::vertical_redraw(bool enabled){
	return update_(CS_VREDRAW, enabled, false);
}

bool grafeex::window::style::vertical_redraw() const{
	return has_(CS_VREDRAW, false);
}

grafeex::window::style &grafeex::window::style::close(bool enabled){
	return update_(CS_NOCLOSE, enabled, false);
}

bool grafeex::window::style::close() const{
	return !has_(CS_NOCLOSE, false);
}

grafeex::window::style &grafeex::window::style::maximize(bool enabled){
	return update_(WS_MAXIMIZEBOX, enabled, false);
}

bool grafeex::window::style::maximize() const{
	return has_(WS_MAXIMIZEBOX, false);
}

grafeex::window::style &grafeex::window::style::minimize(bool enabled){
	return update_(WS_MINIMIZEBOX, enabled, false);
}

bool grafeex::window::style::minimize() const{
	return has_(WS_MINIMIZEBOX, false);
}

grafeex::window::style &grafeex::window::style::border(bool enabled){
	return update_(WS_BORDER, enabled, false);
}

bool grafeex::window::style::border() const{
	return has_(WS_BORDER, false);
}

grafeex::window::style &grafeex::window::style::dialog_frame(bool enabled){
	return update_(WS_DLGFRAME, enabled, false);
}

bool grafeex::window::style::dialog_frame() const{
	return has_(WS_DLGFRAME, false);
}

grafeex::window::style &grafeex::window::style::caption(bool enabled){
	return update_(WS_CAPTION, enabled, false);
}

bool grafeex::window::style::caption() const{
	return has_(WS_CAPTION, false);
}

grafeex::window::style &grafeex::window::style::system_menu(bool enabled){
	return update_(WS_SYSMENU, enabled, false);
}

bool grafeex::window::style::system_menu() const{
	return has_(WS_SYSMENU, false);
}

grafeex::window::style &grafeex::window::style::thick_frame(bool enabled){
	return update_(WS_THICKFRAME, enabled, false);
}

bool grafeex::window::style::thick_frame() const{
	return has_(WS_THICKFRAME, false);
}

grafeex::window::style &grafeex::window::style::clip_children(bool enabled){
	return update_(WS_CLIPCHILDREN, enabled, false);
}

bool grafeex::window::style::clip_children() const{
	return has_(WS_CLIPCHILDREN, false);
}

grafeex::window::style &grafeex::window::style::clip_siblings(bool enabled){
	return update_(WS_CLIPSIBLINGS, enabled, false);
}

bool grafeex::window::style::clip_siblings() const{
	return has_(WS_CLIPSIBLINGS, false);
}

grafeex::window::style &grafeex::window::style::horizontal_scroll_bar(bool enabled){
	return update_(WS_HSCROLL, enabled, false);
}

bool grafeex::window::style::horizontal_scroll_bar() const{
	return has_(WS_HSCROLL, false);
}

grafeex::window::style &grafeex::window::style::vertical_scroll_bar(bool enabled){
	return update_(WS_VSCROLL, enabled, false);
}

bool grafeex::window::style::vertical_scroll_bar() const{
	return has_(WS_VSCROLL, false);
}

grafeex::window::style &grafeex::window::style::tab_stop(bool enabled){
	return update_(WS_TABSTOP, enabled, false);
}

bool grafeex::window::style::tab_stop() const{
	return has_(WS_TABSTOP, false);
}

grafeex::window::style &grafeex::window::style::enabled(bool enabled){
	return update_(WS_DISABLED, !enabled, false);
}

bool grafeex::window::style::enabled() const{
	return !has_(WS_DISABLED, false);
}

grafeex::window::style &grafeex::window::style::visible(bool enabled){
	return update_(WS_VISIBLE, enabled, false);
}

bool grafeex::window::style::visible() const{
	return has_(WS_VISIBLE, false);
}

grafeex::window::style &grafeex::window::style::file_drop(bool enabled){
	return update_(WS_EX_ACCEPTFILES, enabled, true);
}

bool grafeex::window::style::file_drop() const{
	return has_(WS_EX_ACCEPTFILES, true);
}

grafeex::window::style &grafeex::window::style::taskbar(bool enabled){
	return update_(WS_EX_APPWINDOW, enabled, true);
}

bool grafeex::window::style::taskbar() const{
	return has_(WS_EX_APPWINDOW, true);
}

grafeex::window::style &grafeex::window::style::sunken_edge(bool enabled){
	return update_(WS_EX_CLIENTEDGE, enabled, true);
}

bool grafeex::window::style::sunken_edge() const{
	return has_(WS_EX_CLIENTEDGE, true);
}

grafeex::window::style &grafeex::window::style::context_help(bool enabled){
	return update_(WS_EX_CONTEXTHELP, enabled, true);
}

bool grafeex::window::style::context_help() const{
	return has_(WS_EX_CONTEXTHELP, true);
}

grafeex::window::style &grafeex::window::style::control_parent(bool enabled){
	return update_(WS_EX_CONTROLPARENT, enabled, true);
}

bool grafeex::window::style::control_parent() const{
	return has_(WS_EX_CONTROLPARENT, true);
}

grafeex::window::style &grafeex::window::style::dialog_modal_frame(bool enabled){
	return update_(WS_EX_DLGMODALFRAME, enabled, true);
}

bool grafeex::window::style::dialog_modal_frame() const{
	return has_(WS_EX_DLGMODALFRAME, true);
}

grafeex::window::style &grafeex::window::style::layered(bool enabled){
	return update_(WS_EX_LAYERED, enabled, true);
}

bool grafeex::window::style::layered() const{
	return has_(WS_EX_LAYERED, true);
}

grafeex::window::style &grafeex::window::style::right_alignment(bool enabled){
	return update_(WS_EX_RIGHT, enabled, true);
}

bool grafeex::window::style::right_alignment() const{
	return has_(WS_EX_RIGHT, true);
}

grafeex::window::style &grafeex::window::style::rtl_reading(bool enabled){
	return update_(WS_EX_RTLREADING, enabled, true);
}

bool grafeex::window::style::rtl_reading() const{
	return has_(WS_EX_RTLREADING, true);
}

grafeex::window::style &grafeex::window::style::rtl_layout(bool enabled){
	return update_(WS_EX_LAYOUTRTL, enabled, true);
}

bool grafeex::window::style::rtl_layout() const{
	return has_(WS_EX_LAYOUTRTL, true);
}

grafeex::window::style &grafeex::window::style::left_scroll_bar(bool enabled){
	return update_(WS_EX_LEFTSCROLLBAR, enabled, true);
}

bool grafeex::window::style::left_scroll_bar() const{
	return has_(WS_EX_LEFTSCROLLBAR, true);
}

grafeex::window::style &grafeex::window::style::mouse_activation(bool enabled){
	return update_(WS_EX_NOACTIVATE, !enabled, true);
}

bool grafeex::window::style::mouse_activation() const{
	return !has_(WS_EX_NOACTIVATE, true);
}

grafeex::window::style &grafeex::window::style::inheritable_layout(bool enabled){
	return update_(WS_EX_NOINHERITLAYOUT, !enabled, true);
}

bool grafeex::window::style::inheritable_layout() const{
	return !has_(WS_EX_NOINHERITLAYOUT, true);
}

grafeex::window::style &grafeex::window::style::parent_notify(bool enabled){
	return update_(WS_EX_NOPARENTNOTIFY, !enabled, true);
}

bool grafeex::window::style::parent_notify() const{
	return !has_(WS_EX_NOPARENTNOTIFY, true);
}

grafeex::window::style &grafeex::window::style::static_edge(bool enabled){
	return update_(WS_EX_STATICEDGE, enabled, true);
}

bool grafeex::window::style::static_edge() const{
	return has_(WS_EX_STATICEDGE, true);
}

grafeex::window::style &grafeex::window::style::window_edge(bool enabled){
	return update_(WS_EX_WINDOWEDGE, enabled, true);
}

bool grafeex::window::style::window_edge() const{
	return has_(WS_EX_WINDOWEDGE, true);
}

grafeex::window::style &grafeex::window::style::top_most(bool enabled){
	return update_(WS_EX_TOPMOST, enabled, true);
}

bool grafeex::window::style::top_most() const{
	return has_(WS_EX_TOPMOST, true);
}

grafeex::window::style &grafeex::window::style::tarnsparent(bool enabled){
	return update_(WS_EX_TRANSPARENT, enabled, true);
}

bool grafeex::window::style::has_basic(dword_type value) const{
	return has_(value, false);
}

bool grafeex::window::style::has_extended(dword_type value) const{
	return has_(value, true);
}

grafeex::window::style::dword_type grafeex::window::style::basic() const{
	return retrieve_(false);
}

grafeex::window::style::dword_type grafeex::window::style::extended() const{
	return retrieve_(true);
}

bool grafeex::window::style::tarnsparent() const{
	return has_(WS_EX_TRANSPARENT, true);
}

const grafeex::window::style::info_type &grafeex::window::style::enabled_changes() const{
	return update_info_.enabled;
}

const grafeex::window::style::info_type &grafeex::window::style::disabled_changes() const{
	return update_info_.disabled;
}

grafeex::window::style::dword_type grafeex::window::style::merge_changes_(bool extended) const{
	if (extended)
		return GRAFEEX_REMOVE_V(GRAFEEX_SET_V(retrieve_(true), update_info_.enabled.extended), update_info_.disabled.extended);
	return GRAFEEX_REMOVE_V(GRAFEEX_SET_V(retrieve_(false), update_info_.enabled.basic), update_info_.disabled.basic);
}

void grafeex::window::style::write_changes_(){
	final_write_(merge_changes_(false), false);
	final_write_(merge_changes_(true), true);
}

void grafeex::window::style::write_(dword_type value, bool extended, bool add){
	final_write_(add ? GRAFEEX_SET_V(retrieve_(extended), value) : GRAFEEX_REMOVE_V(retrieve_(extended), value), extended);
}

void grafeex::window::style::final_write_(dword_type value, bool extended){
	if (extended){
		if (object_->value_ == nullptr)
			object_->persistent_styles_.extended = object_->filter_style(value, true);
		else//Valid handle
			object_->value_.set_data(value, data_index_type::extended_styles);
	}
	else{//Basic
		if (object_->value_ == nullptr)
			object_->persistent_styles_.basic = object_->filter_style(value, false);
		else//Valid handle
			object_->value_.set_data(value, data_index_type::styles);
	}
}

grafeex::window::style &grafeex::window::style::update_(dword_type value, bool enabled, bool extended){
	return enabled ? enable_(value, extended) : disable_(value, extended);
}

grafeex::window::style &grafeex::window::style::enable_(dword_type value, bool extended){
	if (update_info_.active){
		if (extended){
			GRAFEEX_SET(update_info_.enabled.extended, value);
			GRAFEEX_REMOVE(update_info_.disabled.extended, value);
		}
		else{//Basic
			GRAFEEX_SET(update_info_.enabled.basic, value);
			GRAFEEX_REMOVE(update_info_.disabled.basic, value);
		}
	}
	else//Write
		write_(value, extended, true);

	return *this;
}

grafeex::window::style &grafeex::window::style::disable_(dword_type value, bool extended){
	if (update_info_.active){
		if (extended){
			GRAFEEX_SET(update_info_.disabled.extended, value);
			GRAFEEX_REMOVE(update_info_.enabled.extended, value);
		}
		else{//Basic
			GRAFEEX_SET(update_info_.disabled.basic, value);
			GRAFEEX_REMOVE(update_info_.enabled.basic, value);
		}
	}
	else//Write
		write_(value, extended, false);

	return *this;
}

grafeex::window::style::dword_type grafeex::window::style::retrieve_(bool extended) const{
	if (extended){
		if (object_->value_ == nullptr)
			return object_->persistent_styles_.extended;

		return object_->value_.get_data<dword_type>(data_index_type::extended_styles);
	}

	if (object_->value_ == nullptr)
		return object_->persistent_styles_.basic;

	return object_->value_.get_data<dword_type>(data_index_type::styles);
}

bool grafeex::window::style::has_(dword_type value, bool extended) const{
	if (update_info_.active)//Merge changes
		return GRAFEEX_IS(merge_changes_(extended), value);
	return GRAFEEX_IS(retrieve_(extended), value);
}
