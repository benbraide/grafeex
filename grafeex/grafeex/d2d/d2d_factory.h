#pragma once

#ifndef GRAFEEX_D2D_FACTORY_H
#define GRAFEEX_D2D_FACTORY_H

#include <d2d1.h>
#include <d2d1helper.h>

#include "../common/com_ptr.h"

#pragma comment(lib, "d2d1.lib")

namespace grafeex{
	namespace d2d{
		class factory : public common::com_ptr<::ID2D1Factory>{
		public:
			typedef common::com_ptr<::ID2D1Factory> base_type;

			explicit factory(bool multi_threaded = true);

			~factory();
		};
	}
}

#endif /* !GRAFEEX_D2D_FACTORY_H */
