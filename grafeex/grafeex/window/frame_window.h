#pragma once

#ifndef GRAFEEX_FRAME_WINDOW_H
#define GRAFEEX_FRAME_WINDOW_H

#include "dialog_window.h"

namespace grafeex{
	namespace window{
		template <class window_type>
		class basic_frame : public window_type{
		public:
			typedef window_type window_type;

			typedef typename window_type::point_type point_type;
			typedef typename window_type::size_type size_type;

			typedef typename window_type::object_type object_type;
			typedef typename window_type::sibling_type sibling_type;

			typedef typename window_type::dword_type dword_type;

			basic_frame(){
				reset_persistent_styles_();
			}

			basic_frame(const std::wstring &caption, const point_type &offset, const size_type &size){
				reset_persistent_styles_();
				create(caption, offset, size);
			}

			basic_frame(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size){
				reset_persistent_styles_();
				create(parent, caption, offset, size);
			}

			basic_frame(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size){
				reset_persistent_styles_();
				create(sibling, caption, offset, size);
			}

			virtual ~basic_frame() = default;

			virtual dword_type black_listed_styles(bool is_extended) const override{
				return (window_type::black_listed_styles(is_extended) | (is_extended ? 0L : (WS_CAPTION | WS_BORDER | WS_SYSMENU)));
			}

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size){
				return window_type::create_(caption, offset, size);
			}

			virtual bool create(object_type &parent, const std::wstring &caption, const point_type &offset, const size_type &size){
				window_type::insert_into_parent_(parent);
				return window_type::create_(caption, offset, size);
			}

			virtual bool create(const sibling_type &sibling, const std::wstring &caption, const point_type &offset, const size_type &size){
				window_type::insert_into_parent_(sibling);
				return window_type::create_(caption, offset, size);
			}

		protected:
			virtual void reset_persistent_styles_() override{
				window_type::reset_persistent_styles_();
				GRAFEEX_SET(window_type::persistent_styles_.basic, WS_OVERLAPPEDWINDOW);
			}
		};

		typedef basic_frame<object> frame;
		typedef basic_frame<dialog> dialog_frame;
	}
}

#endif /* !GRAFEEX_FRAME_WINDOW_H */
