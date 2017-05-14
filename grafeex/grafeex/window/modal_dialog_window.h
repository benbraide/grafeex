#pragma once

#ifndef GRAFEEX_MODAL_DIALOG_WINDOW_H
#define GRAFEEX_MODAL_DIALOG_WINDOW_H

#include "dialog_window.h"

namespace grafeex{
	namespace window{
		class modal_dialog : public dialog{
		public:
			modal_dialog();

			modal_dialog(object_type &owner, const std::wstring &caption, const size_type &size, callback_type callback = nullptr);

			virtual ~modal_dialog();

			virtual bool is_modal() const override;

			virtual int run(object_type &owner, const std::wstring &caption, const size_type &size, callback_type callback = nullptr) override;

		protected:
			virtual void reset_persistent_styles_() override;

			virtual int run_() override;
		};
	}
}

#endif /* !GRAFEEX_MODAL_DIALOG_WINDOW_H */
