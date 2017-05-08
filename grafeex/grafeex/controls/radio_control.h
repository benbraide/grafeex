#pragma once

#ifndef GRAFEEX_RADIO_CONTROL_H
#define GRAFEEX_RADIO_CONTROL_H

#include "button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class radio : public button{
			public:
				radio();

				radio(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				radio(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				virtual ~radio();

			protected:
				friend class radio_group;

				virtual hwnd_type get_parent_handle_() override;

				virtual void reset_persistent_styles_() override;

				virtual size_type compute_size_(const std::wstring &label) override;

				virtual size_type compute_additional_size_(const std::wstring &label) override;
			};
		}
	}
}

#endif /* !GRAFEEX_RADIO_CONTROL_H */
