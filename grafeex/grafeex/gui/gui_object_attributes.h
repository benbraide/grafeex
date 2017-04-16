#pragma once

#ifndef GRAFEEX_GUI_OBJECT_ATTRIBUTES_H
#define GRAFEEX_GUI_OBJECT_ATTRIBUTES_H

#include <functional>
#include <unordered_map>

#include "../common/preprocessor.h"
#include "../structures/rect_structure.h"

namespace grafeex{
	namespace gui{
		class object_tree;

		class object_attributes{
		public:
			typedef unsigned long long state_type;

			struct state{
				static const state_type nil				= (0 << 0x0000);
				static const state_type real_time		= (1 << 0x0000);
				static const state_type fill_parent		= (1 << 0x0001);
				static const state_type fill_content	= (1 << 0x0002);
				static const state_type align			= (1 << 0x0003);
				static const state_type last			= (0x0003);
			};

			typedef std::function<void(state_type)> handler_type;
			typedef std::unordered_map<state_type, handler_type> handlers_cache_type;

			typedef structures::point point_type;
			typedef structures::size size_type;
			typedef structures::float_size float_size_type;
			typedef structures::rect rect_type;
			typedef structures::rect::origin_type alignment_type;

			explicit object_attributes(object_tree &object);

			virtual ~object_attributes();

			virtual object_attributes &fill_parent_once(const rect_type &padding = {});

			virtual object_attributes &fill_parent(bool enabled, handler_type handler = nullptr, const rect_type &padding = {});

			virtual object_attributes &fill_parent(const float_size_type &size, const rect_type &padding = {});

			virtual object_attributes &fill_parent_width(const rect_type &padding = {});

			virtual object_attributes &fill_parent_height(const rect_type &padding = {});

			virtual bool parent_filled() const;

			virtual object_attributes &fill_content_once(const rect_type &padding = {});

			virtual object_attributes &fill_content(bool enabled, handler_type handler = nullptr, const rect_type &padding = {});

			virtual bool content_filled() const;

			virtual object_attributes &align(bool enabled, alignment_type alignment = alignment_type::nil, handler_type handler = nullptr,
				const size_type &offset = {});

			virtual bool aligned() const;

		private:
			friend class object_tree;

			virtual void trigger_(state_type states);

			object_tree *object_;
			state_type active_states_;
			handlers_cache_type handlers_cache_;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_ATTRIBUTES_H */
