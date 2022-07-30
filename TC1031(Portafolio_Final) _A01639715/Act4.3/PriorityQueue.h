#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <stdexcept>
#include <vector>
#include <map>
#include "ipAddress.h"

template <class T>
// MAX-HEAP
class PriorityQueue {
private:
  // contiene los elementos del heap
  std::vector<T> data;
  // capacidad maxima del heap
  int maxCapacity;
  // numero de elementos actualmente en el heap
  int numElements;
  // int numElements;
  int parent(int i);
  int left(int i);
  int right(int i);
  void heapify(int index);

public:
  PriorityQueue(int capacity);
  ~PriorityQueue();
  void push(T key);
  T top();
  void pop();
};

// Complejidad computacional: O(1)
template <class T> PriorityQueue<T>::PriorityQueue(int capacity) {
  numElements = 0;
  maxCapacity = capacity;
  data.resize(maxCapacity);
}

// Complejidad computacional: O(1)
template <class T> PriorityQueue<T>::~PriorityQueue() {
  numElements = 0;
  maxCapacity = 0;
  data.clear();
}

template <class T>
// Complejidad computacional: O(1)
int PriorityQueue<T>::parent(int i) {
  return (i - 1) / 2;
}

template <class T>
// Complejidad computacional: O(1)
int PriorityQueue<T>::left(int i) {
  return (2 * i + 1);
}

template <class T>
// Complejidad computacional: O(1)
int PriorityQueue<T>::right(int i) {
  return (2 * i + 2);
}

template <class T>
// Complejidad computacional: O(log 2 n)
void PriorityQueue<T>::push(T key) {
  if (numElements == maxCapacity) {
    throw std::out_of_range("[OVERFLOW] No se puede insertar la llave");
  }
  // Insertar la nueva llave al final del vector
  int i = numElements;
  data[i] = key;
  numElements++;
  // Reparar las propiedades del PriorityQueue
  while (i != 0 && data[parent(i)] < data[i]) {
    std::swap(data[i], data[parent(i)]);
    i = parent(i);
  }
}

template <class T>
// Complejidad computacional: O(1)
T PriorityQueue<T>::top() {
  if (numElements == 0) {
    throw std::out_of_range("No hay elementos");
  }
  return this->data[0];
}

template <class T> 
// Complejidad computacional: O(n log n)
void PriorityQueue<T>::pop() {
  if(numElements > 0){
    std::swap(data[0], data[numElements - 1]);
    data.erase(data.begin() + numElements - 1);
    numElements--;
    heapify(0);
  }
}

template <class T>
// Complejidad computacional: O(log n)
void PriorityQueue<T>::heapify(int index) {
  // Referencia: GeeksforGeeks et al. (2022). HeapSort. GeeksforGeeks.
  // https://www.geeksforgeeks.org/heap-sort/
  int smallest = index, childL = left(index), childR = right(index);
  if (childL < numElements && data[childL] > data[smallest]) {
    smallest = childL;
  }
  if (childR < numElements && data[childR] > data[smallest]) {
    smallest = childR;
  }
  if (smallest != index) {
    std::swap(data[smallest], data[index]);
    heapify(smallest);
  }
}

#endif // _PriorityQueue_H_