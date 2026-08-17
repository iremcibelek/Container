#pragma once

#include <cstddef>

class StaticLinkedList {
private:
    static constexpr std::size_t Capacity = 10;

    struct Node {
        int data;
        Node* next;
        bool used;
    };

    Node list[Capacity]{};
    Node* head = nullptr;
    std::size_t count = 0;

public:
    bool push_front(const int& value);
    bool push_back(const int& value);

    bool pop_front();
    bool pop_back();

    bool insertByIndex(std::size_t index, const int& value);
    bool eraseByIndex(std::size_t index);
    bool eraseByData(const int& value);

    std::size_t size() const;
    bool isEmpty() const;
    bool isFull() const;
    std::size_t capacity() const;

    int* front();
    const int* front() const;

    int* back();
    const int* back() const;

    void clear();

    bool exists(const int& value) const;
    std::size_t find(const int& value) const;

    void reverse();
};

