#pragma once

#ifndef GRAFEEX_CONTROL_STYLES_H
#define GRAFEEX_CONTROL_STYLES_H

#include "../window/window_style.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class tool_tip_item;
			class tool_bar_item;

			class button_style : public window::style{
			public:
				typedef window::style base_type;
				typedef window::object object_type;

				enum class alignment_type : dword_type{
					nil				= 0,
					left			= BS_LEFT,
					center			= BS_CENTER,
					top				= BS_TOP,
					right			= BS_RIGHT,
					vcenter			= BS_VCENTER,
					bottom			= BS_BOTTOM,
				};

				explicit button_style(object_type &object);

				virtual ~button_style();

				button_style &flat(bool enabled);

				bool flat() const;

				button_style &multi_line(bool enabled);

				bool multi_line() const;

				button_style &text_alignment(alignment_type value);

				alignment_type text_alignment() const;
			};

			class tool_tip_item_style{
			public:
				typedef tool_tip_item object_type;

				enum class type : unsigned int{
					nil				= (0 << 0x0000),
					center			= (1 << 0x0000),
					rtl_reading		= (1 << 0x0001),
					parse_links		= (1 << 0x0002),
					in_place		= (1 << 0x0003),
				};

				explicit tool_tip_item_style(object_type &object);

				virtual ~tool_tip_item_style();

				tool_tip_item_style &add(type value);

				tool_tip_item_style &remove(type value);

				bool has(type value) const;

				tool_tip_item_style &center(bool enabled);

				bool center() const;

				tool_tip_item_style &rtl_reading(bool enabled);

				bool rtl_reading() const;

				tool_tip_item_style &parse_links(bool enabled);

				bool parse_links() const;

				tool_tip_item_style &in_place(bool enabled);

				bool in_place() const;

			protected:
				object_type *object_;
			};

			class tool_tip_style : public window::style{
			public:
				typedef window::style base_type;
				typedef window::object object_type;

				typedef tool_tip_item_style::type type;

				explicit tool_tip_style(object_type &object);

				virtual ~tool_tip_style();

				tool_tip_style &add(type value);

				tool_tip_style &remove(type value);

				bool has(type value) const;

				tool_tip_style &always_tip(bool enabled);

				bool always_tip() const;

				tool_tip_style &animate(bool enabled);

				bool animate() const;

				tool_tip_style &fade(bool enabled);

				bool fade() const;

				tool_tip_style &prefix(bool enabled);

				bool prefix() const;

				tool_tip_style &use_visual_style(bool enabled);

				bool use_visual_style() const;

				tool_tip_style &center(bool enabled);

				bool center() const;

				tool_tip_style &rtl_reading(bool enabled);

				bool rtl_reading() const;

				tool_tip_style &parse_links(bool enabled);

				bool parse_links() const;

				tool_tip_style &in_place(bool enabled);

				bool in_place() const;
			};

			class tab_style : public window::style{
			public:
				typedef window::style base_type;
				typedef window::object object_type;

				explicit tab_style(object_type &object);

				virtual ~tab_style();

				tab_style &buttons(bool enabled);

				bool buttons() const;

				tab_style &flat_buttons(bool enabled);

				bool flat_buttons() const;

				tab_style &hot_track(bool enabled);

				bool hot_track() const;

				tab_style &multiline(bool enabled);

				bool multiline() const;

				tab_style &right_justify(bool enabled);

				bool right_justify() const;

				tab_style &scroll_opposite(bool enabled);

				bool scroll_opposite() const;
			};

			class tool_bar_item_style{
			public:
				typedef tool_bar_item object_type;

				enum class type : unsigned int{
					nil				= (0 << 0x0000),
					auto_size		= (1 << 0x0000),
					dropdown		= (1 << 0x0001),
					no_prefix		= (1 << 0x0002),
					show_text		= (1 << 0x0003),
					whole_dropdown	= (1 << 0x0004),
				};

				explicit tool_bar_item_style(object_type &object);

				virtual ~tool_bar_item_style();

				tool_bar_item_style &add(type value);

				tool_bar_item_style &remove(type value);

				bool has(type value) const;

				tool_bar_item_style &auto_size(bool enabled);

				bool auto_size() const;

				tool_bar_item_style &dropdown(bool enabled);

				bool dropdown() const;

				tool_bar_item_style &no_prefix(bool enabled);

				bool no_prefix() const;

				tool_bar_item_style &show_text(bool enabled);

				bool show_text() const;

				tool_bar_item_style &whole_dropdown(bool enabled);

				bool whole_dropdown() const;

			protected:
				object_type *object_;
			};

			class tool_bar_style : public window::style{
			public:
				typedef window::style base_type;
				typedef window::object object_type;

				explicit tool_bar_style(object_type &object);

				virtual ~tool_bar_style();

				tool_bar_style &alt_drag(bool enabled);

				bool alt_drag() const;

				tool_bar_style &custom_erase(bool enabled);

				bool custom_erase() const;

				tool_bar_style &flat(bool enabled);

				bool flat() const;

				tool_bar_style &list(bool enabled);

				bool list() const;

				tool_bar_style &register_drop(bool enabled);

				bool register_drop() const;

				tool_bar_style &transparent(bool enabled);

				bool transparent() const;

				tool_bar_style &wrapable(bool enabled);

				bool wrapable() const;

				tool_bar_style &draw_dropdown_arrows(bool enabled);

				bool draw_dropdown_arrows() const;

				tool_bar_style &hide_clipped_buttons(bool enabled);

				bool hide_clipped_buttons() const;

				tool_bar_style &double_buffer(bool enabled);

				bool double_buffer() const;

				tool_bar_style &mixed_buttons(bool enabled);

				bool mixed_buttons() const;

				static const dword_type specifics = (TBSTYLE_ALTDRAG | TBSTYLE_CUSTOMERASE | TBSTYLE_FLAT | TBSTYLE_LIST |
					TBSTYLE_REGISTERDROP | TBSTYLE_TOOLTIPS | TBSTYLE_TRANSPARENT | TBSTYLE_WRAPABLE);

				static const dword_type extended_specifics = (TBSTYLE_EX_DRAWDDARROWS | TBSTYLE_EX_HIDECLIPPEDBUTTONS |
					TBSTYLE_EX_DOUBLEBUFFER | TBSTYLE_EX_MIXEDBUTTONS | TBSTYLE_EX_MULTICOLUMN | TBSTYLE_EX_VERTICAL);

			protected:
				virtual void final_write_(dword_type value, bool extended) override;

				virtual dword_type retrieve_(bool extended) const override;
			};

			GRAFEEX_MAKE_OPERATORS(button_style::alignment_type)
			GRAFEEX_MAKE_OPERATORS(tool_tip_item_style::type)
			GRAFEEX_MAKE_OPERATORS(tool_bar_item_style::type)
		}
	}
}

#endif /* !GRAFEEX_CONTROL_STYLES_H */
