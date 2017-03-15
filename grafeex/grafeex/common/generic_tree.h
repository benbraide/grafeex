#pragma once

#ifndef GRAFEEX_GENERIC_TREE_H
#define GRAFEEX_GENERIC_TREE_H

#include <list>
#include <functional>

namespace grafeex{
	namespace common{
		template <class child_type, class sibling_type>
		class generic_tree{
		public:
			typedef child_type child_type;
			typedef sibling_type sibling_type;

			typedef std::function<bool(child_type &)> traverser_type;
			typedef std::function<bool(const child_type &)> const_traverser_type;

			typedef std::list<child_type *> list_type;
			typedef typename list_type::size_type index_type;
			typedef typename list_type::size_type size_type;

			virtual ~generic_tree(){}

			virtual index_type add(child_type &child){
				children_.push_back(&child);
				return (children_.size() - 1);
			}

			virtual index_type add(child_type &child, const sibling_type &sibling){
				return add(child, sibling.get_insert_index());
			}

			virtual index_type add(child_type &child, index_type index){
				if (index >= children_.size()){//Append
					children_.push_back(&child);
					index = (children_.size() - 1);
				}
				else//Insert
					children_.insert(std::next(children_.begin(), index), &child);

				return index;
			}

			virtual generic_tree &remove(child_type &child){
				auto iter = std::find(children_.begin(), children_.end(), &child);
				if (iter != children_.end())
					children_.erase(iter);
				return *this;
			}

			virtual generic_tree &remove(index_type index){
				if (index < children_.size())
					children_.erase(std::next(children_.begin(), index), &child);
				return *this;
			}

			virtual generic_tree &traverse_children(traverser_type traverser){
				for (auto child : children_){
					if (!traverser(*child))
						break;
				}

				return *this;
			}

			virtual generic_tree &traverse_children(const_traverser_type traverser) const{
				for (auto child : children_){
					if (!traverser(*child))
						break;
				}

				return *this;
			}

			virtual const child_type *get_child(index_type index) const{
				if (index == static_cast<index_type>(-1))
					return children_.empty() ? nullptr : *children_.rbegin();

				if (index < children_.size())
					return *std::next(children_.begin(), index);

				return nullptr;
			}

			virtual child_type *get_child(index_type index){
				if (index == static_cast<index_type>(-1))
					return children_.empty() ? nullptr : *children_.rbegin();

				if (index < children_.size())
					return *std::next(children_.begin(), index);

				return nullptr;
			}

			virtual index_type get_child_index(const child_type &child) const{
				index_type index = 0;
				for (auto iter = children_.begin(); iter != children_.end(); ++iter, ++index){
					if (*iter == &child)
						return index;
				}

				return static_cast<index_type>(-1);
			}

			virtual bool is_child(const child_type &object) const{
				return (std::find(children_.begin(), children_.end(), &object) != children_.end());
			}

			virtual bool has_children() const{
				return !children_.empty();
			}

			virtual size_type get_children_count() const{
				return children_.size();
			}

		protected:
			list_type children_;
		};
	}
}

#endif /* !GRAFEEX_GENERIC_TREE_H */
