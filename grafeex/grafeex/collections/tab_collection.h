#pragma once

#ifndef GRAFEEX_TAB_COLLECTION_H
#define GRAFEEX_TAB_COLLECTION_H

#include "tab_collection_interface.h"

#include "../window/dialog_window.h"
#include "../controls/tab_control.h"

namespace grafeex{
	namespace collections{
		template <class my_base_type>
		class basic_tab : public tab_interface, public my_base_type{
		public:
			typedef my_base_type my_base_type;

			typedef gui::object gui_object_type;
			typedef gui::object_sibling sibling_type;

			typedef window::object item_type;
			typedef window::object::index_type index_type;

			typedef window::controls::tab_item<window::object> basic_item_type;
			typedef window::controls::tab_item<window::dialog> dialog_item_type;

			typedef std::shared_ptr<item_type> object_type;
			typedef std::list<object_type> list_type;

			typedef typename my_base_type::guard_type guard_type;

			explicit basic_tab(gui_object_type &parent)
				: my_base_type(parent){}

			explicit basic_tab(const sibling_type &sibling)
				: my_base_type(sibling){}

			virtual ~basic_tab(){
				destroy();
			}

			virtual basic_tab &item(const std::wstring &title, callback_type callback) override{
				guard_type guard(my_base_type::lock_);
				auto item = std::make_shared<basic_item_type>(*this, title);

				list_.push_back(item);
				callback(*item);

				return *this;
			}

			virtual basic_tab &dialog(const std::wstring &title, callback_type callback) override{
				guard_type guard(my_base_type::lock_);
				auto item = std::make_shared<dialog_item_type>(*this, title);

				list_.push_back(item);
				callback(*item);

				return *this;
			}

			virtual item_type *get_item(index_type index) const override{
				return (index < list_.size()) ? std::next(list_.begin(), index)->get() : nullptr;
			}

			virtual item_type *get_first_item() const override{
				return (list_.empty() ? nullptr : list_.begin()->get());
			}

			virtual item_type *get_last_item() const override{
				return (list_.empty() ? nullptr : list_.rbegin()->get());
			}

			virtual index_type count() const override{
				return list_.size();
			}

			virtual bool empty() const override{
				return list_.empty();
			}

		protected:
			virtual void remove_(typename my_base_type::child_type &child) override{
				my_base_type::remove_(child);
				for (auto iter = list_.begin(); iter != list_.end(); ++iter){
					if (iter->get() == &child){
						list_.erase(iter);
						break;
					}
				}
			}

			list_type list_;
		};

		typedef basic_tab<window::controls::tab> tab;
	}
}

#endif /* !GRAFEEX_TAB_COLLECTION_H */
