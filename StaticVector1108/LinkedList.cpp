#include "LinkedList.h"

template <typename T>
void LinkedList<T>::push_front(const T& value) {

	Node* newNode = new Node{ value,head };

	head = newNode;
	count++;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {

	Node* newNode = new Node{ value,nullptr };

	if (head == nullptr) {
		head = newNode;
		count++;
		return;
	}

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	temp->next = newNode;
	count++;
}

template <typename T>
bool LinkedList<T>::pop_front() {

	if (head == nullptr)
		return false;

	Node* temp = head; // head'i gecici degisken ile tut
	head = head->next; // head'i ilerlet
	
	delete temp; // ilk head'i sil
	count--;

	return true;
}

template <typename T>
bool LinkedList<T>::pop_back() {
	
	if (head == nullptr) {
		return false;
	}

	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		count--;

		return true;
	}	

	Node* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;
	count--;

	return true;
}

template <typename T>
bool LinkedList<T>::insertByIndex(std::size_t index, const T& value) {

	if (index > count)
		return false;

	if (index == 0) {
		push_front(value);
		return true;
	}

	if (index == count) {
		push_back(value);
		return true;
	}

	Node* temp = head;

	for (std::size_t i = 1; i < index;i++) {
		temp = temp->next;
	}

	Node* newNode = new Node{ value, temp->next };
	temp->next = newNode;

	count++;

	return true;
}

template <typename T>
bool LinkedList<T>::eraseByIndex(std::size_t index) {
	
	if (index >= count)
		return false;

	if (index == 0) {
		pop_front();
		return true;
	}

	if (index == count - 1) {
		pop_back();
		return true;
	}

	Node* temp = head;

	// 10 20 30 40 - eraseByIndex(2) - 30u silmek istiyoruz

	for (std::size_t i = 1;i < index;i++) {
		temp = temp->next; // temp = 20
	}

	Node* toDelete = temp->next; // toDelete:30
	temp->next = toDelete->next; // 20nin nexti 40 oldu

	delete toDelete; // 30 silindi
	count--;

	return true;
}

template <typename T>
bool LinkedList<T>::eraseByData(const T& value) {

	if (head == nullptr)
		return false;

	if (head->data == value) {
		pop_front();
		return true;
	}

	Node* temp = head;
	while (temp->next != nullptr && temp->next->data != value ) {
		temp = temp->next;
	}

	if (temp->next == nullptr)
		return false;

	Node* toDelete = temp->next;
	temp->next = toDelete->next;

	delete toDelete;
	count--;

	return true;
}

template <typename T>
std::size_t LinkedList<T>::size() const {
	return count;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
T* LinkedList<T>::front() {

	if (head == nullptr)
		return nullptr;

	return &head->data;
}

template <typename T>
const T* LinkedList<T>::front() const {
	
	if (head == nullptr)
		return nullptr;

	return &head->data;
}

template <typename T>
T* LinkedList<T>::back() {

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

template <typename T>
const T* LinkedList<T>::back() const {

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

template <typename T>
void LinkedList<T>::clear() {

	Node* temp = head;

	while (temp != nullptr) {

		Node* nextNode = temp->next;

		delete temp;

		temp = nextNode;
	}

	head = nullptr;
	count = 0;
}

template <typename T>
bool LinkedList<T>::exists(const T& value) const {

	Node* temp = head;

	while (temp != nullptr) {

		if (temp->data == value)
			return true;

		temp = temp->next;
	}

	return false;
}

template <typename T>
std::size_t LinkedList<T>::find(const T& value) const {
	
	Node* temp = head;
	std::size_t index = 0;

	while (temp != nullptr) {
		if (temp->data == value)
			return index;
		temp = temp->next;
		index++;
	}

	return count;
}

template <typename T>
void LinkedList<T>::reverse() {

	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;

	while (current != nullptr) {

		next = current->next;

		current->next = prev; 

		prev = current;
		current = next;
	}

	head = prev;
}

template class LinkedList<int>;