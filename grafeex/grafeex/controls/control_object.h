#pragma once

#ifndef GRAFEEX_CONTROL_OBJECT_H
#define GRAFEEX_CONTROL_OBJECT_H

#include "../window/window_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class object : public window::object{
			public:
				typedef window::object base_type;
				typedef ::INITCOMMONCONTROLSEX init_info_type;

				enum class control_type{
					button,
					edit,
					static_,
					list_box,
					combo_box,
					combo_box_ex,
					scroll_bar,
					tab,
					tool_tip,
					animate,
					tool_bar,
					status_bar,
					track_bar,
					rebar,
					date_time_picker,
					hot_key,
					ip,
					hyperlink,
					list_view,
					tree_view,
					native_font,
					pager,
					progress,
					up_down,
					header,
				};

				explicit object(control_type type);

				virtual ~object();

				virtual dword_type black_listed_styles(bool is_extended) const override;

				static dword_type get_initializer(control_type type);

				static const wchar_t *get_class_name(control_type type);

				static procedure_type get_procedure(const wchar_t *class_name);

			protected:
				virtual bool init_common_(control_type type);

				virtual bool create_(const std::wstring &caption, const point_type &offset, const size_type &size,
					dword_type styles = 0, dword_type extended_styles = 0);

				std::wstring class_name_;
				static dword_type initialized_controls_;
			};
		}
	}
}

#endif /* !GRAFEEX_CONTROL_OBJECT_H */
