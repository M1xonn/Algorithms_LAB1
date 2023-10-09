#include "StackChar.h"
#include <iostream>
using namespace std;
StackChar::StackChar()
{
	head = NULL;
	size = 0;
}

StackChar::~StackChar()
{
	while (size != 0)
		pop();
}

bool StackChar::isEmpty()
{
	return head==NULL;
}

void StackChar::push(char value)
{
	NodeChar* newNode = new NodeChar;
	newNode->value = value;
	newNode->next = head;
	size++;
	head = newNode;
}

char StackChar::pop()
{
	if (isEmpty()) {
		cout << "Stack is empty" << '\n';
		return '0';
	}
	NodeChar* temp = head;
	char popValue = temp->value;
	head = head->next;
	size--;
	delete temp;
	return popValue;
}

char StackChar::top()
{
	if (head != NULL)
		return head->value;
}

void StackChar::display()
{
	while (head != NULL)
	{
		cout << head->value << " ";
		head = head->next;
	}
	cout << '\n';
}
