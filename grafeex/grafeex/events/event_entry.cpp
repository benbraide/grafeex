#include "event_entry.h"

grafeex::events::entry::entry()
	: group_(0), value_(0){}

grafeex::events::entry::entry(value_type group, value_type value)
	: group_(group), value_(value){}

bool grafeex::events::entry::operator==(const entry &rhs) const{
	return (group_ == rhs.group_ && value_ == rhs.value_);
}

bool grafeex::events::entry::operator!=(const entry &rhs) const{
	return !(*this == rhs);
}

grafeex::events::entry::group_type grafeex::events::entry::group() const{
	return group_;
}

std::size_t grafeex::events::entry_hasher::operator()(const entry &value) const{
	return std::hash<entry::value_type>()(value.value_);
}
