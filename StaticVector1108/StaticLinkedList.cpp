#include "StaticLinkedList.h"

template<typename T>
StaticLinkedList<T>::StaticLinkedList(std::size_t capacity)
{
	this->capacity_ = capacity;
	list = new Node[capacity];

	for (std::size_t i = 0; i < capacity_; i++) {
		list[i].used = false;
		list[i].next = nullptr;
	}
}

template<typename T>
StaticLinkedList<T>::~StaticLinkedList()
{
	delete[] list;
}


template<typename T>
bool StaticLinkedList<T>::push_front(const T& value) {

	if (count == capacity_)
		return false;

	Node* newNode = nullptr;

	for (std::size_t i = 0;i < capacity_;i++) {
		if (!list[i].used) {
			newNode = &list[i];
			break;
		}
	}

	newNode->data = value;
	newNode->next = head;
	newNode->used = true;

	head = newNode;
	count++;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::push_back(const T& value) {

	if (count == capacity_)
		return false;

	Node* newNode = nullptr;

	// diziyi gez bos Node bul
	for (std::size_t i = 0;i < capacity_;i++) {
		if (!list[i].used) {
			newNode = &list[i];
			break;
		}
	}

	// yeni Node'un bilgilerini ayarla
	newNode->data = value;
	newNode->next = nullptr;
	newNode->used = true;


	if (head == nullptr) { // liste bossa
		head = newNode;
		count++;
		return true;
	}

	Node* temp = head;

	while (temp->next != nullptr) { // Son Node'u bul
		temp = temp->next;
	}

	temp->next = newNode;
	count++;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::pop_front() {

	if (head == nullptr)
		return false;

	Node* temp = head;
	head = head->next;

	temp->used = false; // ilk head Node'u artýk bosta
	temp->next = nullptr; // eski baglantýyý temizle

	count--;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::pop_back() {

	if (head == nullptr) // liste bossa
		return false;

	if (head->next == nullptr) { // listede tek eleman varsa
		head->used = false;
		head->next = nullptr;
		head = nullptr;
		count--;

		return true;
	}

	Node* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next; // temp: silinecek dugumun bir oncesi
	}

	Node* toDelete = temp->next; 

	temp->next = nullptr;
	toDelete->used = false;
	toDelete->next = nullptr;

	count--;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::insertByIndex(std::size_t index, const T& value) {

	if (count == capacity_) // list dolu
		return false;

	if (index > count) // hatalý index
		return false;

	if (index == 0)
		return push_front(value);

	if (index == count)
		return push_back(value);

	//Bos Node bul
	Node* newNode = nullptr;
	for (std::size_t i = 0;i < capacity_;i++) {
		if (!list[i].used) {
			newNode = &list[i];
			break;
		}
	}
	// newNode bilgilerini guncelle
	newNode->data = value;
	newNode->used = true;

	Node* temp = head;
	for (std::size_t i = 1;i < index;i++) {
		temp = temp->next; // eklenecek yerin bir oncesi
	}
	newNode->next = temp->next;
	temp->next = newNode;
	count++;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::eraseByIndex(std::size_t index) {

	if (index >= count)
		return false;

	if (index == 0)
		return pop_front();

	if (index == count-1) // son eleman
		return pop_back();

	Node* temp = head;
	for (std::size_t i = 1; i < index; i++) {
		temp = temp->next; 	// silinecek Node'un bir öncesine git
	}

	Node* toDelete = temp->next;
	temp->next = toDelete->next;

	toDelete->used = false;
	toDelete->next = nullptr;
	count--;

	return true;
}

template<typename T>
bool StaticLinkedList<T>::eraseByData(const T& value) {

	if (head == nullptr)
		return false; // list bos

	if (head->data == value)
		return pop_front();

	Node* temp = head;
	while(temp->next != nullptr && temp->next->data != value){
		temp = temp->next;
	}

	if (temp->next == nullptr) // deger bulunamazsa
		return false;

	Node* toDelete = temp->next;
	temp->next = toDelete->next;

	toDelete->used = false;
	toDelete->next = nullptr;
	count--;

	return true;
}

template<typename T>
std::size_t StaticLinkedList<T>::size() const {
	return count;
}

template<typename T>
bool StaticLinkedList<T>::isEmpty() const {
	return count == 0;
}

template<typename T>
bool StaticLinkedList<T>::isFull() const {
	return count == capacity_;
}

template<typename T>
std::size_t StaticLinkedList<T>::capacity() const {
	return capacity_;
}

template<typename T>
T* StaticLinkedList<T>::front() {

	if (head == nullptr)
		return nullptr;

	return &head->data;
}

template<typename T>
const T* StaticLinkedList<T>::front() const {
	if (head == nullptr)
		return nullptr;

	return &head->data;
}


template<typename T>
T* StaticLinkedList<T>::back(){

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

template<typename T>
const T* StaticLinkedList<T>::back() const {

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

template<typename T>
void StaticLinkedList<T>::clear() {

	Node* temp = head;

	while (temp != nullptr) {

		Node* nextNode = temp->next;

		temp->used = false;
		temp->next = nullptr;

		temp = nextNode;
	}

	head = nullptr;
	count = 0;
}

template<typename T>
bool StaticLinkedList<T>::exists(const T& value) const {

	Node* temp = head;

	while (temp != nullptr) {

		if (temp->data == value)
			return true;

		temp = temp->next;
	}

	return false;
}

template<typename T>
std::size_t StaticLinkedList<T>::find(const T& value) const {

	Node* temp = head;
	std::size_t index = 0;

	while (temp != nullptr) {
		if (temp->data == value)
			return index;
		temp = temp->next;
		index++;
	}

	return count; // bulunamadý
}

template<typename T>
void StaticLinkedList<T>::reverse() {
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

template class StaticLinkedList<int>;
template class StaticLinkedList<double>;