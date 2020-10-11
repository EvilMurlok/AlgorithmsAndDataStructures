#ifndef MYDEQUE_H_
#define MYDEQUE_H_

#include <iostream>
#include <stdexcept>
#include <initializer_list>


//cyclic deque
template <typename T>
class MyDeque
{
public:
	MyDeque<T>() : data{ new T[32] }, maxSize{ 32 }, size{ 0 }, begin{ 32 }, end{ -1 } {};

	explicit MyDeque(size_t max) : maxSize{ max }, data{ new T[max] }, size{ 0 }, begin{ static_cast<int>(max) }, end{ -1 } {};
	explicit MyDeque(size_t max, T elemToFill) : maxSize{ max }, size{ max }, begin{ 0 }, end{ max - 1 } {
		for (size_t i = 0; i < size; ++i) {
			data[i] = elemToFill;
		}
	}

	//inizialization-list
	MyDeque(const std::initializer_list<T>& list) : MyDeque(list.size()) {
		for (auto& item : list) {
			data[size++] = item;
		}
	}

	//copy-constructor
	MyDeque(const MyDeque<T>& dequeToCopy) : maxSize{ dequeToCopy.maxSize }, size{ dequeToCopy.size },
		begin{ dequeToCopy.begin }, end{ dequeToCopy.end }, data{ new T[size] } {
		for (size_t i = 0; i < size; ++i) {
			data[i] = dequeToCopy.data[i];
		}
	}

	//move-constructor
	MyDeque(MyDeque<T>&& dequeToMove) : maxSize{ dequeToMove.maxSize }, size{ dequeToMove.size },
		begin{ dequeToMove.begin }, end{ dequeToMove.end }, data{ dequeToMove.data } {dequeToMove.data = nullptr; }

	//destructor
	virtual ~MyDeque() { 
		std::cout << "MyDeque destructor called!" << std::endl;
		delete[] data; 
	}

	T& front() { return data[begin]; }
	T& back() { return data[end]; }

	//You should use these methods before inserting or deleting!!!
	bool isFull() const { return maxSize == size; }
	bool isEmpty() const { return size == 0; }

	size_t len() { return size; }

	void insertFront(T itemToInsert);
	void insertBack(T itemToInsert);

	T popBack();
	T popFront();

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyDeque<T>& dequeToOut);
private:
	T* data;
	const size_t maxSize;
	size_t size;
	int begin;
	int end;
};

template<typename T>
void MyDeque<T>::insertFront(T itemToInsert){
	if (maxSize == size) {
		throw std::runtime_error("the deque is full");
	}
	if (begin == 0) {
		begin = maxSize;
	}
	data[--begin] = itemToInsert;
	++size;
}

template <typename T>
void MyDeque<T>::insertBack(T itemToInsert) {
	if (maxSize == size) {
		throw std::runtime_error("the deque is full");
	}
	if (end == maxSize - 1) {
		end = -1;
	}
	data[++end] = itemToInsert;
	++size;
}

template<typename T>
T MyDeque<T>::popBack(){
	if (size == 0) {
		throw std::runtime_error("the deque is empty");
	}
	if (end == -1) {
		end = maxSize - 1;
	}
	T temp = data[end--];
	--size;
	return temp;
}

template<typename T>
T MyDeque<T>::popFront(){
	if (size == 0) {
		throw std::runtime_error("the deque is empty");
	}
	if (begin == maxSize) {
		begin = 0;
	}
	T temp = data[begin++];
	--size;
	return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyDeque<T>& dequeToOut)
{
	if (dequeToOut.size == 0) {
		return os;
	}
	int i = dequeToOut.begin;
	int amount = dequeToOut.size;
	while (amount-- > 0) {
		if (i >= dequeToOut.maxSize) {
			i = 0;
		}
		if (amount != 0) {
			os << dequeToOut.data[i++] << ", ";
		}
		else {
			os << dequeToOut.data[i++] << ". ";
		}

	}
	return os;
}

#endif // !MYDEQUE_H_

