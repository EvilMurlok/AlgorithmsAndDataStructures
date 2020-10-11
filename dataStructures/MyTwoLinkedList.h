#ifndef MYTWOLINKEDLIST_H_
#define MYTWOLINKEDLIST_H_


#include <iostream>
#include <stdexcept>

template <typename T>
class MyNode
{
public:
	MyNode<T>() : next{ nullptr }, previous{ nullptr } {};
	MyNode<T>(T itemToAdd) : next{ nullptr }, previous{ nullptr }, data{ itemToAdd } {};
	MyNode<T>(const MyNode<T>& listToCopy) : next{ listToCopy.next }, previous{ listToCopy.previous }, data{ listToCopy.data } {};
	~MyNode<T>() = default;
	
	T& getData() { return data; }
	const T& getData() const { return data; }
	void setData(T itemToSet) { data = itemToSet; };

	MyNode<T>* getPrevious() { return previous; }
	void setPrevious(MyNode<T>* prevToSet) { previous = prevToSet; }

	MyNode<T>* getNext() { return next; }
	void setNext(MyNode<T>* nextToSet) { next = nextToSet; }
	
	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyNode<T>& nodeToOutput) {
		os << nodeToOutput.data << ' ';
		return os;
	}

private:
	T data;
	MyNode<T>* next;
	MyNode<T>* previous;
};

template <typename T>
class MyTwoLinkedList
{
public:

	class Iterator
	{
	public:
		Iterator(MyNode<T>* node) : current{ node } {};
		~Iterator() = default;

		bool operator==(const Iterator& iteratorToCopmpare) {
			return current == iteratorToCopmpare.current;
		}

		bool operator!=(const Iterator& iteratorToCompare) {
			return (current != iteratorToCompare.current);
		}

		void operator++() {
			if (current) { current = current->getNext(); }
			else {
				throw std::out_of_range("it's the end of thelist!");
			}
		}

		void operator--() {
			if (current) { current = current->getPrevious(); }
			else {
				throw std::out_of_range("it's the beggining of the list!");
			}
		}

		T& operator*() {
			if (current) { return current->getData(); }
			else {
				throw std::runtime_error("you are out of the list!");
			}
		}

		const T& operator*() const {
			if (current) { return current->getData(); }
			else {
				throw std::runtime_error("you are out of the list!");
			}
		}
	private:
		MyNode<T>* current;
	};

	MyTwoLinkedList() : head{ nullptr }, tail{ nullptr }, size{ 0 }{};
	
	MyTwoLinkedList(const MyTwoLinkedList<T>& listToCopy);
	MyTwoLinkedList(MyTwoLinkedList<T>&& listToMove) : head{ listToMove.head }, tail{ listToMove.tail }, size{ listToMove.size }
														{ listToMove.head = nullptr; listToMove.tail = nullptr; listToMove.size = 0; };
	MyTwoLinkedList<T>& operator=(const MyTwoLinkedList<T>& listToCopy);
	MyTwoLinkedList<T>& operator=(MyTwoLinkedList<T>&& listToMove); 

	~MyTwoLinkedList() {
		terminate();
	}

	Iterator begin()  { return Iterator(head); }
	Iterator end()  { return Iterator(nullptr); }

	Iterator rbegin()  { return Iterator(tail); }
	Iterator rend()  { return Iterator(nullptr); }

	bool isEmpty() const { return !head; }
	size_t len() const { return size; }
	
	T& getFront() { return head->getData(); }
	const T& getFront() const { return head->getData(); }

	T& getBack() { return tail->getData(); }
	const T& getBack() const { return tail->getData(); }

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	void pushFront(T itemToPush);
	void pushBack(T itemToPush);

	T popFront();
	T popBack();

	void del(T itemToDel);
	T remove(size_t index);
	void terminate();

	void insert(size_t index, T itemToInsert);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyTwoLinkedList<T>& listToOutput);
private:
	MyNode<T>* head, *tail;
	size_t size;
};

 template<typename T>
 MyTwoLinkedList<T>::MyTwoLinkedList(const MyTwoLinkedList<T>& listToCopy){
	if (listToCopy.isEmpty()) {
		head = tail = nullptr;
		size = 0;
		return;
	}
	MyNode<T>* temp = listToCopy.head;
	head = new MyNode<T>(temp->getData());
	MyNode<T>* temp1 = head;
	temp = temp->getNext();
	while (temp != nullptr) {
		temp1->setNext(new MyNode<T>(temp->getData()));
		temp1->getNext()->setPrevious(temp1);
		temp1 = temp1->getNext();
		temp = temp->getNext();
	}
	size = listToCopy.size;
	tail = temp1;
 }

 template<typename T>
 MyTwoLinkedList<T>& MyTwoLinkedList<T>::operator=(const MyTwoLinkedList<T>& listToCopy){
	if (this == &listToCopy) { return *this; }
	terminate();
	MyNode<T>* temp = listToCopy.head;
	head = new MyNode<T>(temp->getData());
	MyNode<T>* temp1 = head;
	temp = temp->getNext();
	while (temp != nullptr) {
		temp1->setNext(new MyNode<T>(temp->getData()));
		temp1->getNext()->setPrevious(temp1);
		temp1 = temp1->getNext();
		temp = temp->getNext();
	}
	tail = temp1;
	size = listToCopy.size;
	return *this;
 }

 template <typename T>
 MyTwoLinkedList<T>& MyTwoLinkedList<T>::operator=(MyTwoLinkedList<T>&& listToMove) {
	if (this == &listToMove) { return *this; }
	terminate();
	head = listToMove.head;
	tail = listToMove.tail;
	size = listToMove.size;
	listToMove.head = listToMove.tail = nullptr;
	listToMove.size = 0;
	return *this;
 }

 template<typename T>
 const T& MyTwoLinkedList<T>::operator[](size_t index) const {
	 if (index > size) { throw std::out_of_range("The index out of range!"); }
	 MyNode<T>* temp = nullptr;
	 if (index <= (size - 1) / 2) {
		 temp = head;
		 for (size_t i = 0; i < index; ++i) { temp = temp->getNext(); }
	 }
	 else {
		 temp = tail;
		 for (size_t i = size - 1; i > index; --i) { temp = temp->getPrevious(); }
	 }
	 return temp->getData();
 }

 template<typename T>
T& MyTwoLinkedList<T>::operator[](size_t index) {
	 if (index > size) { throw std::out_of_range("The index out of range!"); }
	 MyNode<T>* temp = nullptr;
	 if (index <= (size - 1) / 2) {
		 temp = head;
		 for (size_t i = 0; i < index; ++i) { temp = temp->getNext(); }
	 }
	 else {
		 temp = tail;
		 for (size_t i = size - 1; i > index; --i) { temp = temp->getPrevious(); }
	 }
	 return temp->getData();
 }

 template<typename T>
 void MyTwoLinkedList<T>::pushFront(T itemToPush) {
	MyNode<T>* temp = new MyNode<T>(itemToPush);
	if (!head) { tail = temp; }
	else { head->setPrevious(temp); }
	temp->setNext(head);
	head = temp;
	++size;
 }

 template<typename T>
 void MyTwoLinkedList<T>::pushBack(T itemToPush) {
	MyNode<T>* temp = new MyNode<T>(itemToPush);
	if (!head) { head = temp; }
	else { tail->setNext(temp); }
	temp->setPrevious(tail);
	tail = temp;
	++size;
 }

 template<typename T>
 T MyTwoLinkedList<T>::popFront(){
	 if (isEmpty()) { throw std::runtime_error("the list is already empty"); }
	 MyNode<T>* temp = head;
	 T dataToReturn = temp->getData();
	 if (!(head->getNext())) { tail = nullptr; }
	 else { head->getNext()->setPrevious(nullptr); }
	 head = head->getNext();
	 delete temp;
	 --size;
	 return dataToReturn;
 }

 template<typename T>
 T MyTwoLinkedList<T>::popBack() {
	 if (isEmpty()) { throw std::runtime_error("the list is already empty"); }
	 MyNode<T>* temp = tail;
	 T dataToReturn = temp->getData();
	 if (!(tail->getPrevious())) { head = nullptr; }
	 else { tail->getPrevious()->setNext(nullptr); }
	 tail = tail->getPrevious();
	 delete temp;
	 --size;
	 return dataToReturn;
 }

 template<typename T>
 void MyTwoLinkedList<T>::del(T itemToDel) {
	if (isEmpty()) { throw std::runtime_error("the list is already empty"); }
	MyNode<T>* temp = head;
	while (temp->getData() != itemToDel) {
		temp = temp->getNext();
		if (!temp) { return; }
	}
	if (temp == head) { head = head->getNext(); }
	else { temp->getPrevious()->setNext(temp->getNext()); }
	if (temp == tail) { tail = tail->getPrevious(); }
	else { temp->getNext()->setPrevious(temp->getPrevious()); }
	delete temp;
	--size;
 }

 template<typename T>
 T MyTwoLinkedList<T>::remove(size_t index){
	 if (index >= size) { throw std::out_of_range("The index out of range!"); }
	 MyNode<T>* temp = nullptr;
	 if (index <= (size - 1) / 2) {
		 temp = head;
		 for (size_t i = 0; i < index; ++i) { temp = temp->getNext(); }
	 }
	 else {
		 temp = tail;
		 for (size_t i = size - 1; i > index; --i) { temp = temp->getPrevious(); }
	 }
	 T dataToReturn = temp->getData();
	 if (temp == head) { head = head->getNext(); }
	 else { temp->getPrevious()->setNext(temp->getNext()); }
	 if (temp == tail) { tail = tail->getPrevious(); }
	 else { temp->getNext()->setPrevious(temp->getPrevious()); }
	 delete temp;
	 --size;
	 return dataToReturn;
 }

 template<typename T>
 void MyTwoLinkedList<T>::terminate(){
	 MyNode<T>* temp = head;
	 MyNode<T>* temp1 = temp;
	 while (temp) {
		 temp1 = temp;
		 temp = temp->getNext();
		 delete temp1;
	 }
	 head = tail = nullptr;
	 size = 0;
 }

 template<typename T>
 void MyTwoLinkedList<T>::insert(size_t index, T itemToInsert){
	if (index > size) { throw std::out_of_range("The index out of range!"); }
	if (index == 0) {
		pushFront(itemToInsert);
		return;
	}
	else if (index == size) {
		pushBack(itemToInsert);
		return;
	}
	else {
		MyNode<T>* temp = nullptr;
		if (index <= (size - 1) / 2) {
			temp = head;
			for (size_t i = 0; i < index; ++i) { temp = temp->getNext(); }
		}
		else {
			temp = tail;
			for (size_t i = size - 1; i > index; --i) { temp = temp->getPrevious(); }
		}
		MyNode<T>* temp1 = new MyNode<T>(itemToInsert);
		temp->getPrevious()->setNext(temp1);
		temp1->setPrevious(temp->getPrevious());
		temp1->setNext(temp);
		temp->setPrevious(temp1);
		++size;
	}
 }
 
 template<typename T>
 inline std::ostream& operator<<(std::ostream& os, const MyTwoLinkedList<T>& listToOutput)
 {
	 MyNode<T>* temp = listToOutput.head;
	 for (size_t i = 0; i < listToOutput.size; ++i) {
		 if (i < listToOutput.size - 1) { os << temp->getData() << ", "; }
		 else { os << temp->getData() << ". "; }
		 temp = temp->getNext();
	 }
	 return os;
 }

 #endif // !MYTWOLINKEDLIST_H_

 
