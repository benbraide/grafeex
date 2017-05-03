#include "tool_tip_control.h"

grafeex::window::controls::tool_tip::event_tunnel::event_tunnel(){
	event_list_[show_event_.group()] = &show_event_;
	event_list_[hide_event_.group()] = &hide_event_;
	event_list_[link_click_event_.group()] = &link_click_event_;
	event_list_[get_text_event_.group()] = &get_text_event_;
	event_list_[draw_event_.group()] = &draw_event_;
}

grafeex::window::controls::tool_tip::event_tunnel::~event_tunnel() = default;

grafeex::window::controls::tool_tip::tool_tip(bool create)
	: object(control_type::tool_tip, nullptr, &notify_forwarder_list_), style_value_(item_style_type::nil){
	reset_persistent_styles_();
	if (create)
		this->create();
}

grafeex::window::controls::tool_tip::tool_tip(gui_object_type &parent)
	: object(control_type::tool_tip, nullptr, &notify_forwarder_list_), style_value_(item_style_type::nil){
	reset_persistent_styles_();
	create(parent);
}

grafeex::window::controls::tool_tip::tool_tip(const sibling_type &sibling)
	: object(control_type::tool_tip, nullptr, &notify_forwarder_list_), style_value_(item_style_type::nil){
	reset_persistent_styles_();
	create(sibling);
}

grafeex::window::controls::tool_tip::~tool_tip(){
	destroy();
}

grafeex::window::controls::object::dword_type grafeex::window::controls::tool_tip::white_listed_styles(bool is_extended) const{
	return (base_type::white_listed_styles(is_extended) | (is_extended ? 0ul : general_styles));
}

grafeex::window::controls::tool_tip::style_type &grafeex::window::controls::tool_tip::style(){
	return *dynamic_cast<style_type *>(get_style_().get());
}

grafeex::window::controls::tool_tip::event_tunnel &grafeex::window::controls::tool_tip::events(){
	return *dynamic_cast<event_tunnel *>(get_events_().get());
}

bool grafeex::window::controls::tool_tip::create(){
	if (is_created())
		return false;

	return object::create_(L"", point_type{}, size_type{});
}

bool grafeex::window::controls::tool_tip::create(gui_object_type &parent){
	if (is_created())
		return false;

	insert_into_parent_(parent);
	return object::create_(L"", point_type{}, size_type{});
}

bool grafeex::window::controls::tool_tip::create(const sibling_type &sibling){
	if (is_created())
		return false;

	insert_into_parent_(sibling);
	return object::create_(L"", point_type{}, size_type{});
}

grafeex::window::controls::tool_tip_item *grafeex::window::controls::tool_tip::current_item() const{
	item_info_type info{
		sizeof(item_info_type)
	};

	if (value_.send_message(TTM_GETCURRENTTOOLW, 0, &info) == FALSE)
		return nullptr;

	return reinterpret_cast<tool_tip_item *>(info.lParam);
}

grafeex::window::controls::tool_tip &grafeex::window::controls::tool_tip::title(const std::wstring &value){
	secondary_info_.title = value;
	return *this;
}

const std::wstring &grafeex::window::controls::tool_tip::title() const{
	return secondary_info_.title;
}

grafeex::window::controls::tool_tip &grafeex::window::controls::tool_tip::max_width(int value){
	secondary_info_.max_width = value;
	return *this;
}

int grafeex::window::controls::tool_tip::max_width() const{
	return secondary_info_.max_width;
}

grafeex::window::controls::tool_tip &grafeex::window::controls::tool_tip::font(font_type value){
	secondary_info_.font = value;
	return *this;
}

grafeex::window::controls::tool_tip &grafeex::window::controls::tool_tip::font(const wchar_t *family, font_weigth_type weight, long size){
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

grafeex::window::controls::tool_tip::font_type grafeex::window::controls::tool_tip::font() const{
	return secondary_info_.font;
}

grafeex::window::controls::tool_tip &grafeex::window::controls::tool_tip::image(gdi_obj_type value){
	secondary_info_.image = value;
	return *this;
}

grafeex::window::controls::tool_tip::gdi_obj_type grafeex::window::controls::tool_tip::image() const{
	return secondary_info_.image;
}

grafeex::window::controls::tool_tip::dword_type grafeex::window::controls::tool_tip::on_control_draw(messaging::custom_draw_event &e){
	auto target = current_item();
	if (target != nullptr)
		return target->on_draw(e.draw_info());

	grafeex::events::object ev(*this, e);
	return events().draw_event_.fire(ev, CDRF_DODEFAULT);
}

const std::wstring &grafeex::window::controls::tool_tip::on_tool_tip_get_text(messaging::tool_tip_get_text_event &e){
	auto target = e.item();
	if (target != nullptr){
		auto &value = dynamic_cast<tool_tip_item *>(target)->on_get_text();
		if (!value.empty() || events_ == nullptr || events().get_text_event_.empty())
			return value;
	}

	if (events_ == nullptr)//Event object not initialized
		return text_;

	auto &events = this->events();
	if (events.get_text_event_.empty())//No handler
		return text_;

	grafeex::events::object ev(*this, e);
	return (text_cache_ = events.get_text_event_.fire(ev));
}

void grafeex::window::controls::tool_tip::on_tool_tip_show(messaging::object &e){
	auto target = current_item();
	if (target != nullptr && dynamic_cast<tool_tip_item *>(target)->on_show()){
		e << true;
		return;//Show handled
	}

	grafeex::events::object ev(*this);
	e << events().show_event_.fire(ev, false);
}

void grafeex::window::controls::tool_tip::on_tool_tip_hide(messaging::object &e){
	auto target = current_item();
	if (target != nullptr)
		dynamic_cast<tool_tip_item *>(target)->on_hide();

	grafeex::events::object ev(*this);
	events().hide_event_.fire(ev);
}

void grafeex::window::controls::tool_tip::on_tool_tip_link_click(messaging::object &e){
	auto target = current_item();
	if (target != nullptr)
		dynamic_cast<tool_tip_item *>(target)->on_link_click();

	grafeex::events::object ev(*this);
	events().link_click_event_.fire(ev);
}

void grafeex::window::controls::tool_tip::reset_persistent_styles_(){
	object::reset_persistent_styles_();
	GRAFEEX_SET(persistent_styles_.basic, TTS_USEVISUALSTYLE);
}

grafeex::window::object::style_ptr_type grafeex::window::controls::tool_tip::get_style_(){
	return create_style_<style_type>();
}

grafeex::gui::generic_object::events_type grafeex::window::controls::tool_tip::get_events_(){
	return create_events_<event_tunnel>();
}
