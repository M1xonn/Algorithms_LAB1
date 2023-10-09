#include "StackInt.h"
#include <iostream>
using namespace std;
StackInt::StackInt()
{
	head = NULL;
	size = 0;
}

StackInt::~StackInt()
{
	while (size != 0)
		pop();
}

bool StackInt::isEmpty()
{
	return head==NULL;
}

void StackInt::push(int value)
{
	NodeInt* newNode = new NodeInt;
	newNode->value = value;
	newNode->next = head;
	size++;
	head = newNode;
}

int StackInt::pop()
{
	if (isEmpty()) {
		cout << "Stack is empty" << '\n';
		return -1;
	}
	NodeInt* temp = head;
	int popValue = temp->value;
	head = head->next;
	size--;
	delete temp;
	return popValue;
	return 0;
}

int StackInt::top()
{
	if (head != NULL)
		return head->value;
}

void StackInt::display()
{
	NodeInt* temp = head;
	while (temp != NULL) {
		cout << temp->value << ' ';
		temp = temp->next;
	}
	cout << '\n';
}
