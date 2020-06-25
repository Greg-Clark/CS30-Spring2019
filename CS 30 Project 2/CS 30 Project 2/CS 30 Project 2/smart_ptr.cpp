//
//  smart_ptr.cpp
//  CS 30 Project 2
//
//  Created by Gregory Clark on 3/25/19.
//  Copyright © 2019 Gregory Clark. All rights reserved.
//

#include <iostream>
#include <exception>
using namespace std;

class null_ptr_exception : public exception {
	const char *what() const noexcept override { //could also use throw()
		return "nullptr exception";
	}
};

template <typename T>
class smart_ptr {
public:
	smart_ptr() noexcept;
	// Create a smart_ptr that is initialized to nullptr. The reference count
	// should be initialized to nullptr.
	
	explicit smart_ptr(T* &raw_ptr);
	// Create a smart_ptr that is initialized to raw_ptr. The reference count
	// should be one. No change is made to raw_ptr.
	
	explicit smart_ptr(T* &&raw_ptr);
	// Create a smart_ptr that is initialized to raw_ptr. The reference count
	// should be one. If the constructor fails raw_ptr is deleted.
	
	smart_ptr(const smart_ptr& rhs) noexcept;
	// Copy construct a pointer from rhs. The reference count should be
	// incremented by one.
	
	smart_ptr(smart_ptr&& rhs) noexcept;
	// Move construct a pointer from rhs.
	
	smart_ptr& operator=(const smart_ptr& rhs) noexcept;
	// This assignment should make a shallow copy of the right-hand side's
	// pointer data. The reference count should be incremented as appropriate.
	
	smart_ptr& operator=(smart_ptr&& rhs) noexcept;
	// This move assignment should steal the right-hand side's pointer data.
	
	bool clone();
	// If the smart_ptr is either nullptr or has a reference count of one, this
	// function will do nothing and return false. Otherwise, the referred to
	// object's reference count will be decreased and a new deep copy of the
	// object will be created. This new copy will be the object that this
	// smart_ptr points and its reference count will be one.
	
	int ref_count() const noexcept;
	// Returns the reference count of the pointed to data.
	
	T& operator*();
	// The dereference operator shall return a reference to the referred object.
	// Throws null_ptr_exception on invalid access.
	
	T* operator->();
	// The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
	// on invalid access.
	
	~smart_ptr() noexcept;         // deallocate all dynamic memory
	
private:
	T* ptr_;               // pointer to the referred object
	int* ref_;             // pointer to a reference count
};




template <typename T>
smart_ptr<T>::smart_ptr() noexcept : ptr_(nullptr), ref_(nullptr) { }
// Create a smart_ptr that is initialized to nullptr. The reference count
// should be initialized to nullptr.

template <typename T>
smart_ptr<T>::smart_ptr(T* &raw_ptr)
{
	ptr_ = raw_ptr;
	ref_ = new int {1};
}
// Create a smart_ptr that is initialized to raw_ptr. The reference count
// should be one. No change is made to raw_ptr.

template <typename T>
smart_ptr<T>::smart_ptr(T* &&raw_ptr)
{
	try {
	ptr_ = std::move(raw_ptr);
	ref_ = new int {1};
	}
	catch(bad_alloc)
	{
		delete raw_ptr;
		throw;
	}
}
// Create a smart_ptr that is initialized to raw_ptr. The reference count
// should be one. If the constructor fails raw_ptr is deleted.

template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs) noexcept{
	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;
	if(ref_ != nullptr)
		(*ref_)++;
}
// Copy construct a pointer from rhs. The reference count should be
// incremented by one.

template <typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& rhs) noexcept{
	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;
	rhs.ptr_ = nullptr;
	rhs.ref_ = nullptr;
}
// Move construct a pointer from rhs.

template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& rhs) noexcept{
	if(ref_ != nullptr && *ref_ == 1)	//used to prevent a bad access of checking
		delete ptr_;	//a nullptr to an int and deletes object is only one thing is poiting to it
	if(ref_ != nullptr)
		(*ref_)--;			//decreases the count in the previous one by 1
	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;
	if(ref_ != nullptr)
		(*ref_)++;
	return *this;
}
// This assignment should make a shallow copy of the right-hand side's
// pointer data. The reference count should be incremented as appropriate.

template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& rhs) noexcept{
	if(ref_ != nullptr && *ref_ == 1)	//used to prevent a bad access of checking
		delete ptr_;					//a nullptr to an int
	if(ref_ != nullptr)
		(*ref_)--;			//decreases the count in the previous one by 1
	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;
	rhs.ptr_ = nullptr;
	rhs.ref_ = nullptr;
	return *this;
}
// This move assignment should steal the right-hand side's pointer data.

template <typename T>
bool smart_ptr<T>::clone(){
	if(ptr_ == nullptr || (ref_ != nullptr && *ref_ == 1)) 	//used to prevent a bad access of checking
		return false;										//a nullptr to an int
	T* temp = ptr_;
	int* tempInt = ref_;
	(*ref_)--;
	try{
		ptr_ = new T;
		ref_ = new int{1};
		*ptr_ = *temp;
		return true;
	}
	catch(bad_alloc){
		delete ptr_;		//deletes the pointers that were tried to be created
		delete ref_;		//but didn't quite make it due to bad_alloc
		ptr_ = temp;
		ref_ = tempInt;
		throw;
	}
}
// If the smart_ptr is either nullptr or has a reference count of one, this
// function will do nothing and return false. Otherwise, the referred to
// object's reference count will be decreased and a new deep copy of the
// object will be created. This new copy will be the object that this
// smart_ptr points and its reference count will be one.

template <typename T>
int smart_ptr<T>::ref_count() const noexcept
{
	if(ref_ == nullptr)
		return 0;
	return *ref_;
}
// Returns the reference count of the pointed to data.

template <typename T>
T& smart_ptr<T>::operator*(){
	if(ptr_ == nullptr)
		throw null_ptr_exception();
	return *ptr_;
}
// The dereference operator shall return a reference to the referred object.
// Throws null_ptr_exception on invalid access.

template <typename T>
T* smart_ptr<T>::operator->(){
	if(ptr_ == nullptr)
		throw null_ptr_exception();
	return ptr_;
}
// The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
// on invalid access.

template <typename T>
smart_ptr<T>::~smart_ptr() noexcept        // deallocate all dynamic memory
{
	if(ref_ != nullptr && ptr_ != nullptr)	//used to prevent a bad access of checking
	{										//a nullptr to an int and if ptr_ is
		if(*ref_ == 1)						//already pointing to null, no destructing
		{									//is needed
			delete ptr_;
			delete ref_;
		}
		else{
			(*ref_)--;
		}
	}
}

int main() {
	return 0;
}
