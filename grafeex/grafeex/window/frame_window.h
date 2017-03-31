#pragma once

#ifndef GRAFEEX_FRAME_WINDOW_H
#define GRAFEEX_FRAME_WINDOW_H

#include "window_object.h"

namespace grafeex{
	namespace window{
		class frame : public object{
		public:
			frame();

			frame(const std::wstring &caption, const point_type &offset, const size_type &size);

			frame(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size);

			frame(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual ~frame();

			virtual dword_type black_listed_styles(bool is_extended) const override;

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual bool create(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size);

			virtual bool create(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size);
		};
	}
}

#endif /* !GRAFEEX_FRAME_WINDOW_H */
