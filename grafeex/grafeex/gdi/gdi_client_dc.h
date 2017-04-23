#pragma once

#ifndef GRAFEEX_GDI_CLIENT_DC_H
#define GRAFEEX_GDI_CLIENT_DC_H

#include "../wrappers/hdc_wrapper.h"

namespace grafeex{
	namespace gdi{
		class client_dc : public wrappers::hdc{
		public:
			typedef ::HWND hwnd_type;

			typedef wrappers::hdc base_type;

			explicit client_dc(hwnd_type owner);

			~client_dc();

		protected:
			hwnd_type owner_;
		};
	}
}

#endif /* !GRAFEEX_GDI_CLIENT_DC_H */
