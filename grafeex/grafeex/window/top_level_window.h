#pragma once

#ifndef GRAFEEX_TOP_LEVEL_WINDOW_H
#define GRAFEEX_TOP_LEVEL_WINDOW_H

#include "dialog_window.h"

namespace grafeex{
	namespace window{
		template <class window_type>
		class basic_top_level : public window_type{
		public:
			typedef window_type window_type;

			typedef typename window_type::point_type point_type;
			typedef typename window_type::size_type size_type;

			typedef typename window_type::d2d_point_type d2d_point_type;
			typedef typename window_type::d2d_size_type d2d_size_type;

			basic_top_level(){
				reset_persistent_styles_();
			}

			basic_top_level(const std::wstring &caption, const point_type &offset, const size_type &size){
				reset_persistent_styles_();
				create(caption, offset, size);
			}

			basic_top_level(const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size){
				reset_persistent_styles_();
				create(caption, offset, size);
			}

			virtual ~basic_top_level() = default;

			virtual bool is_top_level() const override{
				return true;
			}

			virtual bool create(const std::wstring &caption, const point_type &offset, const size_type &size){
				return window_type::create_(caption, offset, size);
			}

			virtual bool create(const std::wstring &caption, const d2d_point_type &offset, const d2d_size_type &size){
				return window_type::create_(caption, offset, size);
			}

		protected:
			virtual void reset_persistent_styles_() override{
				window_type::persistent_styles_.basic = WS_OVERLAPPEDWINDOW;
			}
		};

		typedef basic_top_level<object> top_level;
		typedef basic_top_level<dialog> dialog_top_level;
	}
}

#endif /* !GRAFEEX_TOP_LEVEL_WINDOW_H */
