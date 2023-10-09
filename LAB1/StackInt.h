#pragma once
#include "NodeInt.h"

class StackInt
{
	NodeInt* head;
public:
	int size;
	StackInt();
	~StackInt();
	bool isEmpty();
	void push(int value);
	int pop();
	int top();
	void display();

};

