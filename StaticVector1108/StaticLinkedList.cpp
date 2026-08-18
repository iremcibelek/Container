#include "StaticLinkedList.h"

template<typename T>
StaticLinkedList<T>::StaticLinkedList(ObjectPool<Node>& pool)
    : pool(pool), head(nullptr), count(0) {
}

template<typename T>
StaticLinkedList<T>::~StaticLinkedList() {
    clear();
}

template<typename T>
bool StaticLinkedList<T>::push_front(const T& value) {
    Node* newNode = pool.acquire();
    if (newNode == nullptr)
        return false;

    newNode->data = value;
    newNode->next = head;
    head = newNode;
    count++;

    return true;
}

template<typename T>
bool StaticLinkedList<T>::push_back(const T& value) {
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

template<typename T>
bool StaticLinkedList<T>::pop_front() {
    if (head == nullptr)
        return false;

    Node* temp = head;
    head = head->next;

    pool.release(temp);
    count--;
    return true;
}

template<typename T>
bool StaticLinkedList<T>::pop_back() {
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

template<typename T>
bool StaticLinkedList<T>::insertByIndex(std::size_t index, const T& value) {
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

template<typename T>
bool StaticLinkedList<T>::eraseByIndex(std::size_t index) {
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

template<typename T>
bool StaticLinkedList<T>::eraseByData(const T& value) {
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

template<typename T>
std::size_t StaticLinkedList<T>::size() const {
    return count;
}

template<typename T>
bool StaticLinkedList<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
bool StaticLinkedList<T>::isFull() const {
    return count == pool.returnCapacity();
}

template<typename T>
std::size_t StaticLinkedList<T>::capacity() const {
    return pool.returnCapacity();
}

template<typename T>
T* StaticLinkedList<T>::front() {
    return head ? &head->data : nullptr;
}

template<typename T>
const T* StaticLinkedList<T>::front() const {
    return head ? &head->data : nullptr;
}

template<typename T>
T* StaticLinkedList<T>::back() {
    if (head == nullptr)
        return nullptr;

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return &temp->data;
}

template<typename T>
const T* StaticLinkedList<T>::back() const {
    if (head == nullptr)
        return nullptr;

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return &temp->data;
}

template<typename T>
void StaticLinkedList<T>::clear() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        pool.release(temp);
        temp = nextNode;
    }
    head = nullptr;
    count = 0;
}

template<typename T>
bool StaticLinkedList<T>::exists(const T& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

template<typename T>
std::size_t StaticLinkedList<T>::find(const T& value) const {
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

template<typename T>
void StaticLinkedList<T>::reverse() {
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
template class StaticLinkedList<int>;
template class StaticLinkedList<double>;