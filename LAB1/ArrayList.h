#pragma once

class ArrayList
{
	int* array;
	int capacity;
	void resize();
public:
	int size;
	ArrayList();
	~ArrayList();
	void add(int data);
	void print();
	void remove(int index);
	int get(int index);

};

