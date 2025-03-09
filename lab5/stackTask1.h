#ifndef STACK_TASK1_H
#define STACK_TASK1_H

#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Stack() : data(nullptr), capacity(0), size(0) {}

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    Stack(Stack&& other) noexcept : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;

            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void push(T&& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = std::move(value);
    }

    template <typename... Args>
    void push_emplace(Args&&... args) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = T(std::forward<Args>(args)...);
    }

    T pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return std::move(data[--size]);
    }

    const T& head() const {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[size - 1];
    }

    bool empty() const {
        return size == 0;
    }
};

#endif // STACK_TASK1_H
