#pragma once

class ArrayList
{
	int* array;
	const int MIN_MERGE = 32;
	int capacity;
	void resize();
	int getMinRun();
	void insertionSort(int left, int right);
	void merge(int start, int mid, int end);
public:
	int size;
	ArrayList();
	~ArrayList();
	void add(int data);
	void print();
	void remove(int index);
	int get(int index);
	void timSort();
};

