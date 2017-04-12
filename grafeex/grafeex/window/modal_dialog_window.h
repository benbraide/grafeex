#pragma once

#ifndef GRAFEEX_MODAL_DIALOG_WINDOW_H
#define GRAFEEX_MODAL_DIALOG_WINDOW_H

#include "dialog_window.h"
#include "../threading/thread_modal_loop.h"

namespace grafeex{
	namespace window{
		class modal_dialog : public dialog{
		public:
			modal_dialog();

			modal_dialog(object_type &owner, const std::wstring &caption, const point_type &offset, const size_type &size);

			modal_dialog(object_type &owner, const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size);

			virtual ~modal_dialog();

			virtual int run(object_type &owner, const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual int run(object_type &owner, const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size);

			virtual bool end(int code = 0);

		protected:
			virtual void reset_persistent_styles_() override;

			virtual int run_();

			int return_value_;
			threading::modal_loop loop_;
		};
	}
}

#endif /* !GRAFEEX_MODAL_DIALOG_WINDOW_H */
