#pragma once

#include <cstddef>
#include "PoolBST.h"

template <typename T, std::size_t Capacity>
class BinarySearchTree {
public:
    using Node = typename PoolBST<T, Capacity>::Node;

private:
    PoolBST<T, Capacity>& pool;
    Node* root= nullptr;
    std::size_t count = 0;

    // Özyinelemeli (Recursive) yardýmcý fonksiyonlar
    Node* insertRec(Node* current, const T& value, bool& inserted);
    Node* eraseRec(Node* current, const T& value, bool& removed);
    Node* findMinNode(Node* current) const;
    Node* findMaxNode(Node* current) const;
    bool existsRec(Node* current, const T& value) const;
    void clearRec(Node* current);

public:
    explicit BinarySearchTree(PoolBST<T, Capacity>& pool);
    ~BinarySearchTree();


    bool insert(const T& value);
    bool erase(const T& value);

    std::size_t size() const;
    bool isEmpty() const;
    bool isFull() const;
    std::size_t capacity() const;

    T* min(); 
    const T* min() const;

    T* max(); // biggest
    const T* max() const;

    void clear();

    bool exists(const T& value) const;
};