#pragma once

#ifndef GRAFEEX_D2D_DRAWER_H
#define GRAFEEX_D2D_DRAWER_H

#include <memory>

#include "d2d_render_target_holder.h"

namespace grafeex{
	namespace d2d{
		template <class render_type>
		class drawer{
		public:
			typedef ::HRESULT hresult_type;
			typedef ::HDC hdc_type;

			typedef render_type render_type;
			typedef render_target_holder<render_type> render_holder_type;
			typedef factory::interface_type factory_type;

			typedef typename render_holder_type::interface_type interface_type;
			typedef typename render_type::color_type color_type;
			typedef typename render_type::gdi_color_type gdi_color_type;
			typedef typename render_type::brush_interface_type brush_interface_type;
			typedef typename render_holder_type::manager_type manager_type;

			typedef std::shared_ptr<render_holder_type> render_holder_ptr_type;
			typedef std::shared_ptr<manager_type> manager_ptr_type;

			virtual ~drawer(){
				end_drawing();
			}

			virtual bool begin_drawing(){
				if (drawing_begun_)
					return false;

				create_render_holder_();
				render_holder_->get().BeginDraw();
				drawing_begun_ = true;

				return true;
			}

			virtual bool end_drawing(){
				if (!drawing_begun_)
					return false;

				auto result = render_holder_->get().EndDraw();
				if (FAILED(result)){
					render_holder_->reset();
					on_error_(result);
				}

				drawing_begun_ = false;
				return true;
			}

			virtual bool drawing_has_begun() const{
				return drawing_begun_;
			}

			virtual interface_type &renderer(bool begin_drawing = false){
				create_render_holder_();
				if (begin_drawing)
					this->begin_drawing();

				return render_holder_->get();
			}

			brush_interface_type &background_brush(const color_type &color){
				return render_holder_->renderer().background_brush(color);
			}

			brush_interface_type &background_brush(const gdi_color_type &color){
				return render_holder_->renderer().background_brush(color);
			}

			brush_interface_type &background_brush(){
				return render_holder_->renderer().background_brush();
			}

		protected:
			virtual void create_render_holder_() = 0;

			virtual void on_error_(hresult_type err) = 0;

			render_holder_ptr_type render_holder_;
			bool drawing_begun_ = false;
		};
	}
}

#endif /* !GRAFEEX_D2D_DRAWER_H */
