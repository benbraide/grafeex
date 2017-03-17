#include "style_message_event.h"

grafeex::messaging::style_event::style_event(object &value)
	: message_event(value), info_(value.info().lparam<info_type *>()){

}

grafeex::messaging::style_event::~style_event(){}

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
