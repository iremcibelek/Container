#include "StaticQueue.h"
#include <iostream>
#include <cstddef>

template <typename T, std::size_t Capacity>
bool StaticQueue<T, Capacity>::push(const T& value) {
	if (full())
		return false;

	arr[rearIndex] = value;
	rearIndex = (rearIndex + 1) % Capacity;
	count++ ;

	return true;
}

template <typename T, std::size_t Capacity>
bool StaticQueue<T, Capacity>::pop(){
	if (empty())
		return false;

	frontIndex = (frontIndex + 1) % Capacity;
	count--;

	return true;
}

template <typename T, std::size_t Capacity>
std::size_t StaticQueue<T, Capacity>::size() const {
	return count;
}

template <typename T, std::size_t Capacity>
constexpr std::size_t StaticQueue<T, Capacity>::capacity() const {
	return Capacity;
}

template <typename T, std::size_t Capacity>
bool StaticQueue<T, Capacity>::empty() const {
	return count == 0;
}

template <typename T, std::size_t Capacity>
bool StaticQueue<T, Capacity>::full() const {
	return count == Capacity;
}

template <typename T, std::size_t Capacity>
T* StaticQueue<T, Capacity>::front() {
	if (empty())
		return nullptr;

	return &arr[frontIndex];
}

template <typename T, std::size_t Capacity>
const T* StaticQueue<T, Capacity>::front() const {
	if (empty())
		return nullptr;

	return &arr[frontIndex];
}

template <typename T, std::size_t Capacity>
T* StaticQueue<T, Capacity>::back() {
	if (empty())
		return nullptr;

	std::size_t index = (rearIndex - 1 + Capacity) % Capacity;
	return &arr[index];
}

template <typename T, std::size_t Capacity>
const T* StaticQueue<T, Capacity>::back() const {
	if (empty())
		return nullptr;
	
	std::size_t index = (rearIndex - 1 + Capacity) % Capacity;
	return &arr[index];
}

template <typename T, std::size_t Capacity>
void StaticQueue<T, Capacity>::clear() {
	
	frontIndex = 0;
	rearIndex = 0;
	count = 0;
}

template <typename T, std::size_t Capacity>
void StaticQueue<T, Capacity>::print() const {

	for (std::size_t i = 0; i < count; i++) {
		std::size_t index = (frontIndex + i) % Capacity;
		printf("%d ", arr[index]);
	}
	printf("\n");
}

template <typename T,std::size_t Capacity>
bool StaticQueue<T, Capacity>::exists(const T& value) const {
	
	for (std::size_t i = 0; i < count; i++) {
		std::size_t index = (frontIndex + i) % Capacity;
		if (arr[index] == value)
			return true;
	}
	return false;
}

template <typename T, std::size_t Capacity>
std::size_t StaticQueue<T, Capacity>::find(const T& value) const {

	for (std::size_t i = 0; i < count; i++) {

		std::size_t index = (frontIndex + i) % Capacity;

		if (arr[index] == value)
			return i;
	}

	return Capacity;
}

template class StaticQueue<int, 6>;
template class StaticQueue<int, 2>;
template class StaticQueue<int, 3>;