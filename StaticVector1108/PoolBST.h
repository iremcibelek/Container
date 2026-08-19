#pragma once

#include <cstddef>

template <typename T, std::size_t Capacity>
class PoolBST {
public:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
    };

private:
    Node objects[Capacity];
    bool used[Capacity]{};

public:
    PoolBST() = default;
    ~PoolBST() = default;

    PoolBST(const PoolBST&) = delete;
    PoolBST& operator=(const PoolBST&) = delete;

    Node* acquire();
    void release(Node* object);
    std::size_t returnCapacity() const;
};