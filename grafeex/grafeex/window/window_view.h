#pragma once

#ifndef GRAFEEX_WINDOW_VIEW_H
#define GRAFEEX_WINDOW_VIEW_H

#include <memory>

#include "../wrappers/hwnd_wrapper.h"
#include "../d2d/d2d_factory.h"

namespace grafeex{
	namespace window{
		class object;

		class view{
		public:
			typedef wrappers::hwnd hwnd_type;
			typedef structures::enumerations::show_mode show_mode;

			typedef structures::color color_type;
			typedef ::D2D1_COLOR_F d2d_color_type;

			typedef std::shared_ptr<d2d_color_type> background_color_type;

			explicit view(object &object);

			virtual ~view();

			virtual view &enable();

			virtual view &disable();

			virtual bool enabled() const;

			virtual view &show(show_mode mode = show_mode::show);

			virtual view &hide();

			virtual bool visisble() const;

			virtual view &maximize();

			virtual bool maximized() const;

			virtual view &minimize();

			virtual bool minimized() const;

			virtual view &restore();

			virtual view &caption(const std::wstring &value);

			const std::wstring &caption() const;

			virtual view &background_color(const color_type &value);

			virtual view &background_color(const d2d_color_type &value);

			virtual d2d_color_type background_color() const;

			virtual bool has_background_color() const;

		protected:
			object *object_;
			background_color_type background_color_;
		};
	}
}

#endif /* !GRAFEEX_WINDOW_VIEW_H */
