#pragma once

#ifndef GRAFEEX_D2D_RENDER_TARGET_MANAGER_H
#define GRAFEEX_D2D_RENDER_TARGET_MANAGER_H

#include "d2d_factory.h"

namespace grafeex{
	namespace d2d{
		template <class render_type>
		class render_target_manager{
		public:
			typedef factory::interface_type factory_type;
			typedef render_type render_type;

			typedef ::Microsoft::WRL::ComPtr<::ID2D1DrawingStateBlock> state_type;

			template <typename... value_types>
			explicit render_target_manager(factory_type &factory, value_types... values)
				: render_(factory, values...){
				render_->SetTransform(::D2D1::Matrix3x2F::Identity());
				if (SUCCEEDED(factory.CreateDrawingStateBlock(state_.GetAddressOf())))
					render_->SaveDrawingState(state_.Get());
				else//Reset
					state_ = nullptr;
			}

			render_type &get(){
				return render_;
			}

			render_type &reset(){
				if (state_ != nullptr)
					render_->RestoreDrawingState(state_.Get());
				return render_;
			}

		private:
			render_type render_;
			state_type state_;
		};
	}
}

#endif /* !GRAFEEX_D2D_RENDER_TARGET_MANAGER_H */
