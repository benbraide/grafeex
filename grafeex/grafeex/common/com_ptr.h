#pragma once

#ifndef GRAFEEX_COM_PTR_H
#define GRAFEEX_COM_PTR_H

#include "windows_headers.h"

namespace grafeex{
	namespace common{
		template <class interface_type>
		class com_ptr{
		public:
			typedef ::HRESULT result_type;
			typedef interface_type interface_type;

			com_ptr()
				: interface_(nullptr){}

			explicit com_ptr(interface_type *value)
				: interface_(&value){}

			template <typename target_type>
			explicit com_ptr(target_type &target)
				: interface_(nullptr){
				if (FAILED(target.QueryInterface(&interface_)))
					interface_ = nullptr;
			}

			com_ptr(const com_ptr &) = delete;
			
			~com_ptr(){
				release();
			}

			com_ptr &operator =(interface_type *value){
				release();
				interface_ = value;
				return *this;
			}

			com_ptr &operator =(const com_ptr &) = delete;

			operator interface_type &() const{
				return *interface_;
			}

			operator interface_type *() const{
				return interface_;
			}

			operator interface_type **() const{
				return &interface_;
			}

			interface_type *operator ->() const{
				return interface_;
			}

			bool operator ==(const com_ptr &rhs) const{
				return (interface_ == rhs.interface_);
			}

			bool operator !=(const com_ptr &rhs) const{
				return (interface_ != rhs.interface_);
			}

			bool operator ==(std::nullptr_t) const{
				return (interface_ == nullptr);
			}

			bool operator !=(std::nullptr_t) const{
				return (interface_ != nullptr);
			}

			void release(){
				if (interface_ != nullptr){
					interface_->Release();
					interface_ = nullptr;
				}
			}

			template <typename target_type>
			void query_target(target_type &target){
				release();
				if (FAILED(target.QueryInterface(&interface_)))
					interface_ = nullptr;
			}

			bool valid() const{
				return (interface_ != nullptr);
			}

		protected:
			interface_type *interface_;
		};
	}
}

#endif /* !GRAFEEX_COM_PTR_H */
