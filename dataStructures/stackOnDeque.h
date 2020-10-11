#ifndef STACKONDEQUE_H_
#define STACKONDEQUE_H_

#include "MyDeque.h"

template <typename T>
class stackOnDeque : public MyDeque<T>
{
public:
	stackOnDeque<T>() : MyDeque<T>() {}
	stackOnDeque<T>(size_t max) : MyDeque<T>(max) {}
	stackOnDeque<T>(size_t max, T itemToFill) : MyDeque<T>(max, itemToFill) {}
	stackOnDeque<T>(const stackOnDeque<T>& stackToCopy) : MyDeque<T>(stackToCopy){}
	
	T popFront() = delete;
	void insertFront(T itemToInsert) = delete;
	
	void push(T itemToInsert) {
		this->insertBack(itemToInsert);
	}

	T pop() {
		
		return this->popBack();
	}

};

#endif // !STACKONDEQUE_H_

