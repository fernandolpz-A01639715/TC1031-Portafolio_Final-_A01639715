#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "LLNode.h"

template <class T>
class LinkedList {
  private:
    LLNode<T>* head;
    LLNode<T>* tail;
    int numElements;

  public:
    LinkedList();
    ~LinkedList();
    void addFirst(T value);
    void addLast(T value);
    LLNode<T>* getHead();
};

// Complejidad computacional: O(1)
template<class T>
LinkedList<T>::LinkedList() {
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
// Complejidad computacional: O(n)
LinkedList<T>::~LinkedList() {
  LLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
// Complejidad computacional: O(1)
void LinkedList<T>::addFirst(T value) {
  LLNode<T> *newLLNode = new LLNode<T>(value);
  newLLNode->next = head;
  head = newLLNode;
  if (numElements == 0) 
    tail = newLLNode;
  numElements++;    
}

template<class T>
// Complejidad computacional: O(n)
void LinkedList<T>::addLast(T value) {
  if (head == nullptr) {
    addFirst(value);
  }
  else {
    LLNode<T> *newLLNode = new LLNode<T>(value);
    newLLNode->next = nullptr;
    tail->next = newLLNode;
    tail = newLLNode;
    numElements++;
  }
}

template<class T>
// Complejidad computacional: O(1)
LLNode<T> * LinkedList<T>::getHead() {
  return head;
}

#endif // _LINKEDLIST_H_