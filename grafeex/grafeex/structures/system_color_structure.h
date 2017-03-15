#pragma once

#ifndef GRAFEEX_SYSTEM_COLOR_STRUCTURE_H
#define GRAFEEX_SYSTEM_COLOR_STRUCTURE_H

#include "color_structure.h"

namespace grafeex{
	namespace structures{
		class system_color{
		public:
			enum class index_type{
				_3d_dark_shadow					= COLOR_3DDKSHADOW,
				_3d_face						= COLOR_3DFACE,
				_3d_highlight					= COLOR_3DHIGHLIGHT,
				_3d_shadow						= COLOR_3DSHADOW,
				active_border					= COLOR_ACTIVEBORDER,
				active_caption					= COLOR_ACTIVECAPTION,
				app_work_space					= COLOR_APPWORKSPACE,
				backgorund						= COLOR_BACKGROUND,
				button_face						= COLOR_BTNFACE,
				button_highlight				= COLOR_BTNHIGHLIGHT,
				button_shadow					= COLOR_BTNSHADOW,
				button_text						= COLOR_BTNTEXT,
				caption_text					= COLOR_CAPTIONTEXT,
				desktop							= COLOR_DESKTOP,
				gradient_active_caption			= COLOR_GRADIENTACTIVECAPTION,
				gradient_inactive_caption		= COLOR_GRADIENTINACTIVECAPTION,
				gray_text						= COLOR_GRAYTEXT,
				grey_text						= COLOR_GRAYTEXT,
				highlight						= COLOR_HIGHLIGHT,
				highlight_text					= COLOR_HIGHLIGHTTEXT,
				hot_light						= COLOR_HOTLIGHT,
				inactive_border					= COLOR_INACTIVEBORDER,
				inactive_caption				= COLOR_INACTIVECAPTION,
				inactive_caption_text			= COLOR_INACTIVECAPTIONTEXT,
				info_background					= COLOR_INFOBK,
				info_text						= COLOR_INFOTEXT,
				menu							= COLOR_MENU,
				menu_bar						= COLOR_MENUBAR,
				menu_highlight					= COLOR_MENUHILIGHT,
				menu_text						= COLOR_MENUTEXT,
				scroll_bar						= COLOR_SCROLLBAR,
				window							= COLOR_WINDOW,
				window_frame					= COLOR_WINDOWFRAME,
				window_text						= COLOR_WINDOWTEXT,
			};

			static color get(int index, color::field_type alpha = static_cast<color::field_type>(color::alpha_type::opaque));

			static color get(index_type index, color::field_type alpha = static_cast<color::field_type>(color::alpha_type::opaque));
		};
	}
}

#endif /* !GRAFEEX_SYSTEM_COLOR_STRUCTURE_H */
