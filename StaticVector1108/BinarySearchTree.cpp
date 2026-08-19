#include "BinarySearchTree.h"

template<typename T, std::size_t Capacity>
BinarySearchTree<T, Capacity>::BinarySearchTree(PoolBST <T, Capacity>& pool)
    : pool(pool), root(nullptr), count(0) {
}

template<typename T, std::size_t Capacity>
BinarySearchTree<T, Capacity>::~BinarySearchTree() {
    clear();
}

template<typename T,std::size_t Capacity>
typename BinarySearchTree<T, Capacity>::Node* BinarySearchTree<T, Capacity>::insertRec(Node* current, const T& value, bool& inserted) {
    if (current == nullptr){
        Node* newNode = pool.acquire();
        if (newNode == nullptr) {
            inserted = false;
            return nullptr;
        }
        newNode->data = value;
        inserted = true;
        return newNode;
    }

    if (value < current->data) {
        current->left = insertRec(current->left, value, inserted);
    }
    else if (value > current->data) {
        current->right = insertRec(current->right, value, inserted);
    }
    else {
        inserted = false; // Duplicate kabul etmiyor
    }
    return current;
}

template<typename T,std::size_t Capacity>
bool BinarySearchTree<T, Capacity>::insert(const T& value) {
    bool inserted = false;
    root = insertRec(root, value, inserted);
    if (inserted)
        count++;

    return inserted;
}

template<typename T,std::size_t Capacity>
typename BinarySearchTree<T, Capacity>::Node* BinarySearchTree<T, Capacity>::eraseRec(Node* current, const T& value, bool& removed) {
    if (current == nullptr) {
        removed = false;
        return nullptr;
    }
    if (value < current->data)
        current->left = eraseRec(current->left, value, removed);
    else if (value > current->data)
        current->right = eraseRec(current->right, value, removed);
    else {
        // eleman bulundu
        removed = true;

        if (current->left == nullptr) { // Sol çocuðu yoksa (veya hiç çocuðu yoksa)
            Node* temp = current->right;
            pool.release(current);
            return temp; // Sað çocuðu (veya nullptr) yukarýya baðla
        }
        else if (current->right == nullptr) { // Sað çocuðu yoksa
            Node* temp = current->left;
            pool.release(current);
            return temp; // Sol çocuðu yukarýya baðla
        }
        // Durum 3: Ýki çocuðu da varsa
        Node* temp = findMinNode(current->right); // Sað dalýn en küçüðünü bul
        current->data = temp->data;                // Veriyi buraya kopyala
        bool dummyRemoved = false;
        current->right = eraseRec(current->right, temp->data, dummyRemoved); // Aþaðýdaki kopyayý sil
    }
    return current;
}

template<typename T,std::size_t Capacity>
bool BinarySearchTree<T, Capacity>::erase(const T& value) {
    bool removed = false;
    root = eraseRec(root, value, removed);
    if (removed)
        count--;
    return removed;
}

template<typename T,std::size_t Capacity>
std::size_t BinarySearchTree<T, Capacity>::size() const {
    return count;
}

template<typename T,std::size_t Capacity>
bool BinarySearchTree<T, Capacity>::isEmpty() const {
    return root == nullptr;
}

template<typename T, std::size_t Capacity>
bool BinarySearchTree<T, Capacity>::isFull() const {
    return count == pool.returnCapacity();
}

template<typename T,std::size_t Capacity>
std::size_t BinarySearchTree<T, Capacity>::capacity() const {
    return pool.returnCapacity();
}

template<typename T,std::size_t Capacity>
typename BinarySearchTree<T, Capacity>::Node* BinarySearchTree<T,Capacity>::findMinNode(Node* current) const {
    while (current != nullptr && current ->left != nullptr)
        current = current->left;
    return current;
}

template<typename T,std::size_t Capacity>
T* BinarySearchTree<T, Capacity>::min() {
    Node* minNode = findMinNode(root);
    return minNode ? &minNode->data : nullptr;
}

template<typename T, std::size_t Capacity>
const T* BinarySearchTree<T, Capacity>::min() const{
    Node* minNode = findMinNode(root);
    return minNode ? &minNode->data : nullptr;
}


template<typename T, std::size_t Capacity>
typename BinarySearchTree<T, Capacity>::Node* BinarySearchTree<T, Capacity>::findMaxNode(Node* current) const {
    while (current != nullptr && current ->right!= nullptr)
        current = current->right;
    return current;
}

template<typename T, std::size_t Capacity>
T* BinarySearchTree<T, Capacity>::max() {
    Node* maxNode = findMaxNode(root);
    return maxNode ? &maxNode->data : nullptr;
}

template<typename T, std::size_t Capacity>
const T* BinarySearchTree<T, Capacity>::max() const {
    Node* maxNode = findMaxNode(root);
    return maxNode ? &maxNode->data : nullptr;
}

template<typename T, std::size_t Capacity>
void BinarySearchTree<T, Capacity>::clearRec(Node* current) {
    if (current == nullptr)
        return;
    clearRec(current->left);
    clearRec(current->right);
    pool.release(current);
}


template<typename T, std::size_t Capacity>
void BinarySearchTree<T, Capacity>::clear() {
    clearRec(root);
    root = nullptr;
    count = 0;
}

template<typename T,std::size_t Capacity>
bool BinarySearchTree<T,Capacity>::existsRec(Node* current, const T& value) const {
    if (current == nullptr)
        return false;
    if (value == current->data)
        return true;

    if (value < current->data) // kucukse sola git 
        return existsRec(current->left, value);

    return existsRec(current->right, value); //degilse sag tarafta ara 
}

template<typename T,std::size_t Capacity>
bool BinarySearchTree<T, Capacity>::exists(const T& value) const {
    return existsRec(root, value);
}

template class BinarySearchTree<int, 10>;
template class BinarySearchTree<int, 3>;