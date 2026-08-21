#pragma once

#include <cstddef>
#include "PoolRBT.h"


template<typename T,std::size_t Capacity>
class RedBlackTree {
public:
	using Node = typename PoolRBT<T, Capacity>::Node;

private:
	PoolRBT<T, Capacity>& pool;
	Node* root = nullptr;
	std::size_t count = 0;

	Node* getGrandparent(Node* x);
	Node* getUncle(Node* x);
	Node* getSibling(Node* x);
	Color getColor(Node* x) const;

	Node* getSuccessor(Node* x);

	void swapColors(Node* a, Node* b);

	void leftRotate(Node* x);
	void rightRotate(Node* y);

	void fixRedProperty(Node* x);
	
	void transplant(Node* u, Node* v);
	void fixDoubleBlack(Node* x,Node* xParent);

	void clearRec(Node* current);

public:

	explicit RedBlackTree(PoolRBT<T, Capacity>& pool);
	~RedBlackTree();

	Node* getRoot() const;

	bool insert(const T& value);
	bool erase(const T& value);

	T* min();
	const T* min() const;
	T* max();
	const T* max() const;

	std::size_t size() const;
	bool isEmpty();
	bool isFull();
	std::size_t capacity() const;

	void clear();
	bool exists(const T& value);
};