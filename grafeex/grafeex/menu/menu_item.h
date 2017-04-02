#pragma once

#ifndef GRAFEEX_MENU_ITEM_H
#define GRAFEEX_MENU_ITEM_H

#include "../wrappers/menu_wrapper.h"
#include "menu_tree.h"

namespace grafeex{
	namespace menu{
		class object;
		class popup;

		class item : public gui::generic_object{
		public:
			typedef gui::object base_type;

			typedef tree_type::index_type index_type;
			typedef tree::id_type id_type;

			typedef wrappers::menu::uint_type uint_type;
			typedef wrappers::menu::ulong_ptr_type ulong_ptr_type;

			typedef ::MENUITEMINFOW info_type;

			enum class option{
				nil,
				new_line,
				bordered_new_line,
			};

			class event_tunnel : public gui::generic_object::event_tunnel{
			public:
				event_tunnel();

				virtual ~event_tunnel();

				virtual event_tunnel &select();

				GGGO_VOID_EVENT2(select)
				GGGO_VOID_EVENT2(draw)
				GGGO_VOID_EVENT2(measure)

				void_event_type select_event_;
				void_event_type draw_event_;
				void_event_type measure_event_;
			};

			explicit item(option options = option::nil);

			item(gui_object_type &parent, const std::wstring &value, option options = option::nil);

			item(const sibling_type &sibling, const std::wstring &value, option options = option::nil);

			virtual ~item();

			virtual object_type type() const override;

			virtual event_tunnel &events() override;

			virtual bool create(gui_object_type &parent, const std::wstring &value);

			virtual bool create(const sibling_type &sibling, const std::wstring &value);

			virtual bool destroy();

			virtual bool is_created() const;

			virtual menu::object *get_sub_menu() const;

			virtual item &select();

			virtual item &enable(bool value = true);

			virtual item &gray();

			virtual item &check(bool value = true);

			virtual item &set_as_default();

			virtual id_type id() const;

			virtual uint_type get_states() const;

			virtual index_type get_item_index_in_parent() const;

			virtual bool is_action() const;

			virtual bool is_separator() const;

			virtual bool is_inside_group() const;

			virtual bool is_disabled() const;

			virtual bool is_grayed() const;

			virtual bool is_checked() const;

			virtual bool is_default() const;

			virtual bool is_new_line() const;

			virtual bool is_bordered() const;

			virtual bool is_owner_drawn() const;

		protected:
			friend class popup;

			virtual events_type get_events_() override;

			virtual void insert_into_parent_(gui_object_type &parent);

			virtual void insert_into_parent_(const sibling_type &sibling);

			virtual bool create_(index_type index, const std::wstring &value);

			virtual bool owner_drawn_() const;

			virtual event_tunnel::void_event_type &draw_event_();

			id_type id_;
			option options_;
			menu::object *sub_;
		};
	}
}

#endif /* !GRAFEEX_MENU_ITEM_H */
