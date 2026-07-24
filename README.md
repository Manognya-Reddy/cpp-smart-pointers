# cpp-smart-pointers

Simple implementation of UniquePtr and SharedPtr to understand RAII and memory ownership.

## Why RAII exists

RAII means Resource Acquisition Is Initialization. Basically you tie a resource (memory, file handle, lock, whatever) to the lifetime of an object. When the object is constructed it grabs the resource, and when it goes out of scope the destructor automatically releases it. This way you don't have to remember to call delete/free/close yourself, the compiler does it for you when the object dies. Less chances of forgetting to clean up.

## Why raw pointers are dangerous

- You can forget to delete them -> memory leak
- You can delete them twice -> undefined behavior / crash
- You can use them after they've been deleted -> dangling pointer
- No way to know who "owns" the pointer, so multiple parts of code might try to delete the same thing
- If an exception is thrown before you reach the delete line, the memory never gets freed

Smart pointers fix this by wrapping the raw pointer and handling delete automatically in the destructor.

## Why shared_ptr is slower

SharedPtr has to maintain a reference count. Every time you copy a SharedPtr, it has to increment a counter, and every time one is destroyed it decrements the counter (and this needs to be thread safe in real implementations, so atomic operations are used which have overhead). UniquePtr doesn't need any of this since only one object owns the pointer at a time, so there's no counting involved, it's basically free compared to shared_ptr.

## How reference counting works

Every SharedPtr that points to the same object shares the same counter (I used a separate RefCount struct on the heap for this). When you copy a SharedPtr, the count goes up by 1. When a SharedPtr is destroyed or reassigned, count goes down by 1. When the count hits 0, that means no more SharedPtrs are pointing to the object, so it's safe to actually delete it.

## How to run

```
g++ -std=c++11 -Iinclude tests/test_smartptr.cpp -o test_run
./test_run
```
