#pragma once

#ifndef GRAFEEX_GUI_OBJECT_COLLECTION_H
#define GRAFEEX_GUI_OBJECT_COLLECTION_H

#include <list>
#include <memory>
#include <string>
#include <functional>

#include "../gui/gui_object_tree.h"

#define GCGUIO_CALLBACK(t) std::function<void(t &) >
#define GCGUIO_CALLBACK_ARG(t) GCGUIO_CALLBACK(t) callback

#define GCGUIO_WIN_CALLBACK_ARG(t) GCGUIO_CALLBACK(grafeex::window::t) callback
#define GCGUIO_CTRL_CALLBACK_ARG(t) GCGUIO_CALLBACK(grafeex::window::controls::t) callback

#define GCGUIO_WIN_ARGS_IMPL1(t) const std::wstring &caption, const point_type &offset, const size_type &size, GCGUIO_CALLBACK_ARG(t)
#define GCGUIO_WIN_ARGS1(t) GCGUIO_WIN_ARGS_IMPL1(t) = nullptr

#define GCGUIO_WIN_ARGS_IMPL(t) const std::wstring &caption, const point_type &offset, const size_type &size, GCGUIO_WIN_CALLBACK_ARG(t)
#define GCGUIO_WIN_ARGS(t) GCGUIO_WIN_ARGS_IMPL(t) = nullptr

#define GCGUIO_FWD_WIN_ARGS *owner_, caption, offset, size
#define GCGUIO_FWD_WIN_ARGS2 caption, offset, size, callback

#define GCGUIO_CTRL_ARGS_IMPL1(t) const std::wstring &label, const point_type &offset, const size_type &padding, GCGUIO_CALLBACK_ARG(t)
#define GCGUIO_CTRL_ARGS1(t) GCGUIO_CTRL_ARGS_IMPL1(t) = nullptr

#define GCGUIO_CTRL_ARGS_IMPL(t) const std::wstring &label, const point_type &offset, const size_type &padding, GCGUIO_CTRL_CALLBACK_ARG(t)
#define GCGUIO_CTRL_ARGS(t) GCGUIO_CTRL_ARGS_IMPL(t) = nullptr

#define GCGUIO_CTRL_ARGS2_IMPL(t) const std::wstring &label, const point_type &offset, GCGUIO_CTRL_CALLBACK_ARG(t)
#define GCGUIO_CTRL_ARGS2(t) GCGUIO_CTRL_ARGS2_IMPL(t) = nullptr

#define GCGUIO_FWD_CTRL_ARGS *owner_, label, offset, padding
#define GCGUIO_FWD_CTRL_ARGS2 label, offset, padding, callback

#define GCGUIO_CTRL_PAD_ARGS_IMPL(t) GCGUIO_CTRL_ARGS2_IMPL(t), const size_type &padding
#define GCGUIO_CTRL_PAD_ARGS(t, pX, pY) GCGUIO_CTRL_ARGS2(t), const size_type &padding = size_type(pX, pY)

#define GCGUIO_BTN_ARGS_IMPL(t) GCGUIO_CTRL_PAD_ARGS_IMPL(t)
#define GCGUIO_BTN_ARGS(t) GCGUIO_CTRL_PAD_ARGS(t, 5, 2)

#define GCGUIO_SBTN_ARGS(t) GCGUIO_CTRL_PAD_ARGS(t, -5, 2)
#define GCGUIO_CHK_ARGS(t) GCGUIO_CTRL_PAD_ARGS(t, 5, -5)

#define GCGUIO_LBL_ARGS_IMPL(t) const std::wstring &label, const point_type &offset, GCGUIO_CTRL_CALLBACK_ARG(t)
#define GCGUIO_LBL_ARGS(t) GCGUIO_LBL_ARGS_IMPL(t) = nullptr

#define GCGUIO_FWD_LBL_ARGS *owner_, label, offset
#define GCGUIO_FWD_LBL_ARGS2 label, offset, callback

#define GCGUIO_CREATE_CTRL(t) control<grafeex::window::controls::t>(GCGUIO_FWD_CTRL_ARGS2)

namespace grafeex{
	namespace window{
		template <class window_type>
		class basic_frame;

		class object;
		class dialog;

		namespace controls{
			class button;
			class default_button;
			class split_button;
			class default_split_button;
			class check;
			class radio;
			class radio_group;
			class label;
			class tab;
		}
	}

	namespace collections{
		template <class my_base_type>
		class basic_tab;

		class tool_tip;

		class gui_object : public gui::object_tree{
		public:
			typedef std::size_t std_size_type;

			typedef gui::object gui_object_type;
			typedef gui::object_tree gui_object_tree_type;
			typedef gui::object_tree base_type;

			typedef std::shared_ptr<gui_object_type> object_type;
			typedef std::list<object_type> list_type;

			typedef grafeex::window::basic_frame<grafeex::window::object> frame_type;
			typedef grafeex::window::basic_frame<grafeex::window::dialog> dialog_frame_type;

			typedef basic_tab<grafeex::window::controls::tab> tab_type;

			explicit gui_object(gui_object_type &owner);

			virtual ~gui_object();

			template <typename window_type>
			gui_object &window(GCGUIO_WIN_ARGS1(window_type)){
				return insert_(std::make_shared<window_type>(GCGUIO_FWD_WIN_ARGS), callback);
			}

			template <typename control_type>
			gui_object &control(GCGUIO_CTRL_ARGS1(control_type)){
				return insert_(std::make_shared<control_type>(GCGUIO_FWD_CTRL_ARGS), callback);
			}

			virtual gui_object &frame_window(GCGUIO_WIN_ARGS1(frame_type));

			virtual gui_object &frame_dialog(GCGUIO_WIN_ARGS1(dialog_frame_type));

			virtual gui_object &button_control(GCGUIO_BTN_ARGS(button));

			virtual gui_object &default_button_control(GCGUIO_BTN_ARGS(default_button));

			virtual gui_object &split_button_control(GCGUIO_SBTN_ARGS(split_button));

			virtual gui_object &default_split_button_control(GCGUIO_SBTN_ARGS(default_split_button));

			virtual gui_object &check_control(GCGUIO_CHK_ARGS(check));

			virtual gui_object &radio_control_group(GCGUIO_CTRL_CALLBACK_ARG(radio_group));

			virtual gui_object &radio_control(GCGUIO_CHK_ARGS(radio));

			virtual gui_object &label_control(GCGUIO_LBL_ARGS(label));

			virtual gui_object &tool_tip_control(GCGUIO_CALLBACK_ARG(tool_tip));

			virtual gui_object &tab_control(GCGUIO_CALLBACK_ARG(tab_type));

			template <typename my_base_type>
			gui_object &typed_tab_control(GCGUIO_CALLBACK_ARG(basic_tab<my_base_type>)){
				return insert_(std::make_shared<basic_tab<my_base_type> >(*owner_), callback);
			}

			virtual gui_object_type *get_item(std_size_type index) const;

			virtual gui_object_type *get_first_item() const;

			virtual gui_object_type *get_last_item() const;

			virtual std_size_type count() const;

			virtual bool empty() const;

		protected:
			virtual void remove_(typename base_type::child_type &child) override;

			template <typename object_type, typename callback_type>
			gui_object &insert_(object_type item, callback_type callback){
				list_.push_back(item);
				if (callback != nullptr)
					callback(*item);
				return *this;
			}

			gui_object_type *owner_;
			list_type list_;
		};
	}
}

#endif /* !GRAFEEX_GUI_OBJECT_COLLECTION_H */