#pragma once

#ifndef GRAFEEX_RADIO_CONTROL_GROUP_H
#define GRAFEEX_RADIO_CONTROL_GROUP_H

#include "control_object.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class radio_group : public controls::object{
			public:
				radio_group();

				explicit radio_group(gui_object_type &parent);

				explicit radio_group(const sibling_type &sibling);

				virtual ~radio_group();

				virtual rect_type dimensions(bool inner = false) const override;

				virtual point_type convert_to_screen(const point_type &value) const override;

				virtual rect_type convert_to_screen(const rect_type &value) const override;

				virtual point_type convert_from_screen(const point_type &value) const override;

				virtual rect_type convert_from_screen(const rect_type &value) const override;

				virtual bool create(gui_object_type &parent);

				virtual bool create(const sibling_type &sibling);

				virtual bool destroy();

				virtual bool is_created() const;

			protected:
				virtual void remove_parent_() override;

				virtual void add_(child_type &child) override;

				virtual void insert_into_parent_(gui_object_type &parent);

				virtual void insert_into_parent_(const sibling_type &sibling);

				virtual bool destroy_(bool force);
			};
		}
	}
}

#endif /* !GRAFEEX_RADIO_CONTROL_GROUP_H */
