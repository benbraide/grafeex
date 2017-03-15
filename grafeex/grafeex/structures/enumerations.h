#pragma once

#ifndef GRAFEEX_ENUMERATIONS_H
#define GRAFEEX_ENUMERATIONS_H

#include "../common/preprocessor.h"
#include "../common/windows_headers.h"

namespace grafeex{
	namespace structures{
		namespace enumerations{
			enum class hit_target_type{
				nil						= HTNOWHERE,
				border					= HTBORDER,
				bottom					= HTBOTTOM,
				bottomleft				= HTBOTTOMLEFT,
				bottomright				= HTBOTTOMRIGHT,
				caption					= HTCAPTION,
				client					= HTCLIENT,
				close					= HTCLOSE,
				error					= HTERROR,
				help					= HTHELP,
				horizontal_scroll		= HTHSCROLL,
				left					= HTLEFT,
				menu					= HTMENU,
				maximize_button			= HTMAXBUTTON,
				minimize_button			= HTMINBUTTON,
				right					= HTRIGHT,
				size					= HTSIZE,
				system_menu				= HTSYSMENU,
				top						= HTTOP,
				top_left				= HTTOPLEFT,
				top_right				= HTTOPRIGHT,
				transparent				= HTTRANSPARENT,
				vertical_scroll			= HTVSCROLL,
			};

			enum class animation_type : ::DWORD{
				show			= 0,
				hide			= AW_HIDE,
				activate		= AW_ACTIVATE,
				roll			= 0,
				slide			= AW_SLIDE,
				fade			= AW_BLEND,
				left_to_right	= AW_HOR_POSITIVE,
				right_to_left	= AW_HOR_NEGATIVE,
				top_to_bottom	= AW_VER_POSITIVE,
				bottom_to_top	= AW_VER_NEGATIVE,
				center			= AW_CENTER,
			};

			enum class show_mode{
				hide							= SW_HIDE,
				normal							= SW_NORMAL,
				minimized						= SW_SHOWMINIMIZED,
				maximized						= SW_SHOWMAXIMIZED,
				normal_without_activating		= SW_SHOWNOACTIVATE,
				show							= SW_SHOW,
				minimize						= SW_MINIMIZE,
				maximize						= SW_MAXIMIZE,
				minimized_without_activating	= SW_SHOWMINNOACTIVE,
				without_activating				= SW_SHOWNA,
				restore							= SW_RESTORE,
				default							= SW_SHOWDEFAULT,
				force_minimize					= SW_FORCEMINIMIZE,
			};

			enum class position_type : ::UINT{
				nil					= 0,
				no_size				= SWP_NOSIZE,
				no_move				= SWP_NOMOVE,
				no_z_order			= SWP_NOZORDER,
				no_redraw			= SWP_NOREDRAW,
				no_activate			= SWP_NOACTIVATE,
				draw_frame			= SWP_DRAWFRAME,
				show				= SWP_SHOWWINDOW,
				hide				= SWP_HIDEWINDOW,
				discard_client		= SWP_NOCOPYBITS,
				no_owner_z_order	= SWP_NOOWNERZORDER,
				no_send_changing	= SWP_NOSENDCHANGING,
				defer_erase			= SWP_DEFERERASE,
				async				= SWP_ASYNCWINDOWPOS,
			};

			enum class placement_type : ::UINT{
				nil						= 0,
				async					= WPF_ASYNCWINDOWPLACEMENT,
				set_minimized_position	= WPF_SETMINPOSITION,
				restore_to_maximized	= WPF_RESTORETOMAXIMIZED,
			};

			enum class data_index{
				procedure				= GWLP_WNDPROC,
				instance				= GWLP_HINSTANCE,
				parent					= GWLP_HWNDPARENT,
				id						= GWL_ID,
				styles					= GWL_STYLE,
				extended_styles			= GWL_EXSTYLE,
				user_data				= GWLP_USERDATA,
			};

			enum class dialog_data_index{
				message_result			= DWLP_MSGRESULT,
				procedure				= DWLP_DLGPROC,
				user_data				= DWLP_USER,
			};

			enum class layered_attributes_option : ::DWORD{
				nil				= 0,
				use_rgb			= LWA_COLORKEY,
				use_alpha		= LWA_ALPHA,
				all				= LWA_COLORKEY | LWA_ALPHA,
			};

			GRAFEEX_MAKE_OPERATORS(animation_type)
			GRAFEEX_MAKE_OPERATORS(position_type)
			GRAFEEX_MAKE_OPERATORS(placement_type)
			GRAFEEX_MAKE_OPERATORS(layered_attributes_option)
		}
	}
}

#endif /* !GRAFEEX_ENUMERATIONS_H */
