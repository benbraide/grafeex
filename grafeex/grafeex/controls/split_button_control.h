#pragma once

#ifndef GRAFEEX_SPLIT_BUTTON_CONTROL_H
#define GRAFEEX_SPLIT_BUTTON_CONTROL_H

#include "button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class split_button : public button{
			public:
				split_button();

				split_button(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				split_button(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				virtual ~split_button();

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

			protected:
				virtual void reset_persistent_styles_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_SPLIT_BUTTON_CONTROL_H */
