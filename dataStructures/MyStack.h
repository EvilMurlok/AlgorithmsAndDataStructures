#ifndef MYSTACK_H_
#define MYSTACK_H_

#include<iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class MyStack {
private:
	int top;
	const size_t maxSize;
	T* data;
public:
	MyStack() : top{ -1 }, maxSize{ 64 }, data{ new T[64] } {};
	explicit MyStack(size_t max) : top{ -1 }, maxSize{ max }, data{ new T[max] } {};
	
	explicit MyStack(size_t max, T elemToFill) : top{ max - 1 }, maxSize{ max }, data{ new T[max] }{
		for (size_t i = 0; i < max; ++i) {
			data[i] = elemToFill;
		}
	}
	
	MyStack(const MyStack<T>& stackToCopy) : top{ stackToCopy.top }, maxSize{ stackToCopy.maxSize }, data{ new T[maxSize] } {
		for (size_t i = 0; i <= top; ++i) {
			data[i] = stackToCopy.data[i];
		}
	}

	MyStack(MyStack<T>&& stackToMove) noexcept : top{ stackToMove.top }, maxSize{ stackToMove.maxSize }, data{ stackToMove.data } { stackToMove.data = nullptr; };

	MyStack(const std::initializer_list<T> list) : MyStack(list.size()) {
		for (auto& item : list) {
			data[++top] = item;
		}
	}

	~MyStack() {
		delete[] data;
	}

	void push(T itemToPush);

	T peek() const;

	size_t size() const { return top + 1; };

	T pop();

	bool isEmpty() const { return top < 0; };
	bool isFull() const { return top == maxSize - 1; };

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyStack<T>& stackToOut);
};

template <typename T>
void MyStack<T>::push(T itemToPush) {
	if (top == maxSize - 1) {
		std::cerr << "stack overflow! " << std::endl;
	}
	else {
		data[++top] = itemToPush;
	}
}

template <typename T>
T MyStack<T>::peek() const {
	if (top < 0) {
		throw std::runtime_error("stack is empty!");
	}
	else {
		return data[top];
	}
}

template<typename T>
T MyStack<T>::pop()
{
	if (top < 0) {
		throw std::runtime_error("stack is empty!");
	}
	else {
		return data[top--];
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyStack<T>& stackToOut) {
	for (int i = stackToOut.top; i >= 0; --i) {
		os << stackToOut.data[i] << " ";
	}
	return os;
}
#endif // !MYSTACK_H_
