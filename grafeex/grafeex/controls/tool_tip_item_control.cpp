#include "tool_tip_control.h"

grafeex::window::controls::tool_tip_item::event_tunnel::event_tunnel(){
	event_list_[show_event_.group()] = &show_event_;
	event_list_[hide_event_.group()] = &hide_event_;
	event_list_[link_click_event_.group()] = &link_click_event_;
	event_list_[get_text_event_.group()] = &get_text_event_;
	event_list_[draw_event_.group()] = &draw_event_;
}

grafeex::window::controls::tool_tip_item::event_tunnel::~event_tunnel() = default;

grafeex::window::controls::tool_tip_item::tool_tip_item()
	: style_(*this), style_value_(style_type::nil){}

grafeex::window::controls::tool_tip_item::tool_tip_item(gui_object_type &parent, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect)
	: style_(*this), style_value_(style_type::nil){
	create(parent, owner, value, bounding_rect);
}

grafeex::window::controls::tool_tip_item::tool_tip_item(const sibling_type &sibling, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect)
	: style_(*this), style_value_(style_type::nil){
	create(sibling, owner, value, bounding_rect);
}

grafeex::window::controls::tool_tip_item::~tool_tip_item(){
	destroy();
}

grafeex::gui::object::object_type grafeex::window::controls::tool_tip_item::type() const{
	return object_type::non_windowed;
}

grafeex::window::controls::tool_tip_item::event_tunnel &grafeex::window::controls::tool_tip_item::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
}

bool grafeex::window::controls::tool_tip_item::create(gui_object_type &parent, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return create_(owner, value, bounding_rect);
}

bool grafeex::window::controls::tool_tip_item::create(const sibling_type &sibling, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return create_(owner, value, bounding_rect);
}

bool grafeex::window::controls::tool_tip_item::destroy(){
	if (!is_created())
		return true;

	uint_ptr_type id = 0;
	uint_type flags = 0;

	if (primary_info_.bounding_rect.is_empty()){
		GRAFEEX_SET(flags, TTF_IDISHWND);
		id = reinterpret_cast<uint_ptr_type>(primary_info_.owner_handle);
	}
	else//Rectangular tip
		id = reinterpret_cast<uint_ptr_type>(this);

	info_type info{
		sizeof(info_type),
		flags,
		primary_info_.owner_handle,
		id
	};

	dynamic_cast<window::object *>(parent_)->operator grafeex::window::object::hwnd_type().send_message(TTM_DELTOOLW, 0, &info);
	dynamic_cast<tree_type *>(parent_)->remove(*this);

	parent_ = nullptr;
	primary_info_ = {};

	return true;
}

bool grafeex::window::controls::tool_tip_item::is_created() const{
	return (primary_info_.owner != nullptr);
}

grafeex::gui::object::gui_object_type *grafeex::window::controls::tool_tip_item::owner() const{
	return primary_info_.owner;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::text(const std::wstring &value){
	primary_info_.value = value;
	return *this;
}

const std::wstring &grafeex::window::controls::tool_tip_item::text() const{
	return primary_info_.value;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::bounding_rect(const rect_type &value){
	if (is_created() && !primary_info_.bounding_rect.is_empty())
		return *this;

	info_type info{};
	retrieve_info_(info);

	info.rect = (primary_info_.bounding_rect = value);
	dynamic_cast<window::object *>(parent_)->operator grafeex::window::object::hwnd_type().send_message(TTM_NEWTOOLRECTW, 0, &info);

	return *this;
}

const grafeex::window::controls::tool_tip_item::rect_type &grafeex::window::controls::tool_tip_item::bounding_rect() const{
	return primary_info_.bounding_rect;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::title(const std::wstring &value){
	secondary_info_.title = value;
	return *this;
}

const std::wstring &grafeex::window::controls::tool_tip_item::title() const{
	return secondary_info_.title;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::max_width(int value){
	secondary_info_.max_width = value;
	return *this;
}

int grafeex::window::controls::tool_tip_item::max_width() const{
	return secondary_info_.max_width;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::font(font_type value){
	secondary_info_.font = value;
	return *this;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::font(const wchar_t *family, font_weigth_type weight, long size){
	font_info_type info{ sizeof(font_info_type) };

	info.lfHeight = size;
	info.lfWeight = static_cast<long>(weight);
	info.lfCharSet = DEFAULT_CHARSET;

	auto max_index = (LF_FACESIZE - 1), i = 0;
	for (; i < max_index && family[i] != L'\0'; ++i)
		info.lfFaceName[i] = family[i];

	info.lfFaceName[i] = L'\0';
	secondary_info_.font_object = (secondary_info_.font = ::CreateFontIndirectW(&info));

	return *this;
}

grafeex::window::controls::tool_tip_item::font_type grafeex::window::controls::tool_tip_item::font() const{
	return secondary_info_.font;
}

grafeex::window::controls::tool_tip_item &grafeex::window::controls::tool_tip_item::image(gdi_obj_type value){
	secondary_info_.image = value;
	return *this;
}

grafeex::window::controls::tool_tip_item::gdi_obj_type grafeex::window::controls::tool_tip_item::image() const{
	return secondary_info_.image;
}

grafeex::window::controls::tool_tip_item::dword_type grafeex::window::controls::tool_tip_item::on_draw(draw_info_type &info){
	return CDRF_DODEFAULT;
}

const std::wstring &grafeex::window::controls::tool_tip_item::on_get_text(){
	std::wstring *resolved_text = nullptr;
	if (events_ != nullptr){
		auto &events = this->events();
		if (!events.get_text_event_.empty()){
			grafeex::events::object e(*this);
			resolved_text = &(text_cache_ = events.get_text_event_.fire(e));
		}
		else//Use default value
			resolved_text = &primary_info_.value;
	}
	else//Use default value
		resolved_text = &primary_info_.value;

	auto tool_tip_parent = dynamic_cast<tool_tip *>(parent_);
	if (!is_shown_){//Apply styles -- applying before 'show'
		tool_tip_parent->view().font(font_(*tool_tip_parent));
		tool_tip_parent->value_.send_message(TTM_SETMAXTIPWIDTH, max_width_(*tool_tip_parent));

		auto image = image_(*tool_tip_parent);
		tool_tip_parent->value_.send_message(TTM_SETTITLEW, (image == nullptr) ? TTI_NONE : image, title_(*tool_tip_parent).c_str());
	}

	return *resolved_text;
}

bool grafeex::window::controls::tool_tip_item::on_show(){
	is_shown_ = true;

	grafeex::events::object e(*this);
	if (events().show_event_.fire(e, false))
		return true;

	auto tool_tip_parent = dynamic_cast<tool_tip *>(parent_);
	if (!in_place_(*tool_tip_parent))
		return false;//Show default

	rect_type bounding_rect;
	if (!primary_info_.bounding_rect.is_empty()){//Bounding rect relative to owner
		bounding_rect = primary_info_.bounding_rect;
		bounding_rect = primary_info_.owner->convert_to_screen(bounding_rect);
	}
	else//Bounding rect relative to screen
		bounding_rect = primary_info_.owner->dimensions(false);

	if (tool_tip_parent->value_.send_message(TTM_ADJUSTRECT, TRUE, bounding_rect.operator RECT *()) == FALSE)
		return false;

	auto grand_parent = parent_->parent();
	if (grand_parent != nullptr)//Make relative to tool-tip's parent
		bounding_rect = grand_parent->convert_from_screen(bounding_rect);

	parent_->move(bounding_rect.top_left());
	return true;
}

void grafeex::window::controls::tool_tip_item::on_hide(){
	grafeex::events::object e(*this);
	events().hide_event_.fire(e);
	is_shown_ = false;
}

void grafeex::window::controls::tool_tip_item::on_link_click(){
	grafeex::events::object e(*this);
	events().link_click_event_.fire(e);
}

grafeex::gui::generic_object::events_type grafeex::window::controls::tool_tip_item::get_events_(){
	return create_events_<event_tunnel>();
}

void grafeex::window::controls::tool_tip_item::update_styles_(){
	if (!is_created())
		return;

	info_type info{};
	retrieve_info_(info);

	if (GRAFEEX_IS(style_value_, style_type::center))
		GRAFEEX_SET(info.uFlags, TTF_CENTERTIP);
	else
		GRAFEEX_REMOVE(info.uFlags, TTF_CENTERTIP);

	if (GRAFEEX_IS(style_value_, style_type::rtl_reading))
		GRAFEEX_SET(info.uFlags, TTF_RTLREADING);
	else
		GRAFEEX_REMOVE(info.uFlags, TTF_RTLREADING);

	if (GRAFEEX_IS(style_value_, style_type::parse_links))
		GRAFEEX_SET(info.uFlags, TTF_PARSELINKS);
	else
		GRAFEEX_REMOVE(info.uFlags, TTF_PARSELINKS);

	dynamic_cast<window::object *>(parent_)->operator grafeex::window::object::hwnd_type().send_message(TTM_SETTOOLINFOW, 0, &info);
}

void grafeex::window::controls::tool_tip_item::retrieve_info_(info_type &info) const{
	if (!is_created()){
		info = {};
		return;
	}

	uint_ptr_type id = 0;
	uint_type flags = 0;

	if (primary_info_.bounding_rect.is_empty()){
		GRAFEEX_SET(flags, TTF_IDISHWND);
		id = reinterpret_cast<uint_ptr_type>(primary_info_.owner_handle);
	}
	else//Rectangular tip
		id = reinterpret_cast<uint_ptr_type>(this);

	info = {
		sizeof(info_type),
		flags,
		primary_info_.owner_handle,
		id
	};

	dynamic_cast<window::object *>(parent_)->operator grafeex::window::object::hwnd_type().send_message(TTM_GETTOOLINFOW, 0, &info);
}

bool grafeex::window::controls::tool_tip_item::in_place_(tool_tip &parent) const{
	return (GRAFEEX_IS(parent.style_value_, style_type::in_place) || GRAFEEX_IS(style_value_, style_type::in_place));
}

int grafeex::window::controls::tool_tip_item::max_width_(tool_tip &parent) const{
	return ((secondary_info_.max_width == -1) ? parent.secondary_info_.max_width : secondary_info_.max_width);
}

const std::wstring &grafeex::window::controls::tool_tip_item::title_(tool_tip &parent) const{
	return (secondary_info_.title.empty() ? parent.secondary_info_.title : secondary_info_.title);
}

grafeex::window::controls::tool_tip_item::gdi_obj_type grafeex::window::controls::tool_tip_item::image_(tool_tip &parent) const{
	return ((secondary_info_.image == nullptr) ? parent.secondary_info_.image : secondary_info_.image);
}

grafeex::window::controls::tool_tip_item::font_type grafeex::window::controls::tool_tip_item::font_(tool_tip &parent) const{
	return ((secondary_info_.font == nullptr) ? parent.secondary_info_.font : secondary_info_.font);
}

bool grafeex::window::controls::tool_tip_item::create_(gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect){
	auto window_parent = dynamic_cast<window::object *>(parent_);
	if (window_parent == nullptr){//Windowed parent required
		dynamic_cast<tree_type *>(parent_)->remove(*this);
		parent_ = nullptr;
		return false;
	}

	auto owner_parent = owner.parent();
	auto window_owner = dynamic_cast<window::object *>(&owner);

	while (window_owner == nullptr && owner_parent != nullptr){
		window_owner = dynamic_cast<window::object *>(owner_parent);
		owner_parent = owner_parent->parent();
	}

	if (window_owner == nullptr){//Windowed owner, or ancestor, required
		window_parent->remove(*this);
		parent_ = nullptr;
		return false;
	}

	uint_ptr_type id = 0;
	uint_type flags = TTF_SUBCLASS;

	if (bounding_rect.is_empty()){
		GRAFEEX_SET(flags, TTF_IDISHWND);
		id = reinterpret_cast<uint_ptr_type>(window_owner->operator HWND());
	}
	else//Rectangular tip
		id = reinterpret_cast<uint_ptr_type>(this);

	if (GRAFEEX_IS(style_value_, style_type::center))
		GRAFEEX_SET(flags, TTF_CENTERTIP);

	if (GRAFEEX_IS(style_value_, style_type::rtl_reading))
		GRAFEEX_SET(flags, TTF_RTLREADING);

	if (GRAFEEX_IS(style_value_, style_type::parse_links))
		GRAFEEX_SET(flags, TTF_PARSELINKS);

	info_type info{
		sizeof(info_type),
		flags,
		window_owner->operator HWND(),
		id,
		bounding_rect,
		nullptr,
		LPSTR_TEXTCALLBACKW,
		reinterpret_cast<lparam_type>(static_cast<gui_object_type *>(this))
	};

	if (window_parent->operator grafeex::window::object::hwnd_type().send_message(TTM_ADDTOOLW, 0, &info) == FALSE){
		window_parent->remove(*this);
		parent_ = nullptr;
		return false;
	}

	primary_info_.owner = &owner;
	primary_info_.owner_handle = window_owner->operator HWND();
	primary_info_.value = value;
	primary_info_.bounding_rect = bounding_rect;

	return true;
}

void grafeex::window::controls::tool_tip_item::insert_into_parent_(gui_object_type &parent){
	dynamic_cast<tree_type *>(parent_ = &parent)->add(*this);
}

void grafeex::window::controls::tool_tip_item::insert_into_parent_(const sibling_type &sibling){
	dynamic_cast<tree_type *>(parent_ = sibling.parent())->add(*this, sibling);
}
