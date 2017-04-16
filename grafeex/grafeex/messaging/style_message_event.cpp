#include "style_message_event.h"
#include "../window/window_object.h"

grafeex::messaging::style_event::style_event(object &value)
	: message_event(value), info_(value.info().lparam<info_type *>()){
	auto styles_removed = object_->target()->filter_style(info_->styleOld & ~info_->styleNew, is_extended());
	auto styles_added = object_->target()->filter_style(~info_->styleOld & info_->styleNew, is_extended());

	if (!is_extended()){//Exclude 'child' style
		GRAFEEX_REMOVE(styles_removed, WS_CHILD);
		GRAFEEX_REMOVE(styles_added, WS_CHILD);
	}

	filtered_ = GRAFEEX_REMOVE_V(GRAFEEX_SET_V(info_->styleOld, styles_added), styles_removed);
}

grafeex::messaging::style_event::~style_event() = default;

grafeex::messaging::message_event &grafeex::messaging::style_event::handle(handle_type type){
	info_->styleNew = filtered_;//Copy value
	return message_event::handle(type);
}

grafeex::messaging::message_event &grafeex::messaging::style_event::dispatch(){
	if (message_event::dispatch().is_propagating())
		*this << object_->target()->on_style_change(*this);
	return *this;
}

bool grafeex::messaging::style_event::is_extended() const{
	return (static_cast<data_index_type>(object_->info().wparam<int>()) == data_index_type::extended_styles);
}

grafeex::messaging::style_event::value_type grafeex::messaging::style_event::old_value() const{
	return info_->styleOld;
}

grafeex::messaging::style_event::value_type grafeex::messaging::style_event::new_value() const{
	return info_->styleNew;
}

grafeex::messaging::style_event &grafeex::messaging::style_event::filtered_value(value_type value){
	filtered_ = value;
	return *this;
}

grafeex::messaging::style_event::value_type grafeex::messaging::style_event::filtered_value() const{
	return filtered_;
}

grafeex::messaging::changing_style_event::changing_style_event(object &value)
	: style_event(value){}

grafeex::messaging::changing_style_event::~changing_style_event() = default;

grafeex::messaging::message_event &grafeex::messaging::changing_style_event::dispatch(){
	if (style_event::dispatch().is_propagating())
		*this << object_->target()->on_style_changing(*this);

	if (is_propagating()){
		if (is_extended())
			*this << object_->target()->on_extended_style_changing(*this);
		else//Basic
			*this << object_->target()->on_basic_style_changing(*this);
	}

	return *this;
}

bool grafeex::messaging::changing_style_event::is_changing() const{
	return true;
}

grafeex::messaging::message_event &grafeex::messaging::changing_style_event::write_bool_(bool value){
	if (!value)//Change rejected
		filtered_ = info_->styleOld;
	return message_event::write_(static_cast<result_type>(0));
}

grafeex::messaging::changed_style_event::changed_style_event(object &value)
	: style_event(value){}

grafeex::messaging::changed_style_event::~changed_style_event() = default;

grafeex::messaging::message_event &grafeex::messaging::changed_style_event::dispatch(){
	if (style_event::dispatch().is_propagating())
		object_->target()->on_style_changed(*this);

	if (is_propagating()){
		if (is_extended())
			object_->target()->on_extended_style_changed(*this);
		else//Basic
			object_->target()->on_basic_style_changed(*this);
	}

	return *this;
}

bool grafeex::messaging::changed_style_event::is_changing() const{
	return false;
}
