#pragma once

#include <cstddef>

template <typename T>

class LinkedList {
private:
	struct Node {
		T data;
		Node* next;
	};

	Node* head = nullptr;
	std::size_t count = 0;

public:
	void push_front(const T& value);
	void push_back(const T& value);

	bool pop_front(); // Liste bossa yanlýslýgý
	bool pop_back();  // test etmek icin bool

	bool insertByIndex(std::size_t index, const T& value);
	bool eraseByIndex(std::size_t index);
	bool eraseByData(const T& value);

	std::size_t size() const;
	bool isEmpty() const;
	
	T* front();
	const T* front() const;

	T* back();
	const T* back() const;

	void clear();

	bool exists(const T& value) const;
	std::size_t find(const T& value) const;

	void reverse();
};



