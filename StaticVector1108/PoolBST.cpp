#include "PoolBST.h"

template <typename T, std::size_t Capacity>
typename PoolBST<T, Capacity>::Node* PoolBST<T, Capacity>::acquire() {
    for (std::size_t i = 0; i < Capacity; i++) {
        if (!used[i]) {
            used[i] = true;
            objects[i].left = nullptr;
            objects[i].right = nullptr;
            return &objects[i];
        }
    }
    return nullptr;
}

template <typename T, std::size_t Capacity>
void PoolBST<T, Capacity>::release(Node* object) {
    if (object == nullptr)
        return;

    for (std::size_t i = 0; i < Capacity; i++) {
        if (&objects[i] == object) {
            used[i] = false;
            return;
        }
    }
}

template <typename T, std::size_t Capacity>
std::size_t PoolBST<T, Capacity>::returnCapacity() const {
    return Capacity;
}

// Explicit Instantiations
template class PoolBST<int, 10>;
template class PoolBST<int, 3>;
template class PoolBST<double, 10>;
template class PoolBST<double, 5>;
template class PoolBST<double, 3>;