#pragma once

#ifndef GRAFEEX_TOP_LEVEL_WINDOW_H
#define GRAFEEX_TOP_LEVEL_WINDOW_H

#include "window_object.h"

namespace grafeex{
	namespace window{
		class top_level : public object{
		public:
			top_level();

			top_level(const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual ~top_level();

			virtual bool is_top_level() const override;

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size);
		};
	}
}

#endif /* !GRAFEEX_TOP_LEVEL_WINDOW_H */
