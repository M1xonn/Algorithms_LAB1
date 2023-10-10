#include "StackDouble.h"
#include <iostream>
using namespace std;
StackDouble::StackDouble()
{
	head = NULL;
	size = 0;
}

StackDouble::~StackDouble()
{
	while (size != 0)
		pop();
}

bool StackDouble::isEmpty()
{
	return head==NULL;
}

void StackDouble::push(double value)
{
	NodeDouble* newNode = new NodeDouble;
	newNode->value = value;
	newNode->next = head;
	size++;
	head = newNode;
}

double StackDouble::pop()
{
	if (isEmpty()) {
		cout << "Stack is empty" << '\n';
		return -1;
	}
	NodeDouble* temp = head;
	double popValue = temp->value;
	head = head->next;
	size--;
	delete temp;
	return popValue;
	return 0;
}

double StackDouble::top()
{
	if (head != NULL)
		return head->value;
}

void StackDouble::display()
{
	NodeDouble* temp = head;
	while (temp != NULL) {
		cout << temp->value << ' ';
		temp = temp->next;
	}
	cout << '\n';
}
