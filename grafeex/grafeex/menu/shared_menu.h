#pragma once

#ifndef GRAFEEX_SHARED_MENU_H
#define GRAFEEX_SHARED_MENU_H

#include "menu_object.h"

namespace grafeex{
	namespace menu{
		class shared : public object{
		public:
			enum class option{
				nil,
				system,
			};

			explicit shared(const hwnd_type &target, option options = option::nil);

			virtual ~shared();
		};
	}
}

#endif /* !GRAFEEX_SHARED_MENU_H */
