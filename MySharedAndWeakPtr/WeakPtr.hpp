// WeakPtr.hpp

#ifndef WEAKPTR_HPP
#define WEAKPTR_HPP

template<typename Resource>
class SharedPtr;

template<typename Resource>
class WeakPtr
{
private:
	Resource* ptr_;
	int* count_;

	void Release();
public:
	WeakPtr();
	WeakPtr(const WeakPtr<Resource>& rhs);
	WeakPtr(const SharedPtr<Resource>& rhs);
	WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs);
	WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
	virtual ~WeakPtr();

	void Reset();
	void Swap(WeakPtr<Resource>& rhs);
	long UseCount() const;
	bool Expired() const;
	SharedPtr<Resource> Lock() const;
};

template<typename Resource>
void WeakPtr<Resource>::Release()
{
	if (count_) {
		--(*count_);
		if (*count_ == 0) {
			delete count_;
			delete ptr_;
		}
		count_ = nullptr;
		ptr_ = nullptr;
	}
}

template<typename Resource>
WeakPtr<Resource>::WeakPtr()
	: ptr_(nullptr)
	, count_(nullptr)
{
}

template<typename Resource>
WeakPtr<Resource>::WeakPtr(const WeakPtr<Resource>& rhs)
	: ptr_(rhs.ptr_)
	, count_(rhs.count_)
{
	if (count_ != nullptr)
		++(*count_);
}

template<typename Resource>
WeakPtr<Resource>::WeakPtr(const SharedPtr<Resource>& rhs)
	: ptr_(rhs.ptr_)
	, count_(rhs.count_)
{
	if (count_ != nullptr)
		++(*count_);
}

template<typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const WeakPtr<Resource>& rhs)
{
	if (this != &rhs) {
		Release();
		ptr_ = rhs.ptr_;
		count_ = rhs.count_;
		if (count_ != nullptr) {
			++(*count_);
		}
	}
	return *this;
}

template<typename Resource>
WeakPtr<Resource>& WeakPtr<Resource>::operator=(const SharedPtr<Resource>& rhs)
{
	Release();
	ptr_ = rhs.ptr_;
	count_ = rhs.count_;
	if (count_ != nullptr) {
		++(*count_);
	}
	return *this;
}

template<typename Resource>
WeakPtr<Resource>::~WeakPtr()
{
	Release();
}

template<typename Resource>
void WeakPtr<Resource>::Reset()
{
	Release();
	ptr_ = nullptr;
	count_ = nullptr;
}

template<typename Resource>
void WeakPtr<Resource>::Swap(WeakPtr<Resource>& rhs)
{
	Resource* tmp_ptr = ptr_;
	int* tmp_count = count_;
	ptr_ = rhs.ptr_;
	count_ = rhs.count_;
	rhs.ptr_ = tmp_ptr;
	rhs.count_ = tmp_count;
}

template<typename Resource>
long WeakPtr<Resource>::UseCount() const
{
	return (count_ != nullptr) ? *count_ : 0;
}

template<typename Resource>
bool WeakPtr<Resource>::Expired() const
{
	return UseCount() == 0;
}

template<typename Resource>
SharedPtr<Resource> WeakPtr<Resource>::Lock() const
{
	SharedPtr<Resource> shared;
	if (count_ && *count_ > 0) {
		shared.ptr_ = ptr_;
		shared.count_ = count_;
		++(*count_);
	}
	return shared;
}


#endif // WEAKPTR_HPP