#include "StaticLinkedList.h"

template<typename T,std::size_t Capacity>
StaticLinkedList<T, Capacity>::StaticLinkedList(ObjectPool <T,Capacity>& pool)
    : pool(pool), head(nullptr), count(0) {
}

template<typename T,std::size_t Capacity>
StaticLinkedList<T,Capacity>::~StaticLinkedList() {
    clear();
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::push_front(const T& value) {
    Node* newNode = pool.acquire();
    if (newNode == nullptr)
        return false;

    newNode->data = value;
    newNode->next = head;
    head = newNode;
    count++;

    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::push_back(const T& value) {
    Node* newNode = pool.acquire();
    if (newNode == nullptr)
        return false;

    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        count++;
        return true;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
    count++;
    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::pop_front() {
    if (head == nullptr)
        return false;

    Node* temp = head;
    head = head->next;

    pool.release(temp);
    count--;
    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::pop_back() {
    if (head == nullptr)
        return false;

    if (head->next == nullptr) {
        Node* temp = head;
        head = nullptr;
        pool.release(temp);
        count--;
        return true;
    }

    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    Node* toDelete = temp->next;
    temp->next = nullptr;
    pool.release(toDelete);
    count--;

    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::insertByIndex(std::size_t index, const T& value) {
    if (index > count)
        return false;

    if (index == 0)
        return push_front(value);

    if (index == count)
        return push_back(value);

    Node* newNode = pool.acquire();
    if (newNode == nullptr)
        return false;

    newNode->data = value;

    Node* temp = head;
    for (std::size_t i = 1; i < index; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    count++;
    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::eraseByIndex(std::size_t index) {
    if (index >= count)
        return false;

    if (index == 0)
        return pop_front();

    if (index == count - 1)
        return pop_back();

    Node* temp = head;
    for (std::size_t i = 1; i < index; i++) {
        temp = temp->next;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;

    pool.release(toDelete);
    count--;
    return true;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::eraseByData(const T& value) {
    if (head == nullptr)
        return false;

    if (head->data == value)
        return pop_front();

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == nullptr)
        return false;

    Node* toDelete = temp->next;
    temp->next = toDelete->next;

    pool.release(toDelete);
    count--;
    return true;
}

template<typename T,std::size_t Capacity>
std::size_t StaticLinkedList<T,Capacity>::size() const {
    return count;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::isEmpty() const {
    return count == 0;
}

template<typename T,std::size_t Capacity>
bool StaticLinkedList<T,Capacity>::isFull() const {
    return count == pool.returnCapacity();
}

template<typename T,std::size_t Capacity>
std::size_t StaticLinkedList<T,Capacity>::capacity() const {
    return pool.returnCapacity();
}

template<typename T,std::size_t Capacity>
T* StaticLinkedList<T,Capacity>::front() {
    return head ? &head->data : nullptr;
}

template<typename T,std::size_t Capacity>
const T* StaticLinkedList<T,Capacity>::front() const {
    return head ? &head->data : nullptr;
}

template<typename T,std::size_t Capacity>
T* StaticLinkedList<T,Capacity>::back() {
    if (head == nullptr)
        return nullptr;

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return &temp->data;
}

template<typename T,std::size_t Capacity>
const T* StaticLinkedList<T,Capacity>::back() const {
    if (head == nullptr)
        return nullptr;

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return &temp->data;
}

template<typename T,std::size_t Capacity>
void StaticLinkedList<T,Capacity>::clear() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        pool.release(temp);
        temp = nextNode;
    }
    head = nullptr;
    count = 0;
}

template<typename T, std::size_t Capacity>
bool StaticLinkedList<T, Capacity>::exists(const T& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

template<typename T,std::size_t Capacity>
std::size_t StaticLinkedList<T, Capacity>::find(const T& value) const {
    Node* temp = head;
    std::size_t index = 0;

    while (temp != nullptr) {
        if (temp->data == value)
            return index;
        temp = temp->next;
        index++;
    }

    return count;
}

template<typename T,std::size_t Capacity>
void StaticLinkedList<T, Capacity>::reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

// Explicit Instantiations
template class StaticLinkedList<int, 10>;
template class StaticLinkedList<int, 3>;
template class StaticLinkedList<double, 10>;
template class StaticLinkedList<double, 5>;
template class StaticLinkedList<double, 3>;