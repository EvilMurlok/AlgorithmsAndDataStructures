#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class MyQueue {
private:
	size_t maxSize;
	size_t _size;
	T* data;
	int begin;
	int end;

public:
	MyQueue() : maxSize{ 32 }, _size{ 0 },  data{ new T[32] }, begin{ 0 }, end{ -1 } {};
	explicit MyQueue(size_t max) : maxSize{ max }, _size{ 0 }, data{ new T[max] }, begin{ 0 }, end{ -1 } {};
	explicit MyQueue(size_t max, T elemToFill) : maxSize{ max }, _size{ max }, data{ new T[maxSize] }, begin{ 0 }, end{ max - 1 } {
		for (size_t i = 0; i < _size; ++i) {
			data[i] = elemToFill;
		}
	}
	
	//inizialization-list
	MyQueue(const std::initializer_list<T>& list) : MyQueue(list.size()) {
		for (auto& item : list) {
			data[_size++] = item;
		}
	}

	//copy-constructor
	MyQueue(const MyQueue<T>& queueToCopy) : maxSize{ queueToCopy.maxSize }, _size{ queueToCopy._size }, 
											data{ new T[maxSize] }, begin{ queueToCopy.begin }, end{ queueToCopy.end } {
		int i = queueToCopy.begin;
		int amount = queueToCopy._size;
		while (amount-- > 0) {
			if (i >= queueToCopy.maxSize) {
				i = 0;
			}
			data[i] = queueToCopy.data[i];
			++i;
		}
	}

	//move-constructor
	MyQueue(MyQueue<T>&& queueToMove) : maxSize{ queueToMove.maxSize }, _size{ queueToMove._size },
										data{ queueToMove.data }, begin{ queueToMove.begin }, end{ queueToMove.end } {
		queueToMove.data = nullptr; 
		queueToMove._size = 0; 
	}

	MyQueue<T>& operator=(const MyQueue<T>& queueToCopy) {
		if (this == &queueToCopy) { return *this; }
		maxSize = queueToCopy.maxSize;
		_size = queueToCopy._size;
		begin = queueToCopy.begin;
		end = queueToCopy.end;
		delete[] data;
		data = new T[maxSize];
		int i = queueToCopy.begin;
		int amount = queueToCopy._size;
		while (amount-- > 0) {
			if (i >= queueToCopy.maxSize) {
				i = 0;
			}
			data[i] = queueToCopy.data[i];
			++i;
		}
		return *this;
	}

	MyQueue<T>& operator=(MyQueue<T>&& queueToMove) {
		delete[] data;
		data = queueToMove.data;
		_size = queueToMove._size;
		maxSize = queueToMove.maxSize;
		begin = queueToMove.begin;
		end = queueToMove.end;
		queueToMove.data = nullptr;
		queueToMove._size = queueToMove.maxSize = queueToMove.begin = queueToMove.end = 0;
		return *this;
	}

	//destructor
	~MyQueue() { delete[] data;	}

	void insert(T itemToInsert);

	//please use this function to check the queue before the removing or getting the fron or back element
	bool isEmpty() const { return _size == 0; }	
	//please use this function to check the queue before the insertion
	bool isFull() const { return _size == maxSize; }

	T front() const {
		if (_size > 0) {
			return data[begin];
		}
		else {
			throw std::runtime_error("queue is empty!");
		}
	}

	T back() const {
		if (_size > 0) {
			return data[end];
		}
		else {
			throw std::runtime_error("queue is empty!");
		}
	}

	T pop();

	size_t size() const { return _size; }

	void cleanQueue() {
		delete[] data;
		data = new T[maxSize];
		_size = 0;
	}
	/*
	only for logging! don't use it!
	int logEnd() const { return end; }
	int logBeg() const { return begin; }
	*/

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyQueue<T>& queuetoOut);
};

template <typename T>
void MyQueue<T>::insert(T itemToInsert) {
	if (_size >= maxSize) {
		throw std::runtime_error("The queue is full!");
	}
	if (end == maxSize - 1) {
		end = -1;
	}
	data[++end] = itemToInsert;
	++_size;
}

template <typename T> 
T MyQueue<T>::pop() {
	if (_size == 0) {
		throw std::runtime_error("the Queue is empty!");
	}
	T temp = data[begin++];
	if (begin >= maxSize) {
		begin = 0;
	}
	--_size;
	return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyQueue<T>& queuetoOut)
{
	if (queuetoOut._size == 0) {
		return os;
	}
	int i = queuetoOut.begin;
	int amount = queuetoOut._size;
	while (amount-- > 0) {
		if (i >= queuetoOut.maxSize) {
			i = 0;
		}
		if (amount != 0) {
			os << queuetoOut.data[i++] << ", ";
		}
		else {
			os << queuetoOut.data[i++] << ". ";
		}
		
	}
	return os;
}

#endif // !MYQUEUE_H_


