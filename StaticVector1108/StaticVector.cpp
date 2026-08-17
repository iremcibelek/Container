#include "StaticVector.h"
#include <cstddef>  // size_t kullanýmý icin 
#include <iostream> // print fonk icin

// T: Veri turu 

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::push_back(const T& value) { // Sona deger ekle 
	if (full()) {
		return false; // Doluysa islemi yapma
	}

	// Dolu degilse 
	arr[count] = value;
	count++;

	return true;
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::pop_back() { // Sondakini sil
	if (empty()) {
		return false; // Dizi bos ise 
	}

	count--;

	return true;
}

template <typename T, std::size_t Capacity>
T& StaticVector<T, Capacity>::operator[](std::size_t index) { // index bilgisi dondur
	return arr[index];
}

template <typename T, std::size_t Capacity>
const T& StaticVector<T, Capacity>::operator[](std::size_t index) const {
	return  arr[index];
}

template <typename T, std::size_t Capacity>
T* StaticVector<T, Capacity>::at(std::size_t index) { // operator ile ayný ama kontrol eder 
	if (index >= count) {
		return nullptr;
	}

	return &arr[index];
}

template <typename T, std::size_t Capacity>
const T* StaticVector<T, Capacity>::at(std::size_t index) const {
	if (index >= count) {
		return nullptr;
	}

	return &arr[index];
}

template <typename T, std::size_t Capacity>
std::size_t StaticVector<T, Capacity>::size() const {
	return count;
}

template <typename T, std::size_t Capacity>
constexpr std::size_t StaticVector<T, Capacity>::capacity() const {
	return Capacity;
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::empty() const {
	return count == 0; // Eleman yoksa true
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::full() const {
	return count == Capacity; // Kapasite doluysa true
}

template <typename T, std::size_t Capacity>
T*  StaticVector<T, Capacity>::back() { // En sondaki degeri goster 
	if (empty()) {
		return nullptr;
	}
	return &arr[count - 1];
}

template <typename T, std::size_t Capacity>
const T* StaticVector<T, Capacity>::back() const {
	if (empty()) {
		return nullptr;
	}
	return &arr[count - 1];
}

template <typename T, std::size_t Capacity>
T* StaticVector<T, Capacity>::front() { // En bastaki degeri goster
	if (empty()) {
		return nullptr;
	}
	return &arr[0];
}

template <typename T, std::size_t Capacity>
const T* StaticVector<T, Capacity>::front() const {
	if (empty()) {
		return nullptr;
	}
	return &arr[0];
}

template <typename T, std::size_t Capacity>
void  StaticVector<T, Capacity>::clear() { // Diziyi temizle
	count = 0;
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::exists(const T& value) const { // Aranan deger var mý 
	for (std::size_t i = 0; i < count; i++) {
		if (arr[i] == value)
			return true;
	}
	return false;
}

template <typename T, std::size_t Capacity>
T* StaticVector<T, Capacity>::find(const T& value) { // Aranan degeri bul
	for (std::size_t i = 0; i < count; i++) {
		if (arr[i] == value)
			return &arr[i];
	}
	return nullptr;
}

template <typename T, std::size_t Capacity>
const T* StaticVector<T, Capacity>::find(const T& value) const {
	for (std::size_t i = 0; i < count; i++) {
		if (arr[i] == value)
			return &arr[i];
	}
	return nullptr;
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::eraseByIndex(std::size_t index) { // Istenen indexteki elemaný sil
	if (index >= count) {
		return false;
	}

	for (std::size_t i = index; i + 1 < count; i++) {
		arr[i] = arr[i + 1];
	}
	count--;
	return true;
}

template <typename T, std::size_t Capacity>
bool StaticVector<T, Capacity>::insertByIndex(std::size_t index, const T& value) { // Istenen indexe eleman ekle 
	if (full() || index > count) {
	 return false;
	}
	for (std::size_t i = count; i > index; i--) { // Sagdan sola kaydýrma 
		arr[i] = arr[i - 1];
	}

	arr[index] = value;
	count++;

	return true;
}

template <typename T, std::size_t Capacity>
void StaticVector<T, Capacity>::print() const {
	for (std::size_t i = 0; i < count; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

// Bu proje için kullanýlacak özel template türü:
template class StaticVector<int, 6>;
template class StaticVector<int, 2>;
