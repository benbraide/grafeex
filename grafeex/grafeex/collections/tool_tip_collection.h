#pragma once

#ifndef GRAFEEX_TOOL_TIP_COLLECTION_H
#define GRAFEEX_TOOL_TIP_COLLECTION_H

#include "tool_tip_collection_interface.h"

namespace grafeex{
	namespace collections{
		class tool_tip : public tool_tip_interface, public window::controls::tool_tip{
		public:
			typedef window::controls::tool_tip base_type;

			typedef tool_tip_interface::gui_object_type gui_object_type;
			typedef tool_tip_interface::rect_type rect_type;
			typedef tool_tip_interface::size_type size_type;

			typedef std::shared_ptr<item_type> object_type;
			typedef std::list<object_type> list_type;

			typedef typename base_type::guard_type guard_type;

			tool_tip(bool create = false);

			explicit tool_tip(gui_object_type &parent);

			explicit tool_tip(const sibling_type &sibling);

			virtual ~tool_tip();

			virtual tool_tip &item(gui_object_type &owner, const std::wstring &value, GCTTC_ARGS = nullptr) override;

			virtual tool_tip &item(gui_object_type &owner, const std::wstring &value, GCTTC_ARGS3 = nullptr) override;

			virtual tool_tip &item(gui_object_type &owner, string_callback_type string_callback, GCTTC_ARGS = nullptr) override;

			virtual tool_tip &item(gui_object_type &owner, string_callback_type string_callback, GCTTC_ARGS3 = nullptr) override;

			virtual item_type *get_item(size_type index) const override;

			virtual item_type *get_first_item() const override;

			virtual item_type *get_last_item() const override;

			virtual size_type count() const override;

			virtual bool empty() const override;

		protected:
			virtual void remove_(typename base_type::child_type &child) override;

			virtual object_type insert_(gui_object_type &owner, const std::wstring &value, GCTTC_ARGS2);

			list_type list_;
		};
	}
}

#endif /* !GRAFEEX_TOOL_TIP_COLLECTION_H */
