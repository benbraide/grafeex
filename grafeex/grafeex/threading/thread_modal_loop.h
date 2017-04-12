#pragma once

#ifndef GRAFEEX_THREAD_MODAL_LOOP_H
#define GRAFEEX_THREAD_MODAL_LOOP_H

#include "thread_object.h"

namespace grafeex{
	namespace window{
		class object;
		class modal_dialog;
	}

	namespace threading{
		class modal_loop : public object{
		public:
			typedef window::object window_type;
			typedef window::modal_dialog modal_dialog_type;

			typedef ::LRESULT result_type;
			typedef ::WPARAM wparam_type;
			typedef ::LPARAM lparam_type;
			typedef ::UINT uint_type;

			explicit modal_loop(modal_dialog_type &modal_dialog);

			virtual ~modal_loop();

			virtual int run() override;

			virtual void stop();

			virtual bool consume(window_type &target, uint_type msg, wparam_type wparam, lparam_type lparam);

		protected:
			friend class application::object;
			friend class window::modal_dialog;

			virtual bool is_filtered_message_() const override;

			virtual void translate_() const override;

			virtual void dispatch_() override;

			virtual void dispatch_thread_message_() override;

			virtual bool on_idle_(int index) override;

			virtual bool is_stopped_() const override;

			modal_dialog_type *modal_dialog_;
			object *previous_modal_;
			bool running_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_MODAL_LOOP_H */
