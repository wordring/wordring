﻿#pragma once

#include <deque>
#include <iterator>

namespace wordring
{
	template <typename Iterator, typename Allocator>
	class tree_iterator_stack
	{
	public:
		explicit tree_iterator_stack(Allocator const& alloc = Allocator())
			: m_stack(alloc)
		{
		}

		explicit tree_iterator_stack(Iterator const& base, Allocator const& alloc = Allocator())
			: m_stack(1, base, alloc)
		{
		}
		
		tree_iterator_stack(Iterator first, Iterator last, Allocator const& alloc = Allocator())
			: m_stack(alloc)
		{
			while (first != last) m_stack.push_back(first++);
		}

		Iterator& top() const { return const_cast<std::deque<Iterator>&>(m_stack).front(); }

		void pop() { m_stack.erase(m_stack.begin()); }

		void push(Iterator const& it) { m_stack.push_front(it); }

		void push(Iterator first, Iterator last)
		{
			auto pos = m_stack.begin();
			while(first != last) pos = ++m_stack.insert(pos, first++);
		}

		bool empty() const { return m_stack.empty(); }

	private:
		std::deque<Iterator> m_stack;
	};

	template <typename Iterator, typename Allocator>
	class tree_iterator_queue
	{
	public:
		explicit tree_iterator_queue(Allocator const& alloc = Allocator())
			: m_queue(alloc)
		{
		}

		explicit tree_iterator_queue(Iterator const& base, Allocator const& alloc = Allocator())
			: m_queue(1, base, alloc)
		{
		}

		tree_iterator_queue(Iterator first, Iterator last, Allocator const& alloc = Allocator())
			: m_queue(alloc)
		{
			while (first != last) m_queue.push_back(first++);
		}

		Iterator& top() const
		{
			return const_cast<std::deque<Iterator>&>(m_queue).front(); }

		void pop() { m_queue.erase(m_queue.begin()); }

		void push(Iterator const& it) { m_queue.push_back(it); }

		void push(Iterator first, Iterator last)
		{
			while(first != last) m_queue.push_back(first++);
		}

		bool empty() const { return m_queue.empty(); }

	private:
		std::deque<Iterator> m_queue;
	};

	template <typename Iterator, typename Container, typename Allocator>
	class basic_tree_iterator
	{
		template <typename Iterator1, typename Container1, typename Allocator1>
		friend bool operator==(basic_tree_iterator<Iterator1, Container1, Allocator1> const&, basic_tree_iterator<Iterator1, Container1, Allocator1> const&);

		template <typename Iterator1, typename Container1, typename Allocator1>
		friend bool operator!=(basic_tree_iterator<Iterator1, Container1, Allocator1> const&, basic_tree_iterator<Iterator1, Container1, Allocator1> const&);

	public:
		using base_type       = Iterator;
		using allocator_type  = Allocator;

		using value_type        = typename base_type::value_type;
		using difference_type   = std::ptrdiff_t;
		using reference         = value_type&;
		using pointer           = value_type*;
		using iterator_category = std::input_iterator_tag;

		using container = Container;

	public:
		explicit basic_tree_iterator(allocator_type const& alloc = allocator_type())
			: m_container(alloc)
		{
		}

		explicit basic_tree_iterator(base_type const& it, allocator_type const& alloc = allocator_type())
			: m_container(it, alloc)
		{
		}
		
		basic_tree_iterator(base_type const& first, base_type const& last, allocator_type const& alloc = allocator_type())
			: m_container(first, last, alloc)
		{
		}

		basic_tree_iterator(basic_tree_iterator const&) = default;

		basic_tree_iterator(basic_tree_iterator&&) = default;

		basic_tree_iterator& operator=(basic_tree_iterator const& rhs) = default;

		basic_tree_iterator& operator=(basic_tree_iterator&& rhs) = default;

		base_type base() const { return m_container.top(); }

		reference operator*() const { return *m_container.top(); }

		pointer operator->() const { return m_container.top().operator->(); }

		basic_tree_iterator& operator++()
		{
			base_type it = m_container.top();
			m_container.pop();
			m_container.push(it.begin(), it.end());
			return *this;
		}

		base_type operator++(int)
		{
			base_type result = m_container.top();
			operator++();
			return result;
		}
		
	private:
		container m_container;
	};

	template <typename Iterator1, typename Container1, typename Allocator1>
	inline bool operator==(basic_tree_iterator<Iterator1, Container1, Allocator1> const& lhs, basic_tree_iterator<Iterator1, Container1, Allocator1> const& rhs)
	{
		return (lhs.m_container.empty() && rhs.m_container.empty())
			|| (!lhs.m_container.empty() && !rhs.m_container.empty() && lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Container1, typename Allocator1>
	inline bool operator!=(basic_tree_iterator<Iterator1, Container1, Allocator1> const& lhs, basic_tree_iterator<Iterator1, Container1, Allocator1> const& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator, typename  Allocator = std::allocator<Iterator>>
	using tree_iterator = basic_tree_iterator<Iterator, tree_iterator_stack<Iterator, Allocator>, Allocator>;

	template <typename Iterator, typename  Allocator = std::allocator<Iterator>>
	using level_order_tree_iterator = basic_tree_iterator<Iterator, tree_iterator_queue<Iterator, Allocator>, Allocator>;
}