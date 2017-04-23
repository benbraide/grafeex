#pragma once

#ifndef GRAFEEX_D2D_WRITE_FACTORY_H
#define GRAFEEX_D2D_WRITE_FACTORY_H

#include <dwrite_2.h>
#include <wrl.h>

#pragma comment(lib, "dwrite.lib")

namespace grafeex{
	namespace d2d{
		class write_factory : public ::Microsoft::WRL::ComPtr<::IDWriteFactory>{
		public:
			typedef ::IUnknown unknown_type;
			typedef ::Microsoft::WRL::ComPtr<::IDWriteFactory> base_type;

			typedef base_type::InterfaceType interface_type;

			explicit write_factory(bool multi_threaded = true);

			~write_factory();

			operator interface_type &() const;
		};
	}
}

#endif /* !GRAFEEX_D2D_WRITE_FACTORY_H */
