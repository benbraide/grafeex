#pragma once

#ifndef GRAFEEX_WINDOW_STYLE_H
#define GRAFEEX_WINDOW_STYLE_H

#include "../wrappers/hwnd_wrapper.h"

namespace grafeex{
	namespace window{
		class object;

		class style{
		public:
			typedef wrappers::hwnd hwnd_type;
			typedef wrappers::hwnd::data_index data_index_type;

			typedef ::DWORD dword_type;

			struct info_type{
				dword_type basic;
				dword_type extended;
			};

			struct update_info{
				bool active;
				info_type enabled;
				info_type disabled;
			};

			explicit style(object &object);

			virtual ~style();

			style &begin();

			style &end();

			style &cancel();

			bool has_begun() const;

			style &apply_basic(dword_type value, bool enabled);

			style &apply_extended(dword_type value, bool enabled);

			style &apply_modal();

			style &dbl_click(bool enabled);

			bool dbl_click() const;

			style &drop_shadow(bool enabled);

			bool drop_shadow() const;

			style &horizontal_redraw(bool enabled);

			bool horizontal_redraw() const;

			style &vertical_redraw(bool enabled);

			bool vertical_redraw() const;

			style &close(bool enabled);

			bool close() const;

			style &maximize(bool enabled);

			bool maximize() const;

			style &minimize(bool enabled);

			bool minimize() const;

			style &border(bool enabled);

			bool border() const;

			style &dialog_frame(bool enabled);

			bool dialog_frame() const;

			style &caption(bool enabled);

			bool caption() const;

			style &system_menu(bool enabled);

			bool system_menu() const;

			style &thick_frame(bool enabled);

			bool thick_frame() const;

			style &clip_children(bool enabled);

			bool clip_children() const;

			style &clip_siblings(bool enabled);

			bool clip_siblings() const;

			style &horizontal_scroll_bar(bool enabled);

			bool horizontal_scroll_bar() const;

			style &vertical_scroll_bar(bool enabled);

			bool vertical_scroll_bar() const;

			style &tab_stop(bool enabled);

			bool tab_stop() const;

			style &enabled(bool enabled);

			bool enabled() const;

			style &visible(bool enabled);

			bool visible() const;

			style &file_drop(bool enabled);

			bool file_drop() const;

			style &taskbar(bool enabled);

			bool taskbar() const;

			style &sunken_edge(bool enabled);

			bool sunken_edge() const;

			style &context_help(bool enabled);

			bool context_help() const;

			style &control_parent(bool enabled);

			bool control_parent() const;

			style &dialog_modal_frame(bool enabled);

			bool dialog_modal_frame() const;

			style &layered(bool enabled);

			bool layered() const;

			style &right_alignment(bool enabled);

			bool right_alignment() const;

			style &rtl_reading(bool enabled);

			bool rtl_reading() const;

			style &rtl_layout(bool enabled);

			bool rtl_layout() const;

			style &left_scroll_bar(bool enabled);

			bool left_scroll_bar() const;

			style &mouse_activation(bool enabled);

			bool mouse_activation() const;

			style &inheritable_layout(bool enabled);

			bool inheritable_layout() const;

			style &parent_notify(bool enabled);

			bool parent_notify() const;

			style &static_edge(bool enabled);

			bool static_edge() const;

			style &window_edge(bool enabled);

			bool window_edge() const;

			style &top_most(bool enabled);

			bool top_most() const;

			style &tarnsparent(bool enabled);

			bool tarnsparent() const;

			bool has_basic(dword_type value) const;

			bool has_extended(dword_type value) const;

			dword_type basic() const;

			dword_type extended() const;

			const info_type &enabled_changes() const;

			const info_type &disabled_changes() const;

		protected:
			hwnd_type object_value_() const;

			dword_type merge_changes_(bool extended) const;

			void write_changes_();

			void write_(dword_type value, bool extended, bool add);

			virtual void final_write_(dword_type value, bool extended);

			style &update_(dword_type value, bool enabled, bool extended);

			style &enable_(dword_type value, bool extended);

			style &disable_(dword_type value, bool extended);

			virtual dword_type retrieve_(bool extended) const;

			bool has_(dword_type value, bool extended) const;

			object *object_;
			update_info update_info_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_STYLE_H */
