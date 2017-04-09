#pragma once

#ifndef GRAFEEX_D2D_FACTORY_H
#define GRAFEEX_D2D_FACTORY_H

#include <d2d1.h>
#include <d2d1helper.h>
#include <wrl.h>

#pragma comment(lib, "d2d1.lib")

namespace grafeex{
	namespace d2d{
		class factory : public ::Microsoft::WRL::ComPtr<::ID2D1Factory>{
		public:
			typedef ::Microsoft::WRL::ComPtr<::ID2D1Factory> base_type;

			typedef base_type::InterfaceType interface_type;

			explicit factory(bool multi_threaded = true);

			~factory();

			operator interface_type &() const;
		};
	}
}

#endif /* !GRAFEEX_D2D_FACTORY_H */
