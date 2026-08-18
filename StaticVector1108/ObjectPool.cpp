#include "ObjectPool.h"
#include "StaticLinkedList.h" // Node turunu kullanabilmek icin

template <typename T>
ObjectPool<T>::ObjectPool(std::size_t capacity) : capacity_(capacity) {
    // : capacity_(capacity) Dýþarýdan gelen kapasite deðerini doðrudan sýnýfýn capacity_ alanýna atar.
    objects = new T[capacity_];
    used = new bool[capacity_];

    for (std::size_t i = 0; i < capacity_; i++) {
        used[i] = false;
    }
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
    delete[] objects; // new ile acýlan iki diziyi heap bellekten temizler
    delete[] used;
}

template <typename T>
T* ObjectPool<T>::acquire() { // alan tahsis etme
    for (std::size_t i = 0; i < capacity_; i++) {
        if (!used[i]) {
            used[i] = true;
            return &objects[i];
        }
    }
    return nullptr;
}

template <typename T>
void ObjectPool<T>::release(T* object) {
    if (object == nullptr)
        return;

    for (std::size_t i = 0; i < capacity_; i++) {
        if (&objects[i] == object) {
            used[i] = false;
            return;
        }
    }
}

template <typename T>
std::size_t ObjectPool<T>::returnCapacity() const {
    return capacity_;
}

// Explicit Instantiations
template class ObjectPool<StaticLinkedList<int>::Node>;
template class ObjectPool<StaticLinkedList<double>::Node>;