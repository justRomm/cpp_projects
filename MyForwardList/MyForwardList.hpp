

// Windows 11, Microsoft Visual Studio 2022, C++17


// MyForwardList.hpp

#ifndef MYFORWARDLIST_HPP
#define MYFORWARDLIST_HPP

#include <memory>
#include <exception>


template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node() = default;
};

template<typename T>
class MyForwardList
{
public:
	using Allocator = std::allocator<T>;
	class iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator() 
			: node_(nullptr) 
		{}
		explicit iterator(Node<T>* node) 
			: node_(node) 
		{}

		iterator& operator++()
		{
			node_ = node_->next;
			return *this;
		}

		T& operator*() const
		{
			return node_->data;
		}

		bool operator!=(const iterator& other) const
		{
			return node_ != other.node_;
		}

	private:
		Node<T>* node_;
	};

	class const_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = const T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		const_iterator() 
			: node_(nullptr) 
		{}
		explicit const_iterator(const Node<T>* node)
			: node_(node) 
		{}
		const_iterator(const iterator& other) 
			: node_(other.node_) 
		{}

		const_iterator& operator++()
		{
			node_ = node_->next;
			return *this;
		}

		const T& operator*() const
		{
			return node_->data;
		}

		bool operator!=(const const_iterator& other) const
		{
			return node_ != other.node_;
		}

	private:
		const Node<T>* node_;
	};

	MyForwardList();
	explicit MyForwardList(const Allocator& alloc);
	MyForwardList(size_t count, const T& value, const Allocator& alloc = Allocator());
	MyForwardList(std::initializer_list<T> init, const Allocator& alloc = Allocator());
	MyForwardList<T> operator=(const MyForwardList<T>& other);

	iterator beforeBegin();
	const_iterator beforeBegin() const;
	const_iterator cbeforeBegin() const;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	bool empty() const;
	void clear();
	size_t size() const;
	void pushFront(const T& value);
	void popFront();
	T front();
	T front() const;
	Allocator getAllocator() const { return alloc_; }

	void assign(size_t count, const T& value);
	void assign(std::initializer_list<T> init);

	virtual ~MyForwardList();

private:
	Node<T>* front_;
	size_t count_;
	Allocator alloc_;
};



template<typename T>
MyForwardList<T>::MyForwardList()
	: front_(nullptr)
	, count_(0)
	, alloc_()
{}

template<typename T>
MyForwardList<T>::MyForwardList(const Allocator & alloc)
	: front_(nullptr)
	, count_(0)
	, alloc_(alloc)
{}

template<typename T>
MyForwardList<T>::MyForwardList(size_t count, const T & value, const Allocator & alloc)
	: front_(nullptr)
	, count_(0)
	, alloc_(alloc)
{
	for (size_t i = 0; i < count; ++i)
	{
		pushFront(value);
	}
}

template<typename T>
inline MyForwardList<T>::MyForwardList(std::initializer_list<T> init, const Allocator& alloc)
	: front_(nullptr)
	, count_(0)
	, alloc_(alloc)
{
	for (const auto& value : init)
	{
		pushFront(value);
	}
}

template<typename T>
MyForwardList<T> MyForwardList<T>::operator=(const MyForwardList<T>& other)
{
	if (this != other) {
		clear();
		Node<T>* current = other.front_;
		while (current != nullptr)
		{
			push_back(current->data);
			current = current->next;
		}
	}
	return *this;
}

template<typename T>
typename MyForwardList<T>::iterator MyForwardList<T>::beforeBegin()
{
	Node<T>* tmp = new Node<T>;
	tmp->next = front_;
	return iterator(tmp);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::beforeBegin() const
{
	Node<T>* tmp = new Node<T>;
	tmp->next = front_;
	return const_iterator(tmp);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::cbeforeBegin() const
{
	Node<T>* tmp = new Node<T>;
	tmp->next = front_;
	return const_iterator(tmp);
}

template<typename T>
typename MyForwardList<T>::iterator MyForwardList<T>::begin()
{
	return iterator(front_);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::begin() const
{
	return const_iterator(front_);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::cbegin() const
{
	return const_iterator(front_);
}

template<typename T>
typename MyForwardList<T>::iterator MyForwardList<T>::end()
{
	return iterator(nullptr);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::end() const
{
	return const_iterator(nullptr);
}

template<typename T>
typename MyForwardList<T>::const_iterator MyForwardList<T>::cend() const
{
	return const_iterator(nullptr);
}

template<typename T>
void MyForwardList<T>::pushFront(const T& value)
{
	if (!front_) {
		Node<T>* tmp = new Node<T>;
		tmp->data = value;
		tmp->next = nullptr;
		front_ = tmp;
		count_++;
	}
	else {
		Node<T>* tmp = new Node<T>;
		tmp->data = value;
		tmp->next = front_;
		front_ = tmp;
		count_++;
	}
}

template<typename T>
void MyForwardList<T>::popFront()
{
	if (empty()) {
		throw std::exception("List is empty.\n");
	}
	Node<T>* tmp = front_;
	front_ = front_->next;
	delete tmp;
	count_--;
}

template<typename T>
T MyForwardList<T>::front()
{
	if (empty()) {
		throw std::exception("List is empty.\n");
	}
	return front_->data;
}

template<typename T>
T MyForwardList<T>::front() const
{
	if (empty()) {
		throw std::exception("List is empty.\n");
	}
	return front_->data;
	
}

template<typename T>
void MyForwardList<T>::assign(size_t count, const T& value)
{
	clear();
	for (size_t i = 0; i < count; ++i)
	{
		push_back(value);
	}
}

template<typename T>
void MyForwardList<T>::assign(std::initializer_list<T> init)
{
	clear();
	for (const auto& value : init)
	{
		pushFront(value);
	}
}

template<typename T>
inline MyForwardList<T>::~MyForwardList()
{
	clear();
}

template<typename T>
inline bool MyForwardList<T>::empty() const
{
	return size() == 0;
}

template<typename T>
void MyForwardList<T>::clear()
{
	if (!empty()) {
		Node<T>* tmp;
		while (front_ != nullptr)
		{
			tmp = front_;
			front_ = front_->next;
			delete tmp;
		}
	}
	count_ = 0;
}

template<typename T>
inline size_t MyForwardList<T>::size() const
{
	return count_;
}


#endif // MYFORWARDLIST_HPP