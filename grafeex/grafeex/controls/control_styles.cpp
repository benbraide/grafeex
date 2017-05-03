#include "control_styles.h"
#include "tool_tip_control.h"

grafeex::window::controls::button_style::button_style(object_type &object)
	: base_type(object){}

grafeex::window::controls::button_style::~button_style() = default;

grafeex::window::controls::button_style &grafeex::window::controls::button_style::flat(bool enabled){
	update_(BS_FLAT, enabled, false);
	return *this;
}

bool grafeex::window::controls::button_style::flat() const{
	return has_(BS_FLAT, false);
}

grafeex::window::controls::button_style &grafeex::window::controls::button_style::multi_line(bool enabled){
	update_(BS_MULTILINE, enabled, false);
	return *this;
}

bool grafeex::window::controls::button_style::multi_line() const{
	return has_(BS_MULTILINE, false);
}

grafeex::window::controls::button_style &grafeex::window::controls::button_style::text_alignment(alignment_type value){
	auto active = update_info_.active;
	if (!active)
		begin();

	update_(BS_CENTER | BS_VCENTER, false, false);
	update_(static_cast<dword_type>(value), true, false);

	if (!active)
		end();

	return *this;
}

grafeex::window::controls::button_style::alignment_type grafeex::window::controls::button_style::text_alignment() const{
	auto styles = basic();
	auto value = alignment_type::nil;

	if (GRAFEEX_IS(styles, BS_CENTER))
		GRAFEEX_SET(value, alignment_type::center);
	else if (GRAFEEX_IS(styles, BS_RIGHT))
		GRAFEEX_SET(value, alignment_type::right);
	else
		GRAFEEX_SET(value, alignment_type::left);

	if (GRAFEEX_IS(styles, BS_VCENTER))
		GRAFEEX_SET(value, alignment_type::vcenter);
	else if (GRAFEEX_IS(styles, BS_BOTTOM))
		GRAFEEX_SET(value, alignment_type::bottom);
	else
		GRAFEEX_SET(value, alignment_type::top);

	return value;
}

grafeex::window::controls::tool_tip_item_style::tool_tip_item_style(object_type &object)
	: object_(&object){}

grafeex::window::controls::tool_tip_item_style::~tool_tip_item_style() = default;

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::add(type value){
	auto old_value = object_->style_value_;

	GRAFEEX_SET(object_->style_value_, value);
	if (object_->style_value_ != old_value)
		object_->update_styles_();

	return *this;
}

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::remove(type value){
	auto old_value = object_->style_value_;

	GRAFEEX_REMOVE(object_->style_value_, value);
	if (object_->style_value_ != old_value)
		object_->update_styles_();

	return *this;
}

bool grafeex::window::controls::tool_tip_item_style::has(type value) const{
	return GRAFEEX_IS(object_->style_value_, value);
}

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::center(bool enabled){
	return (enabled ? add(type::center) : remove(type::center));
}

bool grafeex::window::controls::tool_tip_item_style::center() const{
	return has(type::center);
}

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::rtl_reading(bool enabled){
	return (enabled ? add(type::rtl_reading) : remove(type::rtl_reading));
}

bool grafeex::window::controls::tool_tip_item_style::rtl_reading() const{
	return has(type::rtl_reading);
}

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::parse_links(bool enabled){
	return (enabled ? add(type::parse_links) : remove(type::parse_links));
}

bool grafeex::window::controls::tool_tip_item_style::parse_links() const{
	return has(type::parse_links);
}

grafeex::window::controls::tool_tip_item_style &grafeex::window::controls::tool_tip_item_style::in_place(bool enabled){
	return (enabled ? add(type::in_place) : remove(type::in_place));
}

bool grafeex::window::controls::tool_tip_item_style::in_place() const{
	return has(type::in_place);
}

grafeex::window::controls::tool_tip_style::tool_tip_style(object_type &object)
	: base_type(object){}

grafeex::window::controls::tool_tip_style::~tool_tip_style() = default;

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::add(type value){
	GRAFEEX_SET(dynamic_cast<tool_tip *>(object_)->style_value_, value);
	return *this;
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::remove(type value){
	GRAFEEX_REMOVE(dynamic_cast<tool_tip *>(object_)->style_value_, value);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::has(type value) const{
	return GRAFEEX_IS(dynamic_cast<tool_tip *>(object_)->style_value_, value);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::always_tip(bool enabled){
	update_(TTS_ALWAYSTIP, enabled, false);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::always_tip() const{
	return has_(TTS_ALWAYSTIP, false);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::animate(bool enabled){
	update_(TTS_NOANIMATE, !enabled, false);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::animate() const{
	return !has_(TTS_NOANIMATE, false);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::fade(bool enabled){
	update_(TTS_NOFADE, !enabled, false);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::fade() const{
	return !has_(TTS_NOFADE, false);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::prefix(bool enabled){
	update_(TTS_NOPREFIX, !enabled, false);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::prefix() const{
	return !has_(TTS_NOPREFIX, false);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::use_visual_style(bool enabled){
	update_(TTS_USEVISUALSTYLE, enabled, false);
	return *this;
}

bool grafeex::window::controls::tool_tip_style::use_visual_style() const{
	return has_(TTS_USEVISUALSTYLE, false);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::center(bool enabled){
	return (enabled ? add(type::center) : remove(type::center));
}

bool grafeex::window::controls::tool_tip_style::center() const{
	return has(type::center);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::rtl_reading(bool enabled){
	return (enabled ? add(type::rtl_reading) : remove(type::rtl_reading));
}

bool grafeex::window::controls::tool_tip_style::rtl_reading() const{
	return has(type::rtl_reading);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::parse_links(bool enabled){
	return (enabled ? add(type::parse_links) : remove(type::parse_links));
}

bool grafeex::window::controls::tool_tip_style::parse_links() const{
	return has(type::parse_links);
}

grafeex::window::controls::tool_tip_style &grafeex::window::controls::tool_tip_style::in_place(bool enabled){
	return (enabled ? add(type::in_place) : remove(type::in_place));
}

bool grafeex::window::controls::tool_tip_style::in_place() const{
	return has(type::in_place);
}

grafeex::window::controls::tab_style::tab_style(object_type &object)
	: base_type(object){}

grafeex::window::controls::tab_style::~tab_style() = default;

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::buttons(bool enabled){
	update_(TCS_BUTTONS, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::buttons() const{
	return has_(TCS_BUTTONS, false);
}

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::flat_buttons(bool enabled){
	update_(TCS_FLATBUTTONS, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::flat_buttons() const{
	return has_(TCS_FLATBUTTONS, false);
}

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::hot_track(bool enabled){
	update_(TCS_HOTTRACK, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::hot_track() const{
	return has_(TCS_HOTTRACK, false);
}

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::multiline(bool enabled){
	update_(TCS_MULTILINE, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::multiline() const{
	return has_(TCS_MULTILINE, false);
}

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::right_justify(bool enabled){
	update_(TCS_RIGHTJUSTIFY, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::right_justify() const{
	return has_(TCS_RIGHTJUSTIFY, false);
}

grafeex::window::controls::tab_style &grafeex::window::controls::tab_style::scroll_opposite(bool enabled){
	update_(TCS_SCROLLOPPOSITE, enabled, false);
	return *this;
}

bool grafeex::window::controls::tab_style::scroll_opposite() const{
	return has_(TCS_SCROLLOPPOSITE, false);
}
