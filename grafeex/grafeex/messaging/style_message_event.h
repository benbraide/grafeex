#pragma once

#ifndef GRAFEEX_STYLE_MESSAGE_EVENT_H
#define GRAFEEX_STYLE_MESSAGE_EVENT_H

#include "message_event.h"

namespace grafeex{
	namespace messaging{
		class style_event : public message_event{
		public:
			typedef ::DWORD value_type;
			typedef ::STYLESTRUCT info_type;

			typedef structures::enumerations::data_index data_index_type;

			explicit style_event(object &value);

			virtual ~style_event();

			virtual message_event &handle(handle_type type = handle_type::overwrite) override;

			virtual message_event &dispatch() override;

			virtual bool is_changing() const = 0;

			virtual bool is_extended() const;

			virtual value_type old_value() const;

			virtual value_type new_value() const;

			virtual style_event &filtered_value(value_type value);

			virtual value_type filtered_value() const;
			
		protected:
			info_type *info_;
			value_type filtered_;
		};

		template <bool style_is_changing>
		class typed_style_event;

		template <>
		class typed_style_event<false> : public style_event{
		public:
			explicit typed_style_event(object &value)
				: style_event(value){}

			virtual ~typed_style_event(){}

			virtual message_event &dispatch() override{
				if (style_event::dispatch().is_propagating())
					object_->target()->on_style_changed(*this);

				if (is_propagating()){
					if (is_extended())
						object_->target()->on_extended_style_changed(*this);
					else//Basic
						object_->target()->on_basic_style_changed(*this);
				}

				return *this;
			}

			virtual bool is_changing() const override{
				return false;
			}
		};

		template <>
		class typed_style_event<true> : public style_event{
		public:
			explicit typed_style_event(object &value)
				: style_event(value){}

			virtual ~typed_style_event(){}

			virtual message_event &dispatch() override{
				if (style_event::dispatch().is_propagating())
					*this << object_->target()->on_style_changing(*this);

				if (is_propagating()){
					if (is_extended())
						*this << object_->target()->on_extended_style_changing(*this);
					else//Basic
						*this << object_->target()->on_basic_style_changing(*this);
				}

				return *this;
			}

			virtual bool is_changing() const override{
				return true;
			}

		protected:
			virtual message_event &write_bool_(bool value) override{
				if (!value)//Change rejected
					filtered_ = info_->styleOld;

				return message_event::write_(static_cast<result_type>(0));
			}
		};

		using changing_style_event = typed_style_event<true>;
		using changed_style_event = typed_style_event<false>;
	}
}

#endif /* !GRAFEEX_STYLE_MESSAGE_EVENT_H */
