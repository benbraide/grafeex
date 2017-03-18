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

		class changing_style_event : public style_event{
		public:
			explicit changing_style_event(object &value);

			virtual ~changing_style_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;

		protected:
			virtual message_event &write_bool_(bool value) override;
		};

		class changed_style_event : public style_event{
		public:
			explicit changed_style_event(object &value);

			virtual ~changed_style_event();

			virtual message_event &dispatch() override;

			virtual bool is_changing() const override;
		};
	}
}

#endif /* !GRAFEEX_STYLE_MESSAGE_EVENT_H */
