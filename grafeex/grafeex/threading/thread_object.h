#pragma once

#ifndef GRAFEEX_THREAD_OBJECT_H
#define GRAFEEX_THREAD_OBJECT_H

#include "thread_message_queue.h"
#include "thread_scheduler.h"

namespace grafeex{
	namespace application{
		class object;
	}

	namespace threading{
		class modal_loop;

		class object{
		public:
			typedef wrappers::msg msg_type;
			typedef msg_type::uint_type uint_type;
			typedef msg_type::wparam_type wparam_type;
			typedef msg_type::lparam_type lparam_type;

			struct status_info{
				bool is_posted;
				int return_value;
			};

			object();

			virtual ~object();

			virtual int run();

			virtual bool wake_wait();

			template <typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			bool post_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()) const{
				return (::PostThreadMessageW(id_, msg, (object::wparam_type)wparam, (object::lparam_type)lparam) != FALSE);
			}

			template <typename wparam_type = wparam_type, typename lparam_type = lparam_type>
			bool post_message(uint_type msg, const wparam_type &wparam = wparam_type(), const lparam_type &lparam = lparam_type()){
				return (::PostThreadMessageW(id_, msg, (object::wparam_type)wparam, (object::lparam_type)lparam) != FALSE);
			}

			virtual const id &get_id() const;

		protected:
			friend class application::object;
			friend class modal_loop;

			virtual bool is_sent_() const;

			virtual bool is_filtered_message_() const;

			virtual void translate_() const;

			virtual void dispatch_();

			virtual void dispatch_thread_message_();

			virtual bool on_idle_(int index);

			virtual bool is_stopped_() const;

			id id_;
			message_queue queue_;
			scheduler scheduler_;
			msg_type cache_;
			status_info status_;
			object *modal_;
		};
	}
}

#endif /* !GRAFEEX_THREAD_OBJECT_H */
