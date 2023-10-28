#include "ArrayList.h"
#include <iostream>
using namespace std;

void ArrayList::resize()
{
	capacity *= 2;
	int* newArray = new int[capacity];
	for (int i = 0; i < size; i++) {
		newArray[i] = array[i];
	}
	delete[] array;
	array = newArray;
}

int ArrayList::getMinRun()
{
	int r = 0;
	int n = size;
	while (n >= MIN_MERGE) {
		r |= (n & 1);
		n >>= 1;
	}
	return n + r;
}

void ArrayList::insertionSort(int left, int right)
{
	for (int i = left + 1; i <= right; i++) {
		int key = array[i];
		int j = i - 1;
		while (j >= left && array[j] > key) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

void ArrayList::merge(int start, int mid, int end)
{
	int len1 = mid - start + 1;
	int len2 = end - mid;
	int* left = new int[len1];
	int* right = new int[len2];
	for (int i = 0; i < len1; i++)
		left[i] = array[start + i];
	for (int i = 0; i < len2; i++)
		right[i] = array[mid + 1 + i];
	int i = 0, j = 0, k = start;
	while (i < len1 && j < len2) {
		if (left[i] <= right[j]) {
			array[k] = left[i];
			i++;
		}
		else {
			array[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < len1) {
		array[k] = left[i];
		i++;
		k++;
	}
	while (j < len2) {
		array[k] = right[j];
		j++;
		k++;
	}
	delete[] left;
	delete[] right;
}

ArrayList::ArrayList()
{
	size = 0;
	capacity = 10;
	array = new int[capacity];
}

ArrayList::~ArrayList()
{
	delete[] array;
}

void ArrayList::add(int data)
{
	if (size >= capacity)
		resize();
	array[size++] = data;
}

void ArrayList::print()
{
	for (int i = 0; i < size; i++)
		cout << array[i] << ' ';
}

void ArrayList::remove(int index)
{
	if (index < 0 or index >= size) {
		cout << "Ошибка, индекс выходит за пределы" << '\n';
		return;
	}
	if (size == 0) {
		cout << "Ошибка, список пуст" << '\n';
		return;
	}
	for (int i = index; i < size - 1; i++)
		array[i] = array[i + 1];
	size--;
}

int ArrayList::get(int index)
{
	if (index < 0 || index >= size)
		return -1;
	return array[index];
}

void ArrayList::timSort()
{
	int minRun = getMinRun();
	for (int i = 0; i < size; i += minRun)
		insertionSort(i, min((i + minRun - 1), (size - 1)));
	int len = minRun;
	while (len < size) {
		for (int start = 0; start < size; start += 2 * len) {
			int mid = start + len - 1;
			int end = min((start + 2 * len - 1), (size - 1));
			merge(start, mid, end);
		}
		len *= 2;
	}

}
