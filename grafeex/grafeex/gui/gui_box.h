#pragma once

#ifndef GRAFEEX_GUI_BOX_H
#define GRAFEEX_GUI_BOX_H

#include "gui_object_tree.h"

namespace grafeex{
	namespace gui{
		template <class my_base_type>
		class box : public my_base_type{
		public:
			typedef gui::object::point_type point_type;
			typedef gui::object::rect_type rect_type;

			box(){}

			box(const rect_type &dimensions, const rect_type &padding)
				: dimensions_(dimensions), padding_(padding){}

			virtual ~box() = default;

			virtual box &dimensions(const rect_type &value, bool inner = false) override{
				if (inner)//Inflate with padding
					dimensions_ = value.get_inflated(padding_);
				else//Outer value
					dimensions_ = value;

				return *this;
			}

			virtual rect_type dimensions(bool inner = false) const override{
				if (!inner)//Outer value
					return (my_base_type::parent_ == nullptr) ? dimensions_ : my_base_type::parent_->convert_to_screen(dimensions_);

				auto value = dimensions_.get_deflated(padding_);//Deflate with padding
				return value.move_to(point_type{});//Move to [0, 0]
			}

			virtual point_type convert_to_screen(const point_type &value) const override{
				if (my_base_type::parent_ == nullptr)
					return (value + dimensions_.top_left() + padding_.top_left());

				return my_base_type::parent_->convert_to_screen((my_base_type::parent_->offset() - dimensions_.top_left()) +
					value + padding_.top_left());
			}

			virtual point_type convert_from_screen(const point_type &value) const override{
				if (my_base_type::parent_ == nullptr)
					return (value - dimensions_.top_left() - padding_.top_left());

				return (my_base_type::parent_->convert_from_screen(value) - (my_base_type::parent_->offset() -
					dimensions_.top_left()) - padding_.top_left());
			}

			virtual box &padding(const rect_type &value){
				padding_ = value;
				return *this;
			}

			virtual const rect_type &padding() const{
				return padding_;
			}

		protected:
			rect_type dimensions_;
			rect_type padding_;
		};
	}
}

#endif /* !GRAFEEX_GUI_BOX_H */
