#pragma once

#ifndef GRAFEEX_D2D_RENDER_TARGET_PTR_H
#define GRAFEEX_D2D_RENDER_TARGET_PTR_H

#include "d2d_render_target_manager.h"

namespace grafeex{
	namespace d2d{
		template <class render_type>
		class render_target_holder{
		public:
			typedef ::ID2D1RenderTarget interface_type;

			typedef render_type render_type;
			typedef render_target_manager<render_type> manager_type;

			explicit render_target_holder(manager_type &manager)
				: manager_(&manager){
				manager_->reset();
			}

			~render_target_holder(){
				if (manager_ != nullptr)
					manager_->reset();
			}

			void reset(){
				manager_ = nullptr;
			}

			interface_type &get(){
				return *manager_->get().Get();
			}

			render_type &renderer(){
				return manager_->get();
			}

		protected:
			manager_type *manager_;
		};
	}
}

#endif /* !GRAFEEX_D2D_RENDER_TARGET_PTR_H */
