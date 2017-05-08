#pragma once

#ifndef GRAFEEX_CHECK_CONTROL_H
#define GRAFEEX_CHECK_CONTROL_H

#include "button_control.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class check : public button{
			public:
				check();

				check(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				check(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				virtual ~check();

				virtual bool create(object_type &parent, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

				virtual bool create(const sibling_type &sibling, const std::wstring &label, const point_type &offset, const size_type &padding = { 5, -5 });

			protected:
				virtual void reset_persistent_styles_() override;

				virtual size_type compute_size_(const std::wstring &label) override;

				virtual size_type compute_additional_size_(const std::wstring &label) override;
			};
		}
	}
}

#endif /* !GRAFEEX_CHECK_CONTROL_H */
