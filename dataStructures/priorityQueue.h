#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <stdexcept>
template <typename T>
class MyPriorityQueue
{
private:
	size_t _size;
	bool _less;
	const size_t _maxSize;
	T* _data;
public:
	MyPriorityQueue() : _size{ 0 }, _less{ true }, _maxSize{ 10 }, _data{ new T[10] } {};

	explicit MyPriorityQueue(size_t maxSize, bool less) : _size{ 0 }, _less{ less }, _maxSize{ maxSize }, _data{ new T[maxSize] } {};

	explicit MyPriorityQueue(size_t max, bool less, T elemToFill) : _size{ max }, _less{ less }, _maxSize{ max }, _data{ new T[max] } {
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = elemToFill;
		}
	}

	MyPriorityQueue(const MyPriorityQueue<T>& queueToCopy) : _size{ queueToCopy._size }, _less{ queueToCopy._less },
		_maxSize{ queueToCopy._maxSize }, _data{ new T[queueToCopy._maxSize] } {
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = queueToCopy._data[i];
		}
	}

	MyPriorityQueue(MyPriorityQueue<T>&& queueToMove) : _size{ queueToMove._size }, _less{ queueToMove._less },
		_maxSize{ queueToMove._maxSize }, _data{ queueToMove._data } { queueToMove._data = nullptr; }

	~MyPriorityQueue() { delete[] _data; }

	//please use this function to check the queue before the removing
	bool isEmpty() const { return _size == 0; }
	//please use this function to check the queue before the insertion
	bool isFull() const { return _size == _maxSize; }

	T front() const { 
		if (_size > 0) {
			return _data[_size - 1];
		}
		else {
			throw std::runtime_error("queue is empty!");
		}
	}

	T pop() {
		if (_size > 0) {
			return _data[--_size];
		}
		else {
			throw std::runtime_error("queue is empty!");
		}
	}
	
	void insert(T itemToInsert) {
		if (_size < _maxSize) {
			if (_size == 0) {
				_data[_size++] = itemToInsert;
				return;
			}
			if (_less) {
				int i = _size - 1;
				for (i; i >= 0; --i) {
					if (itemToInsert > _data[i]) {
						_data[i + 1] = _data[i];
					}
					else { break; }
				}
				_data[i + 1] = itemToInsert;
				++_size;
			}
			else {
				int i = _size - 1;
				for (i; i >= 0; --i) {
					if (itemToInsert < _data[i]) {
						_data[i + 1] = _data[i];
					}
					else { break; }
				}
				_data[i + 1] = itemToInsert;
				++_size;
			}
		}
		else {
			throw std::runtime_error("queue is full!");
		}
	}

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyPriorityQueue<T>& queueToOut);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyPriorityQueue<T>& queueToOut) {
	if (queueToOut._size == 0) {
		os << "The Queue is empty! ";
	}
	else {
		for (int i = queueToOut._size - 1; i >= 0; --i) {
			if (i > 0) {
				os << queueToOut._data[i] << ", ";
			}
			else {
				os << queueToOut._data[i] << ".";
			}
		}
	}
	return os;
}


#endif // !PRIORITYQUEUE_H_

