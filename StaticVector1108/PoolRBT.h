#pragma once

#include <cstddef>

enum Color {
	R, B
};

template<typename T, std::size_t Capacity>
class PoolRBT {
public:
	struct Node{
		Color color = R;
		T data;
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;
	};
private:
	Node objects[Capacity];
	bool used[Capacity]{};

public:
	PoolRBT() = default;
	~PoolRBT() = default;

	PoolRBT(const PoolRBT&) = delete;
	PoolRBT& operator = (const PoolRBT& ) = delete;

	Node* acquire();
	void release(Node* object);
	std::size_t returnCapacity() const;
};