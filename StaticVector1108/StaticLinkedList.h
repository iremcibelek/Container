#pragma once

#include <cstddef>

template <typename T>
class StaticLinkedList {
private:

    struct Node {
        T data;
        Node* next;
        bool used;
    };

    Node* list;
    std::size_t capacity_;
    Node* head = nullptr;
    std::size_t count = 0;

public:
    explicit StaticLinkedList(std::size_t capacity);
    ~StaticLinkedList();

    bool push_front(const T& value);
    bool push_back(const T& value);

    bool pop_front();
    bool pop_back();

    bool insertByIndex(std::size_t index, const T& value);
    bool eraseByIndex(std::size_t index);
    bool eraseByData(const T& value);

    std::size_t size() const;
    bool isEmpty() const;
    bool isFull() const;
    std::size_t capacity() const;

    T* front();
    const T* front() const;

    T* back();
    const T* back() const;

    void clear();

    bool exists(const T& value) const;
    std::size_t find(const T& value) const;

    void reverse();
};