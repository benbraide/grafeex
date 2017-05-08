#pragma once

#ifndef GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H
#define GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H

#include "dialog_window.h"

namespace grafeex{
	namespace window{
		template <class window_type>
		class top_level_frame : public object{
		public:
			typedef window_type window_type;

			typedef typename window_type::point_type point_type;
			typedef typename window_type::size_type size_type;

			typedef typename window_type::d2d_point_type d2d_point_type;
			typedef typename window_type::d2d_size_type d2d_size_type;

			top_level_frame(){
				reset_persistent_styles_();
			}

			top_level_frame(const std::wstring &caption, const point_type &offset, const size_type &size){
				reset_persistent_styles_();
				create(caption, offset, size);
			}

			virtual ~top_level_frame(){
				window_type::destroy();
			}

			virtual dword_type black_listed_styles(bool is_extended) const override{
				return (window_type::black_listed_styles(is_extended) | (is_extended ? 0L : (WS_CAPTION | WS_BORDER | WS_SYSMENU)));
			}

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size){
				return window_type::create_(caption, offset, size);
			}

		protected:
			virtual void reset_persistent_styles_() override{
				window_type::reset_persistent_styles_();
				GRAFEEX_SET(window_type::persistent_styles_.basic, WS_OVERLAPPEDWINDOW);
			}
		};
	}
}

#endif /* !GRAFEEX_TOP_LEVEL_FRAME_WINDOW_H */
