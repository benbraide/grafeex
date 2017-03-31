#pragma once

#ifndef GRAFEEX_WINDOW_VIEW_H
#define GRAFEEX_WINDOW_VIEW_H

#include "../wrappers/hwnd_wrapper.h"

namespace grafeex{
	namespace window{
		class object;

		class view{
		public:
			typedef wrappers::hwnd hwnd_type;
			typedef structures::enumerations::show_mode show_mode;

			explicit view(object &object);

			virtual ~view();

			virtual view &show(show_mode mode = show_mode::show);

			virtual view &hide();

			virtual view &maximize();

			virtual view &minimize();

			virtual view &restore();

			virtual view &caption(const std::wstring &value);

			const std::wstring &caption() const;

		protected:
			object &object_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_VIEW_H */
