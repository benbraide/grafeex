#pragma once

#ifndef GRAFEEX_TOOL_TIP_CONTROL_H
#define GRAFEEX_TOOL_TIP_CONTROL_H

#include "tool_tip_item_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class tool_tip : public object, public messaging::tool_tip_notify_event_handler{
			public:
				typedef controls::tool_tip_style style_type;

				typedef object::dword_type dword_type;
				typedef tool_tip_item::secondary_info secondary_info_type;
				typedef tool_tip_item::font_type font_type;
				typedef tool_tip_item::gdi_obj_type gdi_obj_type;
				typedef tool_tip_item::info_type item_info_type;
				typedef tool_tip_item::style_type item_style_type;
				typedef tool_tip_item::font_weigth_type font_weigth_type;

				class event_tunnel : public object::event_tunnel{
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

				tool_tip(bool create = false);

				explicit tool_tip(gui_object_type &parent);

				explicit tool_tip(const sibling_type &sibling);

				virtual ~tool_tip();

				virtual dword_type white_listed_styles(bool is_extended) const override;

				virtual style_type &style() override;

				virtual event_tunnel &events() override;

				virtual bool create();

				virtual bool create(gui_object_type &parent);

				virtual bool create(const sibling_type &sibling);

				virtual tool_tip_item *current_item() const;

				virtual tool_tip &title(const std::wstring &value);

				virtual const std::wstring &title() const;

				virtual tool_tip &max_width(int value);

				virtual int max_width() const;

				virtual tool_tip &font(const wchar_t *family, font_weigth_type weight = font_weigth_type::DWRITE_FONT_WEIGHT_NORMAL, long size = -12);

				virtual tool_tip &font(font_type value);

				virtual font_type font() const;

				virtual tool_tip &image(gdi_obj_type value);

				virtual gdi_obj_type image() const;

				static const dword_type general_styles = (TTS_ALWAYSTIP | TTS_NOANIMATE | TTS_NOFADE | TTS_NOPREFIX | TTS_USEVISUALSTYLE);

			protected:
				friend class tool_tip_style;
				friend class tool_tip_item;

				virtual dword_type on_control_draw(messaging::custom_draw_event &e) override;

				virtual const std::wstring &on_tool_tip_get_text(messaging::tool_tip_get_text_event &e) override;

				virtual void on_tool_tip_show(messaging::object &e) override;

				virtual void on_tool_tip_hide(messaging::object &e) override;

				virtual void on_tool_tip_link_click(messaging::object &e) override;

				virtual void reset_persistent_styles_() override;

				virtual style_ptr_type get_style_() override;

				virtual events_type get_events_() override;

				item_style_type style_value_;
				secondary_info_type secondary_info_{ -1 };
				std::wstring text_cache_;
			};
		}
	}
}

#endif /* !GRAFEEX_TOOL_TIP_CONTROL_H */
