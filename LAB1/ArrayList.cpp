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
