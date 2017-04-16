#include "gui_object_attributes.h"
#include "gui_object_tree.h"

grafeex::gui::object_attributes::object_attributes(object_tree &object)
	: object_(&object), active_states_(state::nil){}

grafeex::gui::object_attributes::~object_attributes(){
	if (GRAFEEX_IS(active_states_, state::fill_parent))
		object_->attribute_removed_(state::fill_parent);

	if (GRAFEEX_IS(active_states_, state::fill_content))
		object_->attribute_removed_(state::fill_content);

	if (GRAFEEX_IS(active_states_, state::align))
		object_->attribute_removed_(state::align);
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_parent_once(const rect_type &padding){
	auto parent = object_->parent();
	if (parent != nullptr)//Update bounding rectangle
		object_->dimensions(parent->dimensions(true).get_deflated(padding), false);
	return *this;
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_parent(bool enabled, handler_type handler, const rect_type &padding){
	object_tree::guard_type guard(object_->lock_);
	if (enabled == parent_filled())
		return *this;

	if (enabled){
		GRAFEEX_SET(active_states_, state::fill_parent);
		if (handler == nullptr){
			handlers_cache_[state::fill_parent] = [this, padding](state_type s){
				auto parent = object_->parent();
				if (parent != nullptr)//Update bounding rectangle
					object_->dimensions(parent->dimensions(true).get_deflated(padding), false);
			};
		}
		else//Use handler
			handlers_cache_[state::fill_parent] = handler;

		object_->attribute_set_(state::fill_parent);
		(handlers_cache_[state::fill_parent])(state::fill_parent);//Trigger
	}
	else{//Disable
		GRAFEEX_REMOVE(active_states_, state::fill_parent);
		handlers_cache_.erase(state::fill_parent);
		object_->attribute_removed_(state::fill_parent);
	}

	return *this;
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_parent(const float_size_type &size, const rect_type &padding){
	return fill_parent(true, [=](state_type){
		auto parent = object_->parent();
		if (parent != nullptr){//Update bounding rectangle
			auto object_size = object_->size(false);
			auto parent_size = parent->size(true);

			size_type computed_size{
				(size.width() < 0.0f) ? object_size.width() : static_cast<size_type::field_type>(parent_size.width() *size.width()),
				(size.height() < 0.0f) ? object_size.height() : static_cast<size_type::field_type>(parent_size.height() *size.height())
			};

			object_->dimensions(rect_type(point_type{}, computed_size).get_deflated(padding), false);
		}
	});
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_parent_width(const rect_type &padding){
	return fill_parent(true, [=](state_type){
		auto parent = object_->parent();
		if (parent != nullptr){//Update bounding rectangle
			object_->dimensions(rect_type(point_type{}, size_type{ parent->size(true).width(),
				object_->size().height() }).get_deflated(padding), false);
		}
	});
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_parent_height(const rect_type &padding){
	return fill_parent(true, [=](state_type){
		auto parent = object_->parent();
		if (parent != nullptr){//Update bounding rectangle
			object_->dimensions(rect_type(point_type{}, size_type{ object_->size().width(),
				parent->size(true).height() }).get_deflated(padding), false);
		}
	});
}

bool grafeex::gui::object_attributes::parent_filled() const{
	return GRAFEEX_IS(active_states_, state::fill_parent);
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_content_once(const rect_type &padding){
	return *this;
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::fill_content(bool enabled, handler_type handler, const rect_type &padding){
	object_tree::guard_type guard(object_->lock_);
	if (enabled == content_filled())
		return *this;

	if (enabled){
		GRAFEEX_SET(active_states_, state::fill_content);
		if (handler == nullptr){
			handlers_cache_[state::fill_content] = [this, padding](state_type s){

			};
		}
		else//Use handler
			handlers_cache_[state::fill_content] = handler;

		object_->attribute_set_(state::fill_content);
		(handlers_cache_[state::fill_content])(state::fill_parent);//Trigger
	}
	else{//Disable
		GRAFEEX_REMOVE(active_states_, state::fill_content);
		handlers_cache_.erase(state::fill_content);
		object_->attribute_removed_(state::fill_content);
	}

	return *this;
}

bool grafeex::gui::object_attributes::content_filled() const{
	return GRAFEEX_IS(active_states_, state::fill_content);
}

grafeex::gui::object_attributes &grafeex::gui::object_attributes::align(bool enabled, alignment_type alignment,
	handler_type handler, const size_type &offset){
	object_tree::guard_type guard(object_->lock_);
	if (enabled == aligned())
		return *this;

	if (enabled){
		GRAFEEX_SET(active_states_, state::align);
		if (handler == nullptr){
			handlers_cache_[state::align] = [this, alignment, offset](state_type s){
				object_->align(alignment, offset);
			};
		}
		else//Use handler
			handlers_cache_[state::align] = handler;

		object_->attribute_set_(state::align);
		(handlers_cache_[state::align])(state::align);//Trigger
	}
	else{//Disable
		GRAFEEX_REMOVE(active_states_, state::align);
		handlers_cache_.erase(state::align);
		object_->attribute_removed_(state::align);
	}

	return *this;
}

bool grafeex::gui::object_attributes::aligned() const{
	return GRAFEEX_IS(active_states_, state::align);
}

void grafeex::gui::object_attributes::trigger_(state_type states){
	if (GRAFEEX_IS(states, state::fill_parent))
		(handlers_cache_[state::fill_parent])(state::fill_parent);

	if (GRAFEEX_IS(states, state::fill_content))
		(handlers_cache_[state::fill_content])(state::fill_content);

	if (GRAFEEX_IS(states, state::align))
		(handlers_cache_[state::align])(state::align);
}
