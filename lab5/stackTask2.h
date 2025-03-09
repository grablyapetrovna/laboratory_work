#ifndef STACK_TASK2_H
#define STACK_TASK2_H

#include <stdexcept>
#include <utility>

template <typename T>
class LinkedStack {
private:
    struct Node {
        T value;
        Node* next;

        template <typename... Args>
        Node(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr) {}
    };

    Node* topNode;

public:
    LinkedStack() : topNode(nullptr) {}

    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    LinkedStack(LinkedStack&& other) noexcept : topNode(other.topNode) {
        other.topNode = nullptr;
    }

    LinkedStack& operator=(LinkedStack&& other) noexcept {
        if (this != &other) {
            while (topNode) {
                Node* temp = topNode;
                topNode = topNode->next;
                delete temp;
            }
            topNode = other.topNode;
            other.topNode = nullptr;
        }
        return *this;
    }

    ~LinkedStack() {
        while (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    template <typename... Args>
    void push_emplace(Args&&... args) {
        Node* newNode = new Node(std::forward<Args>(args)...);
        newNode->next = topNode;
        topNode = newNode;
    }

    void push(T&& value) {
        Node* newNode = new Node(std::move(value));
        newNode->next = topNode;
        topNode = newNode;
    }

    const T& head() const {
        if (!topNode) {
            throw std::out_of_range("Stack is empty");
        }
        return topNode->value;
    }

    T pop() {
        if (!topNode) {
            throw std::out_of_range("Stack is empty");
        }
        Node* temp = topNode;
        T value = std::move(temp->value);
        topNode = topNode->next;
        delete temp;
        return value;
    }

    bool empty() const {
        return topNode == nullptr;
    }
};

#endif // STACK_TASK2_H
