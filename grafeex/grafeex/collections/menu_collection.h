#pragma once

#ifndef GRAFEEX_MENU_COLLECTION_H
#define GRAFEEX_MENU_COLLECTION_H

#include "../menu/menu_check_item.h"
#include "../menu/menu_separator.h"
#include "../menu/menu_group.h"
#include "../menu/menu_bar.h"
#include "../menu/menu_popup.h"

#include "menu_collection_interface.h"

namespace grafeex{
	namespace collections{
		template <class menu_type>
		class menu : public menu_interface, public menu_type{
		public:
			typedef menu_type menu_type;
			typedef menu_interface::index_type index_type;

			typedef gui::object gui_object_type;
			typedef gui::object_sibling sibling_type;

			typedef grafeex::menu::item item_type;
			typedef grafeex::menu::check_item check_item_type;
			typedef grafeex::menu::separator separator_type;

			typedef item_type::option option_type;

			typedef menu<grafeex::menu::group> group_type;
			typedef menu<grafeex::menu::popup> popup_type;

			typedef std::shared_ptr<gui::object> object_type;
			typedef std::list<object_type> list_type;
			typedef std::unordered_map<gui::object *, object_type> cache_type;

			typedef typename menu_type::guard_type guard_type;

			menu(){}

			template <typename value_type, typename... optional_types>
			explicit menu(value_type &value, optional_types... optional_values)
				: menu_type(value, optional_values...){}

			virtual ~menu(){
				menu_type::destroy();
			}

			virtual menu_interface &set_new_line(bool bordered = false) override{
				if (bordered)
					options_ = option_type::bordered_new_line;
				else//No border
					options_ = option_type::new_line;

				return *this;
			}

			virtual menu_interface &clear_new_line() override{
				options_ = option_type::nil;
				return *this;
			}

			virtual menu_interface &item(GCMI_ITEM_BASIC, GCMI_APPEND_INDEX) override{
				return item_<item_type>(value, callback, index);
			}

			virtual menu_interface &item(GCMI_ITEM_BASIC2, GCMI_APPEND_INDEX) override{
				return item_<item_type>(value, callback, index);
			}

			virtual menu_interface &item(void_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				return item_<item_type>(callback, draw_callback, measure_callback, index);
			}

			virtual menu_interface &item(void_no_args_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				return item_<item_type>(callback, draw_callback, measure_callback, index);
			}

			virtual menu_interface &check(GCMI_ITEM_BASIC, GCMI_APPEND_INDEX) override{
				return item_<check_item_type>(value, callback, index);
			}

			virtual menu_interface &check(GCMI_ITEM_BASIC2, GCMI_APPEND_INDEX) override{
				return item_<check_item_type>(value, callback, index);
			}

			virtual menu_interface &check(void_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				return item_<check_item_type>(callback, draw_callback, measure_callback, index);
			}

			virtual menu_interface &check(void_no_args_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				return item_<check_item_type>(callback, draw_callback, measure_callback, index);
			}

			virtual menu_interface &separator(GCMI_APPEND_INDEX) override{
				guard_type guard(menu_type::lock_);

				std::shared_ptr<separator_type> item;
				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);

				if (sibling == nullptr)
					item = std::make_shared<separator_type>(*this);
				else//Use sibling
					item = std::make_shared<separator_type>(sibling_type(*sibling, sibling_type::sibling_value_type::next));

				list_.push_back(item);
				return *this;
			}

			virtual menu_interface &separator(GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				guard_type guard(menu_type::lock_);
				auto item = std::make_shared<separator_type>();

				item->events().draw(draw_callback);
				item->events().measure(measure_callback);

				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);
				if (sibling == nullptr)
					item->create(*this);
				else//Use sibling
					item->create(sibling_type(*sibling, sibling_type::sibling_value_type::next));

				list_.push_back(item);
				return *this;
			}

			virtual menu_interface &sub(GCMI_ITEM_SUB, GCMI_APPEND_INDEX) override{
				guard_type guard(menu_type::lock_);

				auto item = std::make_shared<item_type>();
				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);

				if (sibling == nullptr)
					item->create(*this, value);
				else//Use sibling
					item->create(sibling_type(*sibling, sibling_type::sibling_value_type::next), value);

				auto sub = std::make_shared<popup_type>(*item);
				list_.push_back(item);
				cache_[item.get()] = sub;

				callback(*sub);
				return *this;
			}

			virtual menu_interface &sub(sub_callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX) override{
				guard_type guard(menu_type::lock_);
				auto item = std::make_shared<item_type>();

				item->events().draw(draw_callback);
				item->events().measure(measure_callback);

				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);
				if (sibling == nullptr)
					item->create(*this, L"");
				else//Use sibling
					item->create(sibling_type(*sibling, sibling_type::sibling_value_type::next), L"");

				auto sub = std::make_shared<popup_type>(*item);
				list_.push_back(item);
				cache_[item.get()] = sub;

				callback(*sub);
				return *this;
			}

			virtual menu_interface &group(sub_callback_type callback, GCMI_APPEND_INDEX) override{
				guard_type guard(menu_type::lock_);

				std::shared_ptr<group_type> item;
				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);

				if (sibling == nullptr)
					item = std::make_shared<group_type>(*static_cast<gui::object *>(this));
				else//Use sibling
					item = std::make_shared<group_type>(sibling_type(*sibling, sibling_type::sibling_value_type::next));

				list_.push_back(item);
				callback(*item);

				return *this;
			}

			virtual gui_object_type *get_item(index_type index) const override{
				return (index < list_.size()) ? std::next(list_.begin(), index)->get() : nullptr;
			}

			virtual gui_object_type *get_first_item() const override{
				return (list_.empty() ? nullptr : list_.begin()->get());
			}

			virtual gui_object_type *get_last_item() const override{
				return (list_.empty() ? nullptr : list_.rbegin()->get());
			}

			virtual index_type count() const override{
				return list_.size();
			}

			virtual bool empty() const override{
				return list_.empty();
			}

			virtual bool is_new_line() const override{
				return (options_ != option_type::nil);
			}

		protected:
			virtual void remove_(typename menu_type::child_type &child) override{
				menu_type::remove_(child);
				for (auto iter = list_.begin(); iter != list_.end(); ++iter){
					if (iter->get() == &child){
						list_.erase(iter);
						break;
					}
				}

				if (!cache_.empty())
					cache_.erase(&child);
			}

			template <typename target_type, typename callback_type>
			menu_interface &item_(GCMI_ITEM_BASIC3, GCMI_APPEND_INDEX){
				guard_type guard(menu_type::lock_);

				std::shared_ptr<item_type> item;
				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);

				if (sibling == nullptr)
					item = std::make_shared<target_type>(*this, value, options_);
				else//Use sibling
					item = std::make_shared<target_type>(sibling_type(*sibling, sibling_type::sibling_value_type::next), value, options_);

				options_ = option_type::nil;
				item->events().select(callback);
				list_.push_back(item);

				return *this;
			}

			template <typename target_type, typename callback_type>
			menu_interface &item_(callback_type callback, GCMI_OWNER_DRAW, GCMI_APPEND_INDEX){
				guard_type guard(menu_type::lock_);
				auto item = std::make_shared<target_type>(options_);

				item->events().select(callback);
				item->events().draw(draw_callback);
				item->events().measure(measure_callback);

				auto sibling = (index == GCMI_APPEND_VALUE) ? nullptr : menu_type::get_child(index);
				if (sibling == nullptr)
					item->create(*this, L"");
				else//Use sibling
					item->create(sibling_type(*sibling, sibling_type::sibling_value_type::next), L"");

				options_ = option_type::nil;
				list_.push_back(item);

				return *this;
			}

			list_type list_;
			cache_type cache_;
			option_type options_ = option_type::nil;
		};

		typedef menu<grafeex::menu::bar> menu_bar;
		typedef menu<grafeex::menu::popup> menu_popup;
		typedef menu<grafeex::menu::shared> shared_menu;
	}
}

#endif /* !GRAFEEX_MENU_COLLECTION_H */
