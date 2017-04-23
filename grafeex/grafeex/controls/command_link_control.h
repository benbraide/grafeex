#pragma once

#ifndef GRAFEEX_COMMAND_LINK_CONTROL_H
#define GRAFEEX_COMMAND_LINK_CONTROL_H

#include "button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class command_link : public button{
			public:
				command_link();

				command_link(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				command_link(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, 2 });

				virtual ~command_link();

				virtual command_link &note(const std::wstring &value);

				virtual const std::wstring &note() const;

			protected:
				virtual void created_() override;

				virtual void reset_persistent_styles_() override;

				virtual size_type compute_size_(const std::wstring &label) override;

				virtual size_type compute_additional_size_(const std::wstring &label) override;

				std::wstring note_;
			};
		}
	}
}

#endif /* !GRAFEEX_COMMAND_LINK_CONTROL_H */
