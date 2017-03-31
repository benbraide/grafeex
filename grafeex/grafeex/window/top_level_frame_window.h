#pragma once

#ifndef GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H
#define GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H

#include "window_object.h"

namespace grafeex{
	namespace window{
		class top_level_frame : public object{
		public:
			top_level_frame();

			top_level_frame(const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual ~top_level_frame();

			virtual dword_type black_listed_styles(bool is_extended) const override;

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size);
		};
	}
}

#endif /* !GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H */
