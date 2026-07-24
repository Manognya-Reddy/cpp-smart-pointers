#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>
using namespace std;

template <typename T>
class UniquePtr {
    T* ptr;
public:
    UniquePtr() {
        ptr = nullptr;
    }

    UniquePtr(T* p) {
        ptr = p;
    }

    ~UniquePtr() {
        if(ptr != NULL) {
            delete ptr;
        }
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other){
        if(this != &other)
        {
            if(ptr)
                delete ptr;
            ptr = other.ptr;
            other.ptr = NULL;
        }
        return *this;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->(){
        return ptr;
    }

    T* get() {
        return ptr;
    }

    T* release(){
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        if (ptr) delete ptr;
        ptr = p;
    }
};

template<typename T>
UniquePtr<T> make_unique(T val){
    return UniquePtr<T>(new T(val));
}


struct RefCount {
    int count;
    RefCount(){count=1;}
};

template <class T>
class SharedPtr {
    T* ptr;
    RefCount* rc;

public:
    SharedPtr() : ptr(nullptr), rc(nullptr) {}

    SharedPtr(T* p) {
        ptr = p;
        rc = new RefCount();
    }

    SharedPtr(const SharedPtr<T> &other) {
        ptr = other.ptr;
        rc = other.rc;
        if(rc != nullptr)
        rc->count++;
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        if(this == &other) return *this;

        if(rc && --rc->count == 0){
            delete ptr;
            delete rc;
        }

        ptr = other.ptr;
        rc = other.rc;
        if(rc)
            rc->count++;

        return *this;
    }

    ~SharedPtr(){
        if(rc){
            rc->count--;
            if(rc->count==0){
                delete ptr;
                delete rc;
            }
        }
    }

    int use_count(){
        if(rc==NULL) return 0;
        return rc->count;
    }

    T& operator*(){
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    T* get(){
        return ptr;
    }
};

template<typename T>
SharedPtr<T> make_shared(T val)
{
    T* p = new T(val);
    return SharedPtr<T>(p);
}

#endif
