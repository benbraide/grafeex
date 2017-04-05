#pragma once

#ifndef GRAFEEX_SHARED_GDI_OBJECT_H
#define GRAFEEX_SHARED_GDI_OBJECT_H

#include "gdi_object.h"

namespace grafeex{
	namespace gdi{
		class shared_object : public object{
		public:
			shared_object(value_type value = nullptr);

			shared_object(const shared_object &) = default;

			virtual ~shared_object();

			shared_object &operator =(value_type value);

			shared_object &operator =(const shared_object &) = default;

			virtual operator value_type() const override;

			virtual operator wrapper_type() const override;

			virtual bool operator ==(std::nullptr_t rhs) const;

			virtual bool operator !=(std::nullptr_t rhs) const;

			friend bool operator ==(std::nullptr_t lhs, const shared_object &rhs);

			friend bool operator !=(std::nullptr_t lhs, const shared_object &rhs);

			virtual object_type type() const override;
			
			virtual object *owner() const;

		protected:
			wrapper_type value_;
		};
	}
}

#endif /* !GRAFEEX_SHARED_GDI_OBJECT_H */
