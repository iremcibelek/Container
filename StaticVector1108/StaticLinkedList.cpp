#include "StaticLinkedList.h"

bool StaticLinkedList::push_front(const int& value) {

	if (count == Capacity)
		return false;

	Node* newNode = nullptr;

	for (std::size_t i = 0;i < Capacity;i++) {
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

bool StaticLinkedList::push_back(const int& value) {

	if (count == Capacity)
		return false;

	Node* newNode = nullptr;

	// diziyi gez bos Node bul
	for (std::size_t i = 0;i < Capacity;i++) {
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


bool StaticLinkedList::pop_front() {

	if (head == nullptr)
		return false;

	Node* temp = head;
	head = head->next;

	temp->used = false; // ilk head Node'u artýk bosta
	temp->next = nullptr; // eski baglantýyý temizle

	count--;

	return true;
}

bool StaticLinkedList::pop_back() {

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

bool StaticLinkedList::insertByIndex(std::size_t index, const int& value) {

	if (count == Capacity) // list dolu
		return false;

	if (index > count) // hatalý index
		return false;

	if (index == 0)
		return push_front(value);

	if (index == count)
		return push_back(value);

	//Bos Node bul
	Node* newNode = nullptr;
	for (std::size_t i = 0;i < Capacity;i++) {
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

bool StaticLinkedList::eraseByIndex(std::size_t index) {

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

bool StaticLinkedList::eraseByData(const int& value) {

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


std::size_t StaticLinkedList::size() const {
	return count;
}

bool StaticLinkedList::isEmpty() const {
	return count == 0;
}

bool StaticLinkedList::isFull() const {
	return count == Capacity;
}

std::size_t StaticLinkedList::capacity() const {
	return Capacity;
}

int* StaticLinkedList::front() {

	if (head == nullptr)
		return nullptr;

	return &head->data;
}

const int* StaticLinkedList::front() const {
	if (head == nullptr)
		return nullptr;

	return &head->data;
}


int* StaticLinkedList::back(){

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

const int* StaticLinkedList::back() const {

	if (head == nullptr)
		return nullptr;

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return &temp->data;
}

void StaticLinkedList::clear() {

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

bool StaticLinkedList::exists(const int& value) const {

	Node* temp = head;

	while (temp != nullptr) {

		if (temp->data == value)
			return true;

		temp = temp->next;
	}

	return false;
}

std::size_t StaticLinkedList::find(const int& value) const {

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

void StaticLinkedList::reverse() {
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