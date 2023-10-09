#pragma once
#include <iostream>
#include "Node.h"

class LinkedList
{
	Node* head, * tail;
public:
	int size;
	LinkedList();
	~LinkedList();
	Node* push_front(int data);
	Node* push_back(int data);
	void display();
	Node* get(int index);
	Node* insert(int data, int index);
	void remove(int index);
};

