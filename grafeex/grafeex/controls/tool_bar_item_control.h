#pragma once

#ifndef GRAFEEX_TOOL_BAR_ITEM_CONTROL_H
#define GRAFEEX_TOOL_BAR_ITEM_CONTROL_H

#include "control_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class tool_bar;

			class tool_bar_item : public gui::generic_object{
			public:
				typedef ::HFONT font_type;
				typedef ::HGDIOBJ gdi_obj_type;
				typedef ::HWND native_hwnd_type;
				typedef ::DWRITE_FONT_WEIGHT font_weigth_type;

				typedef ::UINT uint_type;
				typedef ::UINT_PTR uint_ptr_type;
				typedef ::DWORD dword_type;

				typedef ::LPARAM lparam_type;
				typedef ::TTTOOLINFOW info_type;
				typedef ::NMCUSTOMDRAW draw_info_type;

				typedef gui::generic_object base_type;
				typedef structures::rect rect_type;

				typedef graphics::text::font_info_type font_info_type;
				typedef gdi::object_ptr<font_type> gdi_font_type;

				typedef tool_bar_item_style::type style_type;

				struct primary_info{
					gui_object_type *owner;
					native_hwnd_type owner_handle;
					std::wstring value;
					rect_type bounding_rect;
				};

				struct secondary_info{
					int max_width;
					std::wstring title;
					font_type font;
					gdi_obj_type image;
					gdi_font_type font_object;
				};

				class event_tunnel : public gui::generic_object::event_tunnel{
				public:
					typedef grafeex::events::tunnel<std::wstring> string_event_type;
					typedef grafeex::events::tunnel<dword_type> dword_event_type;

					event_tunnel();

					virtual ~event_tunnel();

					GGGO_BOOL_EVENT2(show)
					GGGO_VOID_EVENT2(hide)
					GGGO_VOID_EVENT2(link_click)
					GGGO_EVENT2(std::wstring, get_text)
					GGGO_EVENT2(dword_type, draw)

					bool_event_type show_event_;
					void_event_type hide_event_;
					void_event_type link_click_event_;
					string_event_type get_text_event_;
					dword_event_type draw_event_;
				};

				tool_bar_item();

				tool_bar_item(gui_object_type &parent, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect = rect_type());

				tool_bar_item(const sibling_type &sibling, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect = rect_type());

				virtual ~tool_bar_item();

				virtual object_type type() const override;

				virtual event_tunnel &events() override;

				virtual bool create(gui_object_type &parent, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect = rect_type());

				virtual bool create(const sibling_type &sibling, gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect = rect_type());

				virtual bool destroy();

				virtual bool is_created() const;

				virtual gui_object_type *owner() const;

				virtual tool_bar_item &text(const std::wstring &value);

				virtual const std::wstring &text() const;

				virtual tool_bar_item &bounding_rect(const rect_type &value);

				virtual const rect_type &bounding_rect() const;

				virtual tool_bar_item &title(const std::wstring &value);

				virtual const std::wstring &title() const;

				virtual tool_bar_item &max_width(int value);

				virtual int max_width() const;

				virtual tool_bar_item &font(const wchar_t *family, font_weigth_type weight = font_weigth_type::DWRITE_FONT_WEIGHT_NORMAL, long size = -12);

				virtual tool_bar_item &font(font_type value);

				virtual font_type font() const;

				virtual tool_bar_item &image(gdi_obj_type value);

				virtual gdi_obj_type image() const;

			protected:
				friend class tool_bar_item_style;
				friend class tool_bar;

				virtual dword_type on_draw(draw_info_type &info);

				virtual const std::wstring &on_get_text();

				virtual bool on_show();

				virtual void on_hide();

				virtual void on_link_click();

				virtual events_type get_events_() override;

				virtual void update_styles_();

				virtual void retrieve_info_(info_type &info) const;

				virtual bool in_place_(tool_bar &parent) const;

				virtual int max_width_(tool_bar &parent) const;

				virtual const std::wstring &title_(tool_bar &parent) const;

				virtual gdi_obj_type image_(tool_bar &parent) const;

				virtual font_type font_(tool_bar &parent) const;

				virtual bool create_(gui_object_type &owner, const std::wstring &value, const rect_type &bounding_rect);

				virtual void insert_into_parent_(gui_object_type &parent);

				virtual void insert_into_parent_(const sibling_type &sibling);

				tool_bar_item_style style_;
				style_type style_value_;
				primary_info primary_info_{};
				secondary_info secondary_info_{ -1 };
				std::wstring text_cache_;
				bool is_shown_ = false;
			};
		}
	}
}

#endif /* !GRAFEEX_TOOL_BAR_ITEM_CONTROL_H */
