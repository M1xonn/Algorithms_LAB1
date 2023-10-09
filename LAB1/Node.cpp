#include "Node.h"
#include <iostream>

Node::Node(int data) {
	this->data = data;
	this->prev = this->next = NULL;
}