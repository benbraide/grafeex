#pragma once

#ifndef GRAFEEX_DEFAULT_COMMAND_LINK_CONTROL_H
#define GRAFEEX_DEFAULT_COMMAND_LINK_CONTROL_H

#include "command_link_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class default_command_link : public command_link{
			public:
				default_command_link();

				default_command_link(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				default_command_link(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { -5, 2 });

				virtual ~default_command_link();

			protected:
				virtual void reset_persistent_styles_() override;
			};
		}
	}
}

#endif /* !GRAFEEX_DEFAULT_COMMAND_LINK_CONTROL_H */
