#include "PoolRBT.h"


template <typename T,std::size_t Capacity>
typename PoolRBT<T, Capacity>::Node* PoolRBT<T, Capacity>::acquire() {

	for (std::size_t i = 0;i < Capacity;i++) {
		if (!used[i]) {
			used[i] = true;
			objects[i].color = R;
			objects[i].parent = nullptr;
			objects[i].left = nullptr;
			objects[i].right = nullptr;

			return &objects[i];
		}
	}
	return nullptr;
}

template<typename T,std::size_t Capacity>
void PoolRBT<T, Capacity>::release(Node* object) {
	if (object == nullptr)
		return;

	for (std::size_t i = 0;i < Capacity;i++) {
		if (&objects[i] == object) {
			used[i] = false;
			return;
		}
	}

}

template<typename T,std::size_t Capacity>
std::size_t PoolRBT<T, Capacity>::returnCapacity() const {
	return Capacity;
}


template class PoolRBT<int, 5>;
