#include "tool_tip_collection.h"

grafeex::collections::tool_tip::tool_tip(bool create)
	: base_type(create){}

grafeex::collections::tool_tip::tool_tip(gui_object_type &parent)
	: base_type(parent){}

grafeex::collections::tool_tip::tool_tip(const sibling_type &sibling)
	: base_type(sibling){}

grafeex::collections::tool_tip::~tool_tip(){
	destroy();
}

grafeex::collections::tool_tip &grafeex::collections::tool_tip::item(gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect){
	guard_type guard(base_type::lock_);
	auto item = std::make_shared<item_type>(*this, owner, value, bounding_rect);
	list_.push_back(item);
	return *this;
}

grafeex::collections::tool_tip &grafeex::collections::tool_tip::item(gui_object_type &owner, string_callback_type callback, const rect_type &bounding_rect){
	guard_type guard(base_type::lock_);
	auto item = std::make_shared<item_type>(*this, owner, L"", bounding_rect);
	item->events().get_text(callback);
	list_.push_back(item);
	return *this;
}

grafeex::collections::tool_tip_interface::item_type *grafeex::collections::tool_tip::get_item(size_type index) const{
	return (index < list_.size()) ? std::next(list_.begin(), index)->get() : nullptr;
}

grafeex::collections::tool_tip_interface::item_type *grafeex::collections::tool_tip::get_first_item() const{
	return (list_.empty() ? nullptr : list_.begin()->get());
}

grafeex::collections::tool_tip_interface::item_type *grafeex::collections::tool_tip::get_last_item() const{
	return (list_.empty() ? nullptr : list_.rbegin()->get());
}

grafeex::collections::tool_tip::size_type grafeex::collections::tool_tip::count() const{
	return list_.size();
}

bool grafeex::collections::tool_tip::empty() const{
	return list_.empty();
}

void grafeex::collections::tool_tip::remove_(typename base_type::child_type &child){
	base_type::remove_(child);
	for (auto iter = list_.begin(); iter != list_.end(); ++iter){
		if (iter->get() == &child){
			list_.erase(iter);
			break;
		}
	}
}
