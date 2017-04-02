#pragma once

#ifndef GRAFEEX_MENU_OBJECT_H
#define GRAFEEX_MENU_OBJECT_H

#include <climits>

#include "../common/random_number.h"
#include "../wrappers/hwnd_wrapper.h"

#include "menu_group.h"

namespace grafeex{
	namespace menu{
		class object : public gui::object_tree, public tree{
		public:
			typedef gui::object_tree base_type;

			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::menu value_type;

			typedef wrappers::menu::info_type info_type;
			typedef wrappers::menu::dword_type dword_type;
			typedef wrappers::menu::brush_type brush_type;

			typedef gui::object_tree::traverser_type traverser_type;
			typedef gui::object_tree::const_traverser_type const_traverser_type;

			typedef gui::object_tree::index_type index_type;
			typedef gui::object_tree::size_type size_type;

			typedef gui::object_tree::child_type child_type;
			typedef common::basic_random_number<id_type> random_engine_type;

			typedef ::UINT uint_type;
			typedef ::ULONG_PTR ulong_ptr_type;

			enum class track_option : uint_type{
				nil					= 0,
				left_align			= TPM_LEFTALIGN,
				right_align			= TPM_RIGHTALIGN,
				center_align		= TPM_CENTERALIGN,
				top_align			= TPM_TOPALIGN,
				bottom_align		= TPM_BOTTOMALIGN,
				vcenter_align		= TPM_VCENTERALIGN,
				dont_notify			= TPM_NONOTIFY,
				return_cmd			= TPM_RETURNCMD,
				left_button			= TPM_LEFTBUTTON,
				right_button		= TPM_RIGHTBUTTON,
				no_animation		= TPM_NOANIMATION,
				hor_pos_animation	= TPM_HORPOSANIMATION,
				hor_neg_animation	= TPM_HORNEGANIMATION,
				ver_pos_animation	= TPM_VERPOSANIMATION,
				ver_neg_animation	= TPM_VERNEGANIMATION,
				recursive			= TPM_RECURSE,
				right_to_left		= TPM_LAYOUTRTL,
			};

			class event_tunnel : public base_type::event_tunnel{
			public:
				event_tunnel();

				virtual ~event_tunnel();

				GGGO_VOID_EVENT2(select)

				void_event_type select_event_;
			};

			object(native_type value);

			object(value_type value);

			virtual ~object();

			virtual object_type type() const override;
			
			virtual event_tunnel &events() override;

			virtual native_type native_value() const override;

			virtual object &traverse_children_absolute(traverser_type traverser) override;

			virtual const object &traverse_children_absolute(const_traverser_type traverser) const override;

			virtual const child_type *get_child_absolute(index_type index) const override;

			virtual child_type *get_child_absolute(index_type index) override;

			virtual index_type get_child_index_absolute(const child_type &child) const override;

			virtual index_type get_children_count_absolute() const override;

			virtual const child_type *find_child(id_type id) const override;

			virtual child_type *find_child(id_type id) override;

			virtual id_type generate_id() override;

			virtual bool track(const hwnd_type &owner, const point_type &offset, track_option options = track_option::left_align);

			virtual bool set(const info_type &info);

			template <typename... types>
			bool set(types... values){
				return value_.set(values...);
			}

			virtual bool styles(dword_type value, bool apply_to_submenus = false);

			virtual dword_type styles() const;

			virtual bool max_height(uint_type value, bool apply_to_submenus = false);

			virtual uint_type max_height() const;

			virtual bool background_brush(brush_type value, bool apply_to_submenus = false);

			virtual brush_type background_brush() const;

			virtual bool context_help_id(dword_type value);

			virtual dword_type context_help_id() const;

		protected:
			virtual events_type get_events_() override;

			virtual bool init_();

			value_type value_;
			static random_engine_type random_engine_;
		};

		GRAFEEX_MAKE_OPERATORS(object::track_option)
	}
}

#endif /* !GRAFEEX_MENU_OBJECT_H */
