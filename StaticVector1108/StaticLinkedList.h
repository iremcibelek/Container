#pragma once

#include <cstddef>
#include "ObjectPool.h"

template <typename T,std::size_t Capacity>
class StaticLinkedList {
public:
    using Node = typename ObjectPool<T,Capacity>::Node;

private:
    ObjectPool<T,Capacity>& pool;
    Node* head = nullptr;
    std::size_t count = 0;

public:
    explicit StaticLinkedList(ObjectPool<T,Capacity>& pool);
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