#pragma once
#include "NodeDouble.h"

class StackDouble
{
	NodeDouble* head;
public:
	int size;
	StackDouble();
	~StackDouble();
	bool isEmpty();
	void push(double value);
	double pop();
	double top();
	void display();

};

