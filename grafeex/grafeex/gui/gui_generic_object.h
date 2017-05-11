#pragma once

#ifndef GRAFEEX_GUI_GENERIC_OBJECT_H
#define GRAFEEX_GUI_GENERIC_OBJECT_H

#include <memory>

#include "../common/generic_tree.h"
#include "../events/event_tunnel.h"

#include "gui_object_sibling.h"

#define GGGO_EVENT(r, n, t)\
	event_tunnel &n(std::function<r(event_object_type &)> callback){\
		t.add(callback);\
		return *this;\
	}\
	event_tunnel &n(std::function<r()> callback){\
		t.add(callback);\
		return *this;\
	}

#define GGGO_EVENT2(r, n) GGGO_EVENT(r, n, n ## _event_)

#define GGGO_VOID_EVENT(n, t) GGGO_EVENT(void, n, t)
#define GGGO_VOID_EVENT2(n) GGGO_EVENT(void, n, n ## _event_)

#define GGGO_BOOL_EVENT(n, t) GGGO_EVENT(bool, n, t)
#define GGGO_BOOL_EVENT2(n) GGGO_EVENT(bool, n, n ## _event_)

namespace grafeex{
	namespace messaging{
		class message_event;
	}

	namespace gui{
		class generic_object : public object{
		public:
			typedef common::generic_tree<object, object_sibling> tree_type;

			typedef object::size_type size_type;
			typedef object::sibling_type sibling_type;

			class event_tunnel : public object::event_tunnel{
			public:
				typedef grafeex::events::entry entry_type;
				typedef grafeex::events::entry::group_type group_type;
				typedef grafeex::events::tunnel_interface tunnel_interface_type;

				typedef grafeex::events::object event_object_type;

				typedef grafeex::events::tunnel<void> void_event_type;
				typedef grafeex::events::tunnel<bool> bool_event_type;

				typedef void_event_type::callback_type void_callback_type;
				typedef void_event_type::no_args_callback_type void_no_args_callback_type;

				typedef bool_event_type::callback_type bool_callback_type;
				typedef bool_event_type::no_args_callback_type bool_no_args_callback_type;

				typedef std::unordered_map<group_type, tunnel_interface_type *> event_list_type;

				virtual ~event_tunnel();

				virtual void unbind(const entry_type &entry);

			protected:
				friend class generic_object;

				object *owner_;
				event_list_type event_list_;
			};

			typedef std::shared_ptr<event_tunnel> events_type;

			virtual ~generic_object();

			virtual object *non_sibling() override;

			virtual object *parent() const override;

			virtual object &traverse_siblings(sibling_traverser_type traverser) override;

			virtual const object &traverse_siblings(const_sibling_traverser_type traverser) const override;

			virtual object &dimensions(const rect_type &value, bool inner = false) override;

			virtual rect_type dimensions(bool inner = false) const override;

			virtual rect_type relative_dimensions() const override;

			virtual object &size(const size_type &value, bool inner = false) override;

			virtual size_type size(bool inner = false) const override;

			virtual object &offset(const size_type &value) override;

			virtual point_type offset() const override;

			virtual object &move(const point_type &value) override;

			virtual object &drag(const size_type &value) override;

			virtual object &align(alignment_type value, const size_type &delta = {}) override;

			virtual point_type compute_alignment(alignment_type value, const size_type &delta = {}) const override;

			virtual hit_target_type test(const point_type &value) const override;

			virtual point_type convert_to_screen(const point_type &value) const override;

			virtual rect_type convert_to_screen(const rect_type &value) const override;

			virtual point_type convert_from_screen(const point_type &value) const override;

			virtual rect_type convert_from_screen(const rect_type &value) const override;

			virtual object_type type() const override;

			virtual event_tunnel &events() override;

		protected:
			friend class messaging::message_event;

			virtual void remove_parent_() override;

			virtual void insert_into_parent_(gui_object_type &parent);

			virtual void insert_into_parent_(const sibling_type &sibling);

			virtual events_type get_events_();

			template <typename generic_events_type>
			events_type create_events_(){
				if (events_ == nullptr){
					events_ = std::make_shared<generic_events_type>();
					init_events_();
				}

				return events_;
			}

			virtual void init_events_();

			object *parent_ = nullptr;
			events_type events_;
		};
	}
}

#endif /* !GRAFEEX_GUI_GENERIC_OBJECT_H */
