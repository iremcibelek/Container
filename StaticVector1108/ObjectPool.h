#pragma once

#include <cstddef>

template <typename T>
class ObjectPool {
private:
    T* objects; // dizi
    bool* used;
    std::size_t capacity_;

public:
    explicit ObjectPool(std::size_t capacity);
    ~ObjectPool();

    // = delete; : Copy constructor ve copy assignment operatörlerini derleyici seviyesinde yasaklar.
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

    T* acquire();  // yer tahsis etme
    void release(T* object);
    std::size_t returnCapacity() const; // havuzun toplam kapasitesini doner
};