#include "LinkedList.h"
#include "Node.h"
#include <iostream>
using namespace std;



LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

LinkedList::~LinkedList()
{
    while (head != NULL)
        remove(0);
}

Node* LinkedList::push_front(int data)
{
    Node* newNode = new Node(data);
    newNode->next = head;
    if (head != NULL)
        head->prev = newNode;
    if (tail == NULL)
        tail = newNode;
    head = newNode;
    size++;
    return newNode;
}

Node* LinkedList::push_back(int data)
{
    Node* newNode = new Node(data);
    newNode->prev = tail;
    if (tail != NULL)
        tail->next = newNode;
    if (head == NULL)
        head = newNode;
    tail = newNode;
    size++;
    return newNode;
}

void LinkedList::display()
{
    Node* curr = head;
    cout << '\n';
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << '\n';
}

Node* LinkedList::get(int index)
{
    if (index < 0 or index >= size) {
        cout << "Ошибка, индекс выходит за пределы" << '\n';
        return NULL;
    }
    Node* newNode = head;
    int n = 0;
    while (n != index) {
        if (newNode == NULL)
            return newNode;
        newNode = newNode->next;
        n++;
    }
    return newNode;
}

Node* LinkedList::insert(int data, int index)
{
    Node* rightEl = get(index);
    if (rightEl == NULL)
        return push_back(data);
    Node* leftEl = rightEl->prev;
    if (leftEl == NULL)
        return push_front(data);
    Node* newNode = new Node(data);
    newNode->prev = leftEl;
    newNode->next = rightEl;
    leftEl->next = newNode;
    rightEl->prev = newNode;
    return newNode;
}

void LinkedList::remove(int index)
{
    if (index < 0 or index >= size) {
        cout << "Ошибка, индекс выходит за пределы" << '\n';
        return;
    }
    if (size == 0) {
        cout << "Ошибка, список пуст" << '\n';
        return;
    }
    Node* curr = get(index);
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    }
    else {
        head = curr->next;
    }
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }
    else {
        tail = curr->prev;
    }
    delete curr;
    size--;
}
 