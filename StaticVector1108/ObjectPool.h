#pragma once

#include <cstddef>

template <typename T,std::size_t Capacity>
class ObjectPool {
public:
    struct Node {
        T data;
        Node* next = nullptr;
    };

private:
    Node objects[Capacity];
    bool used[Capacity]{};

public:
     ObjectPool();
    ~ObjectPool()=default;

    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

    Node* acquire();
    void release(Node* object);
    std::size_t returnCapacity() const;
};