#pragma once

#ifndef GRAFEEX_DEFAULT_SPLIT_BUTTON_CONTROL_H
#define GRAFEEX_DEFAULT_SPLIT_BUTTON_CONTROL_H

#include "split_button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class default_split_button : public split_button{
			public:
				default_split_button();

				default_split_button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				default_split_button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				virtual ~default_split_button();

			protected:
				virtual void reset_persistent_styles_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_DEFAULT_SPLIT_BUTTON_CONTROL_H */
