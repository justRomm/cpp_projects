// SharedPtr.hpp

#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

template<typename Resource>
class WeakPtr;

template <typename Resource>
class SharedPtr
{
	friend class WeakPtr<Resource>;
private:
	Resource* ptr_;
	int* count_;

	void Release();
public:
	SharedPtr();
	explicit SharedPtr(Resource* res);
	SharedPtr(const SharedPtr<Resource>& rhs);
	SharedPtr(const WeakPtr<Resource>& rhs);
	SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
	virtual ~SharedPtr();

	void Reset();
	void Reset(Resource* res);
	void Swap(SharedPtr<Resource>& rhs);

	Resource* Get() const;
	Resource& operator*() const;
	Resource* operator->() const;
	long UseCount() const;
};

template<typename Resource>
void SharedPtr<Resource>::Release()
{
    if (count_ != nullptr && --(*count_) == 0)
    {
        delete count_;
        delete ptr_;
    }
}

template<typename Resource>
SharedPtr<Resource>::SharedPtr()
    : ptr_(nullptr)
    , count_(nullptr)
{
}

template<typename Resource>
inline SharedPtr<Resource>::SharedPtr(Resource* res)
    : ptr_(res)
    , count_(new int(1))
{}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(const SharedPtr<Resource>& rhs)
    : ptr_(rhs.ptr_)
    , count_(rhs.count_)
{
    if (count_ != nullptr)
    {
        ++(*count_);
    }
}

template<typename Resource>
SharedPtr<Resource>::SharedPtr(const WeakPtr<Resource>& rhs)
    : ptr_(rhs.ptr_)
    , count_(rhs.count_)
{
    if (count_ != nullptr) {
        ++(*count_);
    }
}

template<typename Resource>
SharedPtr<Resource>& SharedPtr<Resource>::operator=(const SharedPtr<Resource>& rhs)
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
SharedPtr<Resource>::~SharedPtr()
{
    Release();
}

template<typename Resource>
void SharedPtr<Resource>::Reset()
{
    Release();
    count_ = new int(0);
    ptr_ = nullptr;
}

template<typename Resource>
void SharedPtr<Resource>::Reset(Resource* res)
{
    Release();
    ptr_ = res;
    count_ = new int(0);
}

template<typename Resource>
void SharedPtr<Resource>::Swap(SharedPtr<Resource>& rhs)
{
    Resource* tmp_ptr = ptr_;
    int* tmp_count = count_;
    ptr_ = rhs.ptr_;
    count_ = rhs.count_;
    rhs.ptr_ = tmp_ptr;
    rhs.count_ = tmp_count;
}

template<typename Resource>
Resource* SharedPtr<Resource>::Get() const
{
    return ptr_;
}

template<typename Resource>
Resource& SharedPtr<Resource>::operator*() const
{
    return *ptr_;
}

template<typename Resource>
Resource* SharedPtr<Resource>::operator->() const
{
    return ptr_;
}

template<typename Resource>
long SharedPtr<Resource>::UseCount() const
{
    return (count_ != nullptr) ? *count_ : 0;
}

#endif // SHAREDPTR_HPP