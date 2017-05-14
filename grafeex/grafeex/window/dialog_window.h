#pragma once

#ifndef GRAFEEX_DIALOG_WINDOW_H
#define GRAFEEX_DIALOG_WINDOW_H

#include <functional>

#include "window_object.h"
#include "../threading/thread_modal_loop.h"

namespace grafeex{
	namespace window{
		class dialog : public object{
		public:
			typedef object base_type;

			typedef std::shared_ptr<threading::modal_loop> loop_type;
			typedef std::function<void(dialog &)> callback_type;

			dialog();

			virtual ~dialog();

			virtual bool is_dialog() const override;

			virtual bool is_modal() const;

			virtual int run(object_type &owner, const std::wstring &caption, const size_type &size, callback_type callback = nullptr);

			virtual int run(bool update_styles = true);

			virtual bool end(int code = 0);

		protected:
			using base_type::create_;

			virtual bool create_(object_type &owner, const std::wstring &caption, const size_type &size);

			virtual int run_();

			int result_;
			loop_type loop_;
		};
	}
}

#endif /* !GRAFEEX_DIALOG_WINDOW_H */
