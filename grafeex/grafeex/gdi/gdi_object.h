#pragma once

#ifndef GRAFEEX_GDI_OBJECT_H
#define GRAFEEX_GDI_OBJECT_H

#include "../wrappers/gdi_wrapper.h"

namespace grafeex{
	namespace gdi{
		class object{
		public:
			typedef wrappers::gdi wrapper_type;
			typedef wrappers::gdi::value_type value_type;
			typedef wrappers::gdi::object_type object_type;

			virtual ~object();

			virtual operator value_type() const = 0;

			virtual operator wrapper_type() const = 0;

			virtual object_type type() const = 0;

		protected:
			virtual void init_();

			virtual void uninit_();
		};
	}
}

#endif /* !GRAFEEX_GDI_OBJECT_H */
