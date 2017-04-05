#pragma once

#ifndef GRAFEEX_COM_H
#define GRAFEEX_COM_H

#include "windows_headers.h"

namespace grafeex{
	namespace common{
		class com{
		public:
			explicit com(bool multi_threaded = true);

			~com();
		};
	}
}

#endif /* !GRAFEEX_COM_H */
