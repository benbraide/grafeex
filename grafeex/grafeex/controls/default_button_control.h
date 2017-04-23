#pragma once

#ifndef GRAFEEX_DEFAULT_BUTTON_CONTROL_H
#define GRAFEEX_DEFAULT_BUTTON_CONTROL_H

#include "button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class default_button : public button{
			public:
				default_button();

				default_button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				default_button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				virtual ~default_button();

			protected:
				virtual void reset_persistent_styles_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_DEFAULT_BUTTON_CONTROL_H */
