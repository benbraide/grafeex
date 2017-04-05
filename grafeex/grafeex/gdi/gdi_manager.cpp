#include "gdi_manager.h"

void grafeex::gdi::manager::init(){
	static unsigned long acl_entries[] = { 0 };
	guard_type guard(lock_);

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, dc_type> >(L"gdi32", "CreateCompatibleDC",
		[](dc_type a) -> dc_type{
		guard_type guard(lock_);

		auto v = ::CreateCompatibleDC(a);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, string_type, string_type, string_type, dev_mode_type> >(L"gdi32", "CreateDCW",
		[](string_type a, string_type b, string_type c, dev_mode_type d) -> dc_type{
		guard_type guard(lock_);

		auto v = ::CreateDCW(a, b, c, d);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, string_type, string_type, string_type, dev_mode_type> >(L"gdi32", "CreateICW",
		[](string_type a, string_type b, string_type c, dev_mode_type d) -> dc_type{
		guard_type guard(lock_);
		
		auto v = ::CreateICW(a, b, c, d);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, hwnd_type> >(L"user32", "GetDC",
		[](hwnd_type a) -> dc_type{
		guard_type guard(lock_);

		auto v = ::GetDC(a);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false, a };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, hwnd_type, rgn_type, dword_type> >(L"user32", "GetDCEx",
		[](hwnd_type a, rgn_type b, dword_type c) -> dc_type{
		guard_type guard(lock_);

		auto v = ::GetDCEx(a, b, c);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false, a };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<dc_type, hwnd_type> >(L"user32", "GetWindowDC",
		[](hwnd_type a) -> dc_type{
		guard_type guard(lock_);

		auto v = ::GetWindowDC(a);
		if (v != nullptr)//Cache object
			dc_cache_[v] = dc_info{ false, a };

		return v;
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<bool_type, hwnd_type, dc_type> >(L"user32", "ReleaseDC",
		[](hwnd_type a, dc_type b) -> bool_type{
		lock_.lock();

		auto entry = dc_cache_.find(b);
		if (entry == dc_cache_.end()){//Not in cache
			lock_.unlock();
			return ::ReleaseDC(a, b);
		}

		if (!entry->second.unknown && entry->second.owner == nullptr){//Should be deleted
			lock_.unlock();
			return ::DeleteDC(b);
		}

		remove_dc_from_objects_(b, entry->second.object_list);
		auto owner = entry->second.owner;

		dc_cache_.erase(entry);
		lock_.unlock();

		return ::ReleaseDC(owner, b);
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<bool_type, dc_type> >(L"gdi32", "DeleteDC",
		[](dc_type a) -> bool_type{
		lock_.lock();

		auto entry = dc_cache_.find(a);
		if (entry == dc_cache_.end()){//Not in cache
			lock_.unlock();
			return ::DeleteDC(a);
		}

		if (!entry->second.unknown && entry->second.owner != nullptr){//Should be released
			lock_.unlock();
			return ::ReleaseDC(entry->second.owner, a);
		}

		remove_dc_from_objects_(a, entry->second.object_list);
		dc_cache_.erase(entry);
		lock_.unlock();

		return ::DeleteDC(a);
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<bool_type, value_type> >(L"gdi32", "DeleteObject",
		[](value_type a) -> bool_type{
		guard_type guard(lock_);

		auto entry = object_cache_.find(a);
		if (entry == object_cache_.end())//Not in cache
			return ::DeleteObject(a);

		if (!entry->second.object_list.empty()){//Defer delete
			entry->second.deleted = true;
			return true;
		}

		object_cache_.erase(entry);
		return ::DeleteObject(a);
	}));

	hook_list_.push_back(std::make_shared<common::windows_hook<value_type, dc_type, value_type> >(L"gdi32", "SelectObject",
		[](dc_type a, value_type b) -> value_type{
		lock_.lock();

		auto dc_entry = dc_cache_.find(a);
		if (dc_entry == dc_cache_.end()){//Unknown
			dc_cache_[a] = dc_info{ true };
			dc_entry = dc_cache_.find(a);
		}

		value_type to_be_deleted = nullptr;
		value_type previous_value = nullptr;

		auto previous_object = ::SelectObject(a, b);
		auto previous_entry = object_cache_.find(previous_object);
		if (previous_entry != object_cache_.end()){//Remove dc from previous entry
			previous_value = previous_entry->first;
			auto dc_in_entry = std::find(previous_entry->second.object_list.begin(),
				previous_entry->second.object_list.end(), a);

			if (dc_in_entry != previous_entry->second.object_list.end()){
				previous_entry->second.object_list.erase(dc_in_entry);
				if (previous_entry->second.deleted && previous_entry->second.object_list.empty()){
					to_be_deleted = previous_entry->first;//Object should be deleted
					object_cache_.erase(previous_entry);
				}
			}

			auto entry_in_dc = std::find(dc_entry->second.object_list.begin(),
				dc_entry->second.object_list.end(), previous_entry->first);

			if (entry_in_dc != dc_entry->second.object_list.end())
				dc_entry->second.object_list.erase(entry_in_dc);
		}

		if (b != nullptr){
			auto object_entry = object_cache_.find(b);
			if (object_entry == object_cache_.end()){//Unknown
				object_cache_[a] = object_info{ false };
				object_entry = object_cache_.find(b);
			}

			dc_entry->second.object_list.push_back(b);//Add object to dc list
			object_entry->second.object_list.push_back(a);//Add dc to object list
		}

		lock_.unlock();
		if (to_be_deleted != nullptr)
			::DeleteObject(to_be_deleted);

		return previous_value;
	}));

	::HOOK_TRACE_INFO info{};
	if (FAILED(::LhSetInclusiveACL(acl_entries, 1, &info)))
		hook_list_.clear();//Failed to activate hooks
}

void grafeex::gdi::manager::uninit(){
	guard_type guard(lock_);
	hook_list_.clear();
}

grafeex::gdi::object *grafeex::gdi::manager::owner(value_type value){
	guard_type guard(lock_);
	auto entry = owner_cache_.find(value);
	return (entry == owner_cache_.end()) ? nullptr : entry->second;
}

void grafeex::gdi::manager::remove_dc_from_objects_(value_type dc, object_list_type &list){
	for (auto object : list){
		auto object_entry = object_cache_.find(object);
		if (object_entry != object_cache_.end()){//Remove from object list
			auto entry_in_object = std::find(object_entry->second.object_list.begin(),
				object_entry->second.object_list.end(), dc);

			if (entry_in_object == object_entry->second.object_list.end())
				continue;

			object_entry->second.object_list.erase(entry_in_object);
			if (object_entry->second.deleted && object_entry->second.object_list.empty()){
				::DeleteObject(object_entry->first);
				object_cache_.erase(object_entry);
			}
		}
	}
}

grafeex::gdi::manager::hook_list_type grafeex::gdi::manager::hook_list_;

grafeex::gdi::manager::owner_cache_type grafeex::gdi::manager::owner_cache_;

grafeex::gdi::manager::dc_cache_type grafeex::gdi::manager::dc_cache_;

grafeex::gdi::manager::object_cache_type grafeex::gdi::manager::object_cache_;

grafeex::gdi::manager::lock_type grafeex::gdi::manager::lock_;
