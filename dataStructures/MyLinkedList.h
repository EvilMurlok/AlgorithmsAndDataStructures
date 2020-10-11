#ifndef MYLINKEDLIST_H_
#define MYLINKEDLIST_H_

#include <iostream>
#include <cassert>
#include <stdexcept>

template <typename T>
class MyNode
{
public:
	MyNode<T>() : next{ nullptr } {};
	MyNode<T>(T itemToAdd) : next{ nullptr }, data{ itemToAdd } {};
	MyNode<T>(const MyNode<T>& listToCopy) : next{ listToCopy.next }, data{ listToCopy.data } {};
	~MyNode<T>() = default;

	T& getData() { return data; }
	const T& getData() const { return data; }
	void setData(T itemToSet) { data = itemToSet; };

	MyNode<T>* getNext() const { return next; }
	void setNext(MyNode<T>* nextToSet) { next = nextToSet; }

private:
	T data;
	MyNode<T>* next;
};

template <typename T>
class MyLinkedList
{
public:
	MyLinkedList<T>() : head{ nullptr }, tail{ nullptr }, size{ 0 } {};
	explicit MyLinkedList<T>(bool isSort) : head{ nullptr }, tail{ nullptr }, size{ 0 }{};
	MyLinkedList<T>(const MyLinkedList<T>& listToCopy);

	MyLinkedList<T>(MyLinkedList<T>&& listToMove) : head{ listToMove.head }, tail{ listToMove.tail },
		size{ listToMove.size }
	{ listToMove.head = nullptr; listToMove.tail = nullptr; listToMove.size = 0; };

	size_t len() const { return size; }

	MyLinkedList<T>& operator=(const MyLinkedList<T>& listToCopy);
	MyLinkedList<T>& operator=(MyLinkedList<T>&& listtoMove);

	bool isEmpty() const { return head == nullptr; }
	T getFront() const { return head->getData(); }
	T getBack() const { return tail->getData(); }

	void pushBack(T itemToAdd);
	void pushFront(T itemToAdd);

	T popBack();
	T popFront();

	int find(T itemToFind) const;

	void del(T itemToDel);
	T remove(size_t indexToDelete);
	void terminate();

	void insert(size_t index, T value);
	void insSort(T itemToInsert);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	~MyLinkedList<T>() {
		terminate();
	}

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyLinkedList<T>& listToOutput);

private:
	MyNode<T>* head, * tail;
	size_t size;
};

template <typename T>
MyLinkedList<T>::MyLinkedList(const MyLinkedList<T>& listToCopy) {
	MyNode<T>* temp1 = listToCopy.head;
	MyNode<T>* temp2 = new MyNode<T>(temp1->getData());
	head = temp2;
	while (temp1->getNext()) {
		temp1 = temp1->getNext();
		temp2->setNext(new MyNode<T>(temp1->getData()));
		temp2 = temp2->getNext();
	}
	tail = temp2;
	size = listToCopy.size;
}

template<typename T>
MyLinkedList<T>& MyLinkedList<T>::operator=(const MyLinkedList<T>& listToCopy) {
	if (this == &listToCopy) {
		return *this;
	}
	terminate();
	MyNode<T>* temp1 = listToCopy.head;
	MyNode<T>* temp2 = new MyNode<T>(temp1->getData());
	head = temp2;
	while (temp1->getNext()) {
		temp1 = temp1->getNext();
		temp2->setNext(new MyNode<T>(temp1->getData()));
		temp2 = temp2->getNext();
	}
	tail = temp2;
	size = listToCopy.size;
	return *this;
}

template<typename T>
MyLinkedList<T>& MyLinkedList<T>::operator=(MyLinkedList<T>&& listToMove) {
	if (this == &listToMove) {
		return *this;
	}
	terminate();
	head = listToMove.head;
	tail = listToMove.tail;
	listToMove.head = listToMove.tail = nullptr;
	size = listToMove.size;
	listToMove.size = 0;
	return *this;
}

template<typename T>
void MyLinkedList<T>::pushBack(T itemToPush) {
	if (size == 0) {
		tail = head = new MyNode<T>(itemToPush);
	}
	else {
		tail->setNext(new MyNode<T>(itemToPush));
		tail = tail->getNext();
	}
	++size;
}

template <typename T>
void MyLinkedList<T>::pushFront(T itemToPush) {
	MyNode<T>* temp = new MyNode<T>(itemToPush);
	temp->setNext(head);
	head = temp;
	++size;
	if (size == 1) {
		tail = head;
	}
}

//O(n)
template <typename T>
T MyLinkedList<T>::popBack() {
	if (size == 0) {
		throw std::runtime_error("The list is Empty");
	}
	else if (size == 1) {
		T temp = head->getData();
		delete head;
		--size;
		tail = head = nullptr;
		return temp;
	}
	MyNode<T>* temp = head;
	while (temp->getNext() != tail) {
		temp = temp->getNext();
	}
	T temp1 = temp->getNext()->getData();
	delete temp->getNext();
	tail = temp;
	tail->setNext(nullptr);
	--size;
	return temp1;
}

template <typename T>
T MyLinkedList<T>::popFront() {
	if (size == 0) {
		throw std::runtime_error("The list is Empty");
	}
	MyNode<T>* temp = head;
	T temp1 = head->getData();
	head = head->getNext();
	delete temp;
	if (size == 1) { tail = nullptr; }
	--size;
	return temp1;
}

template<typename T>
int MyLinkedList<T>::find(T itemToFind) const {
	if (!head) { return -1; }
	MyNode<T>* current = head;
	int position = 0;
	while (current->getData() != itemToFind) {
		if (!(current->getNext())) { return -1; } //itemToFind not found
		else { current = current->getNext(); }
		++position;
	}
	return position;
}

template<typename T>
void MyLinkedList<T>::del(T itemToDel) {
	if (size == 0) {
		throw std::runtime_error("The list is Empty");
	}
	MyNode<T>* current = head, * previous = head;
	while (current->getData() != itemToDel) {
		if (!(current->getNext())) {
			return; //item not found
		}
		else {
			previous = current;
			current = current->getNext();
		}
	}
	if (current == head) {
		head = head->getNext();
		delete previous;
		if (size == 1) { tail = nullptr; }
	}
	else {
		previous->setNext(current->getNext());
		if (!(current->getNext())) { tail = previous; }
		delete current;
	}
	--size;
}

template<typename T>
T MyLinkedList<T>::remove(size_t indexToDelete) {
	if (indexToDelete < 0 || indexToDelete >= size) {
		throw std::out_of_range("The index is out of range");
	}
	MyNode<T>* current = head, * previous = head;
	for (size_t i = 0; i < indexToDelete; ++i) {
		previous = current;
		current = current->getNext();
	}
	T dataToReturn = current->getData();
	if (current == head) {
		head = head->getNext();
		delete previous;
		if (size == 1) { tail = nullptr; }
	}
	else {
		previous->setNext(current->getNext());
		if (!(current->getNext())) { tail = previous; }
		delete current;
	}
	--size;
	return dataToReturn;
}

template<typename T>
void MyLinkedList<T>::terminate() {
	MyNode<T>* temp = head;
	MyNode<T>* temp1 = temp;
	while (temp) {
		temp1 = temp;
		temp = temp->getNext();
		delete temp1;
	}
	size = 0;
	head = tail = nullptr;
}

template<typename T>
void MyLinkedList<T>::insert(size_t index, T value) {
	if (index < 0 || index > size) {
		throw std::out_of_range("The index is out of range");
	}
	if (index == 0) {
		pushFront(value);
		return;
	}
	else if (index == size) {
		pushBack(value);
		return;
	}
	MyNode<T>* current = head, * previous = head;
	for (size_t i = 0; i < index; ++i) {
		previous = current;
		current = current->getNext();
	}
	previous->setNext(new MyNode<T>(value));
	previous = previous->getNext();
	previous->setNext(current);
	++size;
}

template<typename T>
T& MyLinkedList<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("The index is out of range");
	}
	MyNode<T>* temp = head;
	for (size_t i = 0; i < index; ++i) {
		temp = temp->getNext();
	}
	return temp->getData();
}

template<typename T>
const T& MyLinkedList<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("The index is out of range");
	}
	MyNode<T>* temp = head;
	for (size_t i = 0; i < index; ++i) {
		temp = temp->getNext();
	}
	return temp->getData();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyLinkedList<T>& listToOutput) {
	MyNode<T>* temp = listToOutput.head;
	for (size_t i = 0; i < listToOutput.size; ++i) {
		if (i < listToOutput.size - 1) {
			os << temp->getData() << ", ";
		}
		else {
			os << temp->getData() << ". ";
		}
		temp = temp->getNext();
	}
	return os;
}
#endif
