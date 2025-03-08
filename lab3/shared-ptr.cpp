#include <atomic>
#include <cstddef>  

template <typename T>
class SharedPtr {
private:
    T* ptr;                  
    std::atomic_uint* count; 

    void increment() {
        if (count) {
            ++(*count);
        }
    }

    void decrement() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

public:
    SharedPtr() : ptr(nullptr), count(nullptr) {}

    SharedPtr(T* p) : ptr(p), count(new std::atomic_uint(1)) {}

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
        increment();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            decrement(); 
            ptr = other.ptr;
            count = other.count;
            increment(); 
        }
        return *this;
    }

    ~SharedPtr() {
        decrement();
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    size_t use_count() const {
        return (count ? count->load() : 0); 
    }
};
