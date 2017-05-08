#pragma once

#ifndef GRAFEEX_MESSAGE_WINDOW_H
#define GRAFEEX_MESSAGE_WINDOW_H

#include "window_object.h"

namespace grafeex{
	namespace window{
		class message : public object{
		public:
			message(bool create = false);

			virtual ~message();

			virtual dword_type black_listed_styles(bool is_extended) const override;

			virtual bool create();

		protected:
			virtual void reset_persistent_styles_() override;

			virtual hwnd_type get_parent_handle_() override;
		};
	}
}

#endif /* !GRAFEEX_MESSAGE_WINDOW_H */
