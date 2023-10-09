#pragma once
#include "NodeChar.h"
class StackChar
{
	NodeChar* head;

public:
	int size;
	StackChar();
	~StackChar();
	bool isEmpty();
	void push(char value);
	char pop();
	char top();
	void display();
};

