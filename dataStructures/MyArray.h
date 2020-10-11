#ifndef MYARRAY_H_
#define MYARRAY_H_

#include <stdexcept>
#include <cassert>
#include <iostream>
#include <initializer_list>

template <typename T>
class MyArray {
private:
	size_t size;
	size_t capasity;
	T* arr;

	void swap(size_t lhs, size_t rhs) {
		T temp = arr[lhs];
		arr[lhs] = arr[rhs];
		arr[rhs] = temp;
	}

public:
	MyArray() : size{ 0 }, capasity{ 0 }, arr{ nullptr } {};
	
	explicit MyArray(size_t sz) : size{ sz }, capasity{ sz }, arr{ new T[sz] } {
		for (size_t i = 0; i < size; ++i) {
			arr[i] = T();
		}
	};
	
	explicit MyArray(size_t sz, T itemToFill) : size{ sz }, capasity{ sz }, arr{ new T[sz] } {
		for (size_t i = 0; i < size; ++i) {
			arr[i] = itemToFill;
		}
	}

	MyArray(const std::initializer_list<T>& list) : MyArray(list.size()) {
		size_t i = 0;
		for (auto& item : list) {
			arr[i++] = item;
		}
	}

	MyArray(const MyArray<T>& arrToCopy) : size{ arrToCopy.size }, capasity{ arrToCopy.capasity }, arr{ new T[capasity] }{
		if (size % 2) {
			for (size_t i = 0; i < size / 2; ++i) {
				arr[i] = arrToCopy.arr[i];
				arr[size - i - 1] = arrToCopy.arr[size - i - 1];
			}
			arr[size / 2] = arrToCopy.arr[size / 2];
		}
		else {
			for (size_t i = 0; i < size / 2; ++i) {
				arr[i] = arrToCopy.arr[i];
				arr[size - i - 1] = arrToCopy.arr[size - i - 1];
			}
		}
	}

	MyArray(MyArray&& arrToMove) : size{ arrToMove.size }, capasity{ arrToMove.capasity },  arr{ arrToMove.arr } 
	{arrToMove.arr = nullptr; arrToMove.size = 0; }

	~MyArray() { delete[] arr; }

	size_t len() const { return size; }

	bool empty() const { return !size; }

	void pushBack(T itemToInsert);

	void popBack();

	//returns the first index of itemToFind (if there is no such element, returns -1)
	int binarySearch(T itemToFind) const;
	
	//returns the last index of itemToFind (if there is no such element, returns -1)
	int rBinarySearch(T itemToFind) const;

	//returns the first index of itemToFind (if there is no such element, returns -1)
	//different searches: lenear or binary
	int find(T itemToFind) const;

	T getMax() const; 

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	MyArray<T>& operator=(const MyArray<T>& arrToCopy);
	MyArray<T>& operator=(MyArray<T>&& arrToMove);

	void insert(T itemToInsert);

	void remove(size_t indexForRemoving);

	//delete the first itemToDel
	void del(T itemToDel);

	//delete all itemsToDel
	void delAll(T itemsToDel);

	//fucking bubble-sort
	void bubbleSort();

	void oddEvenSort();

	//fucking selection-sort
	void selectionSort();

	void insertionSort();

	//delete all dubs of all elements
	void noDubs();

	//delete all dubs of certain element
	void noDubs(T itemNoDubs);

	//merge
	void mergeArrs(const MyArray<T>& lhs, const MyArray<T>& rhs);

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyArray<T>& arrToOutput);
	template <typename T>
	friend bool operator<(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator>(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator==(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator!=(const MyArray<T>& lhs, const MyArray<T>& rhs);
};

template <typename T>
void MyArray<T>::pushBack(T itemToInsert) {
	if (size >= capasity) {
		capasity = (capasity) ? capasity * 2 : 1;
		T* newArr = new T[capasity];
		for (size_t i = 0; i < size; ++i) {
			newArr[i] = arr[i];
		}
		newArr[size++] = itemToInsert;
		T* arrToDel = arr;
		arr = newArr;
		delete[] arrToDel;
	}
	else {
		arr[size++] = itemToInsert;
	}
}

template <typename T>
int MyArray<T>::binarySearch(T itemToFind) const {
	int left = -1, right = size;
	while (left + 1 < right) {
		int middle = (left + right) / 2;
		if (arr[middle] < itemToFind) {
			left = middle;
		}
		else {
			right = middle;
		}
	}

	if (right < size && arr[right] == itemToFind) { return right; }
	else { return -1; }
}

//returns the last index of itemToFind (if there is no such element, returns -1)
template <typename T>
int MyArray<T>::rBinarySearch(T itemToFind) const {
	int left = -1, right = size;
	while (left + 1 < right) {
		int middle = (left + right) / 2;
		if (arr[middle] <= itemToFind) {
			left = middle;
		}
		else {
			right = middle;
		}
	}
	if (left >= 0 && arr[left] == itemToFind) { return left; }
	else { return -1; }
}

//returns the first index of itemToFind (if there is no such element, returns -1)
//different searches: lenear or binary
template <typename T>
int MyArray<T>::find(T itemToFind) const {
	size_t i = 0;
	for (i; i < size; ++i) {
		if (arr[i] == itemToFind) { break; }
	}
	if (i == size) { return -1; }
	else { return i; }
}

template <typename T>
const T& MyArray<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("index was out of range!");
	}
	else {
		return arr[index];
	}
}

template <typename T>
T& MyArray<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("index was out of range!");
	}
	else {
		return arr[index];
	}
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T>& arrToCopy) {
	if (this == &arrToCopy) {
		return *this;
	}
	size = arrToCopy.size;
	capasity = arrToCopy.capasity;
	delete[] arr;
	arr = new T[capasity];
	for (size_t i = 0; i < size; ++i) {
		arr[i] = arrToCopy.arr[i];
	}
	return *this;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray<T>&& arrToMove) {
	if (this == &arrToMove) {
		return *this;
	}
	size = arrToMove.size;
	capasity = arrToMove.capasity;
	delete[] arr;
	arr = arrToMove.arr;
	arrToMove.arr = nullptr;
	return *this;
}

template <typename T>
void MyArray<T>::insert(T itemToInsert) {
	if (size >= capasity) {
		capasity = (capasity) ? capasity * 2 : 1;
		T* newArr = new T[capasity];
		for (size_t i = 0; i < size; ++i) {
			newArr[i] = arr[i];
		}
		newArr[size++] = itemToInsert;
		T* arrToDel = arr;
		arr = newArr;
		delete[] arrToDel;
	}
	else {
		arr[size++] = itemToInsert;
	}
}

template <typename T>
void MyArray<T>::popBack() {
	if (!(size && capasity)) {
		throw std::runtime_error("array is already empty!");
	}
	T* newArr = new T[capasity];
	for (size_t i = 0; i < size - 1; ++i) {
		newArr[i] = arr[i];
	}
	--size;
	T* arrToDel = arr;
	arr = newArr;
	delete[] arrToDel;
}

template <typename T>
void MyArray<T>::remove(size_t indexForRemoving) {
	if (indexForRemoving < 0 || indexForRemoving >= size) {
		throw std::out_of_range("index was out of range!");
	}
	T* newArr = new T[capasity];
	size_t i = 0;
	for (i; i < indexForRemoving; ++i) {
		newArr[i] = arr[i];
	}
	for (i; i < size - 1; ++i) {
		newArr[i] = arr[i + 1];
	}
	--size;
	T* arrToDell = arr;
	arr = newArr;
	delete[] arrToDell;
}

template <typename T>
void MyArray<T>::del(T itemToDel) {
	int index = find(itemToDel);
	if (index >= 0) {
		remove(index);
	}
}

template <typename T> 
void MyArray<T>::delAll(T itemsToDel) {
	T* newArr = new T[capasity];
	size_t j = 0;
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] != itemsToDel) {
			newArr[j++] = arr[i];
		}
	}
	size = j;
	T* arrToDel = arr;
	arr = newArr;
	delete[] arrToDel;
}

template <typename T>
T MyArray<T>::getMax() const {
	if (!empty()) {
		T max = arr[0];
		for (size_t i = 1; i < size; ++i) {
			if (max < arr[i]) {
				max = arr[i];
			}
		}
		return max;
	}
	else {
		throw std::runtime_error("Array is empty!");
	}
}

template <typename T>
void MyArray<T>::bubbleSort() {
	int left = 0, right = size - 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int j = left; j < right; ++j) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = true;
			}
		}
		--right;
		for (int j = right; j > left; --j) {
			if (arr[j] < arr[j - 1]) {
				T temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				flag = true;
			}
		}
		++left;
	}

	/*
	//usual bubble-sort
	for (size_t i = size - 1; i > 0; --i) {
		for (size_t j = 0; j < i; ++j) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}*/
}

template<typename T>
void MyArray<T>::oddEvenSort(){
	bool flag = true;
	while (flag) {
		flag = false;
		for (size_t i = 1; i < size - 1; i += 2) {
			if (arr[i] > arr[i + 1]) {
				T temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = true;
			}
		}
		for (size_t i = 0; i < size - 1; i += 2) {
			if (arr[i] > arr[i + 1]) {
				T temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = true;
			}
		}
	}
}

template<typename T>
void MyArray<T>::selectionSort(){
	size_t indexOfMin = 0;
	for (size_t i = 0; i < size - 1; ++i) {
		indexOfMin = i;
		for (size_t j = i + 1; j < size; ++j) {
			if (arr[indexOfMin] > arr[j]) {
				indexOfMin = j;
			}
		}
		T temp = arr[i];
		arr[i] = arr[indexOfMin];
		arr[indexOfMin] = temp;
	}
}

template<typename T>
void MyArray<T>::insertionSort(){
	size_t j = 0;
	for (size_t i = 1; i < size; ++i) {
		T temp = arr[i];
		j = i;
		while (j > 0 && arr[j - 1] >= temp) {
			arr[j] = arr[j - 1];
			--j;
		}
		arr[j] = temp;
	}
}

template <typename T>
void MyArray<T>::noDubs() {
	if (!empty()){
		T* newArr = new T[capasity];
		newArr[0] = arr[0];
		size_t indexOfNewArr = 1;
		for (size_t i = 1; i < size; ++i) {
			size_t j = 0;
			for (j; j < indexOfNewArr; ++j) {
				if (arr[i] == newArr[j]) { break; }
			}
			if (j == indexOfNewArr) { newArr[indexOfNewArr++] = arr[i]; }
		}
		size = indexOfNewArr;
		T* arrToDell = arr;
		arr = newArr;
		delete[] arrToDell;
	}
}

template <typename T>
void MyArray<T>::noDubs(T itemNoDubs) {
	if (!empty()) {
		int left = find(itemNoDubs);
		if (left < 0) {
			return;
		}
		T* newArr = new T[capasity];
		size_t j = 0;
		for (size_t i = 0; i <= left; ++i) {
			newArr[j++] = arr[i];
		}
		for (size_t i = ++left; i < size; ++i) {
			if (arr[i] != itemNoDubs) {
					newArr[j++] = arr[i];
			}
		}
		size = j;
		T* arrToDell = arr;
		arr = newArr;
		delete[] arrToDell;
	}
}

template <typename T>
void MyArray<T>::mergeArrs(const MyArray<T>& arrA, const MyArray<T>& arrB) {
	if (arr) { 
		delete[] arr;
	}
	arr = new T[arrA.capasity + arrB.capasity];
	size = arrA.size + arrB.size;
	size_t aDex = 0, bDex = 0, cDex = 0;
	while (aDex < arrA.size && bDex < arrB.size) {
		if (arrA[aDex] < arrB[bDex]) {
			arr[cDex++] = arrA[aDex++];
		}
		else {
			arr[cDex++] = arrB[bDex++];
		}
	}
	while (aDex < arrA.size) {
		arr[cDex++] = arrA[aDex++];
	}
	while (bDex < arrB.size) {
		arr[cDex++] = arrB[bDex++];
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyArray<T>& arrToOutput) {
	for (size_t i = 0; i < arrToOutput.size; ++i) {
		os << arrToOutput.arr[i] << ' ';
	}
	return os;
}

template <typename T>
bool operator<(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	if (lhs.size < rhs.size) { return true; }
	else if (lhs.size > rhs.size) { return false; }
	else {
		for (size_t i = 0; i < lhs.size; ++i) {
			if (!(lhs.arr[i] < rhs.arr[i])) {
				return false;
			}
		}
		return true;
	}
}

template <typename T>
bool operator>(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator==(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return !(lhs < rhs || lhs > rhs);
}

template <typename T>
bool operator!=(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return !(lhs == rhs);
}
#endif // !MYARRAY_H_