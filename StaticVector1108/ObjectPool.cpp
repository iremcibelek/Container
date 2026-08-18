#include "ObjectPool.h"

template <typename T,std::size_t Capacity>
ObjectPool<T,Capacity>::ObjectPool() {

    for (std::size_t i = 0; i < Capacity; i++) {
        used[i] = false;
    }
}

template <typename T,std::size_t Capacity>
typename ObjectPool<T,Capacity>::Node* ObjectPool<T,Capacity>::acquire() {
    for (std::size_t i = 0; i < Capacity; i++) {
        if (!used[i]) {
            used[i] = true;
            return &objects[i];
        }
    }
    return nullptr;
}

template <typename T,std::size_t Capacity>
void ObjectPool<T,Capacity>::release(Node* object) {
    if (object == nullptr)
        return;

    for (std::size_t i = 0; i < Capacity; i++) {
        if (&objects[i] == object) {
            used[i] = false;
            return;
        }
    }
}

template <typename T,std::size_t Capacity>
std::size_t ObjectPool<T,Capacity>::returnCapacity() const {
    return Capacity;
}

// Explicit Instantiations
template class ObjectPool<int, 10>;
template class ObjectPool<int, 3>;
template class ObjectPool<double, 10>;
template class ObjectPool<double, 5>;
template class ObjectPool<double, 3>;