#pragma once

#include <cstddef>

template <typename T, std::size_t Capacity>

class StaticQueue {
private:
	std::size_t frontIndex = 0;
	std::size_t rearIndex = 0;
	std::size_t count = 0;

	T arr[Capacity]{};
public:
	bool push(const T& value);
	bool pop();

	std::size_t size() const;
	constexpr std::size_t capacity() const;

	bool empty() const;
	bool full() const;

	T* front();
	const T* front() const;

	T* back();
	const T* back() const;

	void clear();
	void print() const;

	bool exists(const T& value) const;
	std::size_t find(const T& value) const;
};
