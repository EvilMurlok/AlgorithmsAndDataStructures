#ifndef RECURSION_H_
#define RECURSION_H_

#include <iostream>
#include <string>
#include "MyArray.h"
#include <utility>
#include <vector>

//simple examples
unsigned long long sumFirstDigits(unsigned long long n) {
	if (n == 1) {
		return 1;
	}
	else {
		return n + sumFirstDigits(n - 1);
	}
}

unsigned long long Fibonachi(unsigned long long n) {
	if (n == 1 || n == 2) { return 1; }
	else { return Fibonachi(n - 1) + Fibonachi(n - 2); }
}

unsigned long long factorial(unsigned long n) {
	if (n == 0) { return 1; }
	else { return n * factorial(n - 1); }
}

long long power(long long x, unsigned long y) {
	if (y == 0LL) { return 1LL; }
	if (y % 2) { //the digit is odd
		return x * power(x, y - 1);
	}
	long long temp = power(x, y / 2);
	return temp * temp;
}

long long mult(long long x, long long y) {
	if (y == 0) {
		return 0;
	}
	else {
		return x + mult(x, y - 1);
	}
}

//Max weight i can carry away (indexing of the input array starts at one!!!)
template <typename Sequence>
int solutionAboutBackpack(const Sequence& arr, int targetWeight) {
	std::vector<std::vector<int>> dp(arr.len(), std::vector<int>(targetWeight + 1, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= arr.len() - 1; ++i) {
		for (int j = 0; j <= targetWeight; ++j) {
			if (arr[i] <= j) {
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i]];
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	for (int w = targetWeight; w >= 0; --w) {
		if (dp[arr.len() - 1][w] == 1) {
			return w;
		}
	}
	return 0;
}

class Anagramm
{
public:
	Anagramm(std::string w) : word{ w }, sizeWord{ word.size() } {};
	size_t len() const { return sizeWord; }
	void rotate(size_t newSize) {
		size_t j = 0;
		size_t position = sizeWord - newSize;
		char temp = word[position];
		for (j = position + 1; j < sizeWord; ++j) {
			word[j - 1] = word[j];
		}
		word[j - 1] = temp;
	}

	void doAnagram(size_t newSize) {
		if (newSize == 1) { return; }
		for (size_t i = 0; i < newSize; ++i) {
			doAnagram(newSize - 1);
			if (newSize == 2) {
				std::cout << word << std::endl;
			}
			rotate(newSize);
		}
	}
private:
	std::string word;
	size_t sizeWord;
};

template <typename Sequence>
void combinationUtil(Sequence arr, Sequence temp, size_t start, size_t end, size_t index, size_t r) {
	if (index == r) {
		for (size_t i = 0; i < r; ++i) {
			if (i == r - 1) {
				cout << temp[i] << '.';
			}
			else {
				cout << temp[i] << ", ";
			}
		}
		cout << endl;
		return;
	}
	for (size_t i = start; i <= end && end - i + 1 >= r - index; ++i) {
		temp[index] = arr[i];
		combinationUtil(arr, temp, i + 1, end, index + 1, r);
	}
}

template <typename Sequence>
void printCombination(Sequence arr, size_t n, size_t r) {
	Sequence temp(r);
	combinationUtil(arr, temp, 0, n - 1, 0, r);
}

/*without any recursion!*/
template <typename Sequence, typename T>
int rBinarySearch(Sequence seq, T itemToFind) {
	int left = -1, right = seq.len();
	while (left + 1 < right) {
		int mid = (left + right) / 2;
		if (seq[mid] <= itemToFind) { //инвариант относительно поиска элемента: ищем самый крайний правый элемент(на случай повтор€ющихс€)
			left = mid;
		}
		else {
			right = mid;
		}
	}
	if (left > -1 && seq[left] == itemToFind) {
		return left;
	}
	else { return -1; }
}

template <typename Sequence, typename T>
int lBinarySearch(Sequence seq, T itemToFind) {
	int left = -1, right = seq.len();
	while (left + 1 < right) {
		int mid = (left + right) / 2;
		if (seq[mid] < itemToFind) { //инвариант относительно поиска элемента: ищем самый крайний левый элемент(на случай повтор€ющихс€)
			left = mid;
		}
		else {
			right = mid;
		}
	}
	if (right < seq.len() && seq[right] == itemToFind) {
		return right;
	}
	else { return -1; }
}
/*it was written for repetition*/

template<typename Sequence, typename T>
int recBinarySearch(Sequence seq, T itemToFind, int lowerBound, int upperBound) {
	int mid = (lowerBound + upperBound) / 2;
	if (seq[mid] == itemToFind) {
		return mid;
	}
	else if (lowerBound > upperBound) { return -1; } //не найден!
	else {
		if (seq[mid] < itemToFind) {
			return recBinarySearch(seq, itemToFind, mid + 1, upperBound);
		}
		else {
			return recBinarySearch(seq, itemToFind, lowerBound, mid - 1);
		}
	}
}

/*the solution of the problem with the Hanoy towers*/
void doTowers(size_t amount, char from, char inter, char to) {
	if (amount == 1) {
		std::cout << "Disk 1 from " << from << " to " << to << std::endl;
	}
	else {
		doTowers(amount - 1, from, to, inter);
		std::cout << "Disk " << amount << " from " << from << " to " << to << std::endl;
		doTowers(amount - 1, inter, from, to);
	}
}

/*this function helps us to merge two containers*/
template <typename Sequence>
void merge(const Sequence& arrA, const Sequence& arrB, Sequence& arrC) {
	size_t aDex = 0, bDex = 0, cDex = 0;
	while (aDex < arrA.len() && bDex < arrB.len()) {
		if (arrA[aDex] < arrB[bDex]) {
			arrC[cDex++] = arrA[aDex++];
		}
		else {
			arrC[cDex++] = arrB[bDex++];
		}
	}
	while (aDex < arrA.len()) {
		arrC[cDex++] = arrA[aDex++];
	}
	while (bDex < arrB.len()) {
		arrC[cDex++] = arrB[bDex++];
	}
}

template<typename Sequence, typename Comparison>
void rMergeForSort(Sequence& seq, Sequence workSpace, size_t lowPtr, size_t highPtr, size_t upperBound, Comparison fcn) {
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
void rRecMergeSort(Sequence& seq, Sequence workSpace, size_t lowerBound, size_t upperBound, Comparison fcn) {
	if (lowerBound == upperBound) {
		return;
	}
	else {
		size_t mid = (lowerBound + upperBound) / 2;
		rRecMergeSort(seq, workSpace, lowerBound, mid, fcn);
		rRecMergeSort(seq, workSpace, mid + 1, upperBound, fcn);
		rMergeForSort(seq, workSpace, lowerBound, mid + 1, upperBound, fcn);
	}
}

template <typename Sequence, typename Comparison>
void rMergeSort(Sequence& seq, Comparison fcn) {
	Sequence workSpace(seq.len());
	rRecMergeSort(seq, workSpace, 0, seq.len() - 1, fcn);
}

#endif