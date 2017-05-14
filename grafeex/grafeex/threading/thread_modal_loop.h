#pragma once

#ifndef GRAFEEX_THREAD_MODAL_LOOP_H
#define GRAFEEX_THREAD_MODAL_LOOP_H

#include "thread_object.h"

#ifndef GTML_POLL_SLEEP
#define GTML_POLL_SLEEP 5
#endif // !GTML_POLL_SLEEP

#ifndef GTML_POLL_TIMEOUT
#define GTML_POLL_TIMEOUT 2000
#endif // !GTML_POLL_TIMEOUT

namespace grafeex{
	namespace window{
		class object;
		class dialog;
	}

	namespace threading{
		class modal_loop : public object{
		public:
			typedef window::object window_type;
			typedef window::dialog modal_dialog_type;

			typedef ::LRESULT result_type;
			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;
			typedef ::UINT uint_type;

			modal_loop();

			explicit modal_loop(modal_dialog_type &modal_dialog);

			virtual ~modal_loop();

			virtual int run(modal_dialog_type &modal_dialog);

		protected:
			friend class application::object;
			friend class application::window_manager;
			friend class window::dialog;

			virtual bool is_filtered_message_() const override;

			virtual void translate_() const override;

			virtual void dispatch_() override;

			virtual bool on_idle_(int index) override;

			virtual bool is_stopped_() const override;

			modal_dialog_type *modal_dialog_;
			object *previous_pump_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_MODAL_LOOP_H */
