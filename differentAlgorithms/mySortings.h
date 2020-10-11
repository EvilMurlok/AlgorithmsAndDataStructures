#ifndef MYSORTINGS_H_
#define MYSORTINGS_H_

#include <utility>
#include "MyArray.h"
#include "MyTwoLinkedList.h"

template <typename T>
void swap(T&& lhs, T&& rhs) {
	T temp{ std::move(lhs) };
	lhs = std::move(rhs);
	rhs = std::move(temp);
}

template <typename T>
void swap(T& lhs, T& rhs) {
	T temp{ lhs };
	lhs = rhs;
	rhs = temp;
}

//template<typename Sequence, typename fcn>
//int binarySearch()
template <typename Sequence, typename Comparison>
void bubbleSort(Sequence& seq, Comparison fcn) {
	for (size_t i = seq.len() - 1; i > 0; --i) {
		for (size_t j = 0; j < i; ++j) {
			if (fcn(seq[j], seq[j + 1])) {
				swap(seq[j], seq[j + 1]);
			}
		}
	}
}

template <typename Sequence, typename Comparison>
void shakerSort(Sequence& seq, Comparison fcn) {
	int left = 0, right = seq.len() - 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int j = left; j < right; ++j) {
			if (fcn(seq[j], seq[j + 1])) {
				swap(seq[j], seq[j + 1]);
				flag = true;
			}
		}
		--right;
		for (int j = right; j > left; --j) {
			if (fcn(seq[j - 1], seq[j])) {
				swap(seq[j - 1], seq[j]);
				flag = true;
			}
		}
		++left;
	}
}

template <typename Sequence, typename Comparison>
void selectionSort(Sequence& seq, Comparison fcn) {
	for (size_t i = 0; i < seq.len() - 1; ++i) {
		size_t min = i;
		for (size_t j = i + 1; j < seq.len(); ++j) {
			if (fcn(seq[j], seq[min])) {
				min = j;
			}
		}
		swap(seq[i], seq[min]);
	}
}

template <typename Sequence, typename Comparison>
void insertionSort(Sequence& seq, Comparison fcn) {
	for (size_t i = 1; i < seq.len(); ++i) {
		auto temp = seq[i];
		size_t j = i;
		while (j > 0 && fcn(temp, seq[j - 1])) {
			seq[j] = seq[j - 1];
			--j;
		}
		seq[j] = temp;
	}
}

template <typename Sequence, typename Comparison>
void gnomeSort(Sequence& seq, Comparison fcn) {
	size_t i = 0;
	while (i < seq.len()) {
		if (i == 0 || !fcn(seq[i - 1], seq[i])) { ++i; }
		else { 
			swap(seq[i - 1], seq[i]);
			--i;
		}
	}
}

template<typename Sequence, typename Comparison>
void mergeForSort(Sequence& seq, Sequence workSpace, size_t lowPtr, size_t highPtr, size_t upperBound, Comparison fcn) {
	size_t j = 0;
	size_t lowerBound = lowPtr;
	size_t mid = highPtr - 1;
	while (lowPtr <= mid && highPtr <= upperBound) {
		if (fcn(seq[lowPtr], seq[highPtr])) {
			workSpace[j++] = seq[lowPtr++];
		}
		else {
			workSpace[j++] = seq[highPtr++];
		}
	}
	while (lowPtr <= mid) {
		workSpace[j++] = seq[lowPtr++];
	}
	while (highPtr <= upperBound) {
		workSpace[j++] = seq[highPtr++];
	}
	for (j = 0; j < upperBound - lowerBound + 1; ++j) {
		seq[lowerBound + j] = workSpace[j];
	}
}

template <typename Sequence, typename Comparison>
void recMergeSort(Sequence& seq, Sequence workSpace, size_t lowerBound, size_t upperBound, Comparison fcn) {
	if (lowerBound == upperBound) {
		return;
	}
	else {
		size_t mid = (lowerBound + upperBound) / 2;
		recMergeSort(seq, workSpace, lowerBound, mid, fcn);
		recMergeSort(seq, workSpace, mid + 1, upperBound, fcn);
		mergeForSort(seq, workSpace, lowerBound, mid + 1, upperBound, fcn);
	}
}

template <typename Sequence, typename Comparison>
void mergeSort(Sequence& seq, Comparison fcn) {
	Sequence workSpace(seq.len());
	recMergeSort(seq, workSpace, 0, seq.len() - 1, fcn);
}

template <typename Sequence, typename Comparison>
void ShellSort(Sequence& seq, Comparison fcn) {
	int h = 1;
	while (h <= seq.len()) {
		h = h * 3 + 1;
	}
	while (h > 0) {
		for (int out = h; out < seq.len(); ++out) {
			auto temp = seq[out];
			int in = out;
			while (in > h - 1 && fcn(seq[in - h], temp)) {
				seq[in] = seq[in - h];
				in -= h;
			}
			seq[in] = temp;
		}
		h = (h - 1) / 3;
	}
}

//функция сортировки
template <typename Sequence, typename Comparison>
void quickSort(Sequence& seq, int first, int last, Comparison fcn) {
	int f = first, l = last;
	auto mid = seq[(f + l) / 2]; //вычисление опорного элемента
	do {
		while (fcn(seq[f], mid)) ++f;
		while (seq[l] != mid && !fcn(seq[l], mid)) --l;
		if (f <= l) { //перестановка элементов
			auto count = seq[f];
			seq[f] = seq[l];
			seq[l] = count;
			++f;
			--l;
		}
	} while (f < l);
	if (first < l) quickSort(seq, first, l, fcn);
	if (f < last) quickSort(seq, f, last, fcn);
}

#endif
