#pragma once

#ifndef GRAFEEX_DIALOG_WINDOW_H
#define GRAFEEX_DIALOG_WINDOW_H

#include "window_object.h"

namespace grafeex{
	namespace window{
		class dialog : public object{
		public:
			typedef object base_type;

			dialog();

			virtual ~dialog();

			virtual bool is_dialog() const override;

			virtual bool is_modal() const;

			virtual bool do_modal(object &owner, bool center = true);

			virtual bool cancel_modal();

			virtual object *get_owner() const;

		protected:
			object *owner_;
		};
	}
}

#endif /* !GRAFEEX_DIALOG_WINDOW_H */
