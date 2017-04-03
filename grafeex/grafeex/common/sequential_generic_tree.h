#pragma once

#ifndef GRAFEEX_SEQUENTIAL_GENERIC_TREE_H
#define GRAFEEX_SEQUENTIAL_GENERIC_TREE_H

#include <mutex>

#include "generic_tree.h"

namespace grafeex{
	namespace common{
		template <class child_type, class sibling_type>
		class sequential_generic_tree : public generic_tree<child_type, sibling_type>{
		public:
			typedef generic_tree<child_type, sibling_type> base_type;

			typedef std::recursive_mutex lock_type;
			typedef std::lock_guard<lock_type> guard_type;

			using base_type::add;
			using base_type::get_child;

			virtual ~sequential_generic_tree(){
				destroy();
			}

			virtual bool destroy() override{
				guard_type guard(lock_);
				return base_type::destroy();
			}

			virtual index_type add(child_type &child) override{
				guard_type guard(lock_);
				return base_type::add(child);
			}

			virtual index_type add(child_type &child, index_type index) override{
				guard_type guard(lock_);
				return base_type::add(child, index);
			}

			virtual generic_tree &remove(child_type &child) override{
				guard_type guard(lock_);
				return base_type::remove(child);
			}

			virtual generic_tree &remove(index_type index) override{
				guard_type guard(lock_);
				return base_type::remove(index);
			}

			virtual generic_tree &traverse_children(traverser_type traverser) override{
				guard_type guard(lock_);
				return base_type::traverse_children(traverser);
			}

			virtual const generic_tree &traverse_children(const_traverser_type traverser) const override{
				guard_type guard(lock_);
				return base_type::traverse_children(traverser);
			}

			virtual child_type *get_child(index_type index) const override{
				guard_type guard(lock_);
				return base_type::get_child(index);
			}

			virtual index_type get_child_index(const child_type &child) const override{
				guard_type guard(lock_);
				return base_type::get_child_index(child);
			}

			virtual bool is_child(const child_type &object) const override{
				guard_type guard(lock_);
				return base_type::is_child(object);
			}

			virtual bool is_offspring(const child_type &object) const override{
				guard_type guard(lock_);
				return base_type::is_offspring(object);
			}

		protected:
			mutable lock_type lock_;
		};
	}
}

#endif /* !GRAFEEX_SEQUENTIAL_GENERIC_TREE_H */
