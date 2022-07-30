#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

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
  void heapify(int index, int heapSize);

public:
  PriorityQueue(int capacity);
  ~PriorityQueue();
  bool empty();
  int getCapacity();
  int size();
  void print();
  void push(T key);
  T top();
  void pop();
  void heapSort();
  bool successfulHeapSort();
  void exportar(std::string fileName);
  // Bitácora (Registros)
  void leerBitacora(std::string fileName);
  std::vector<int> contReps();
  std::vector<std::string> nonRepeatedData();
  void printtop5();
};

template <class T> PriorityQueue<T>::PriorityQueue(int capacity) {
  numElements = 0;
  maxCapacity = capacity;
  data.resize(maxCapacity);
  std::cout << "-*- Fila priorizada vacía creada: " << this << " -*-"
            << std::endl;
}

template <class T> PriorityQueue<T>::~PriorityQueue() {
  numElements = 0;
  maxCapacity = 0;
  data.clear();
  std::cout << "-*- Memoria liberada de la fila priorizada: " << this << " -*-"
            << std::endl;
}

template <class T>
// Complejidad computacional: O(1)
bool PriorityQueue<T>::empty() {
  return (numElements == 0);
}

template <class T>
// Complejidad computacional: O(1)
int PriorityQueue<T>::getCapacity() {
  return maxCapacity;
}

template <class T>
// Complejidad computacional: O(1)
int PriorityQueue<T>::size() {
  return numElements;
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
// Complejidad computacional: O(n)
void PriorityQueue<T>::print() {
  for (int i = 0; i < numElements; i++) {
    std::cout << data[i] << std::endl;
  }
}

template <class T>
// Complejidad computacional: O(log 2 n)
void PriorityQueue<T>::push(T key) {
  if (numElements == maxCapacity) {
    throw std::out_of_range("[OVERFLOW: No se puede insertar la llave]");
  }
  // Insertar la nueva llave al final del vector
  int i = numElements;
  data[i] = key;
  numElements++;
  // Reparar las propiedades del PriorityQueue
  while (i != 0 && data[parent(i)] > data[i]) {
    std::swap(data[i], data[parent(i)]);
    i = parent(i);
  }
}

template <class T>
// Complejidad computacional: O(1)
T PriorityQueue<T>::top() {
  if (numElements == 0) {
    throw std::out_of_range("[ERROR: No hay elementos]");
  }
  return this->data[0];
}

template <class T>
// Complejidad computacional: O(log n)
void PriorityQueue<T>::heapify(int index, int heapSize) {
  // Referencia: GeeksforGeeks et al. (2022). HeapSort. GeeksforGeeks.
  // https://www.geeksforgeeks.org/heap-sort/
  int smallest = index, childL = left(index), childR = right(index);
  if (childL < heapSize && data[childL] < data[smallest]) {
    smallest = childL;
  }
  if (childR < heapSize && data[childR] < data[smallest]) {
    smallest = childR;
  }
  if (smallest != index) {
    std::swap(data[smallest], data[index]);
    heapify(smallest, heapSize);
  }
}

template <class T>
// Complejidad computacional: O(n log n)
void PriorityQueue<T>::pop() {
  if (numElements > 0) {
    std::swap(data[0], data[numElements - 1]);
    data.erase(data.begin() + numElements - 1);
    numElements--;
    heapify(0,numElements);
  }
}

template <class T>
// Complejidad temporal: O(n log n)
void PriorityQueue<T>::heapSort() {
  int heapSize = numElements;
  while (heapSize > 1) {
    std::swap(data[0], data[heapSize - 1]);
    heapSize--;
    heapify(0, heapSize);
  }
}

template <class T>
// Complejidad temporal: O(n)
bool PriorityQueue<T>::successfulHeapSort() {
  while (int i = 0 > numElements) {
    if (data[i] < data[i + 1]) {
      return false;
    }
  }
  return true;
}

template <class T>
// Complejidad temporal: O(n)
void PriorityQueue<T>::leerBitacora(std::string fileName) {
  std::string month, day, hour, minute, second, ipAdd, port, message, octetoUno,
      octetoDos, octetoTres, octetoCuatro;
  unsigned int ipDec;
  std::ifstream inputFile(fileName);
  if (!inputFile.good()) {
    inputFile.close();
    throw std::invalid_argument("File not found");
  } else {
    while (!inputFile.eof()) {
      ipDec = 0;
      // to-do validar que la longitud de month sea mayor a cero
      std::getline(inputFile, month, ' ');
      std::getline(inputFile, day, ' ');
      std::getline(inputFile, hour, ':');
      std::getline(inputFile, minute, ':');
      std::getline(inputFile, second, ' ');
      std::getline(inputFile, octetoUno, '.');
      std::getline(inputFile, octetoDos, '.');
      std::getline(inputFile, octetoTres, '.');
      std::getline(inputFile, octetoCuatro, ':');
      std::getline(inputFile, port, ' ');
      std::getline(inputFile, message);
      // crear ipAdd (str) & ipDec (int)
      ipAdd =
          octetoUno + "." + octetoDos + "." + octetoTres + "." + octetoCuatro;
      ipDec += (std::stoul(octetoUno, nullptr, 0) * 16777216);
      ipDec += (std::stoul(octetoDos, nullptr, 0) * 65536);
      ipDec += (std::stoul(octetoTres, nullptr, 0) * 256);
      ipDec += std::stoul(octetoCuatro, nullptr, 0);
      // Referencia: https://cplusplus.com/reference/string/stoul/
      // crear un objeto de la clase
      T tmpReg(month, day, hour, minute, second, ipAdd, port, message, ipDec);
      // agragar el objeto al vector
      if (month.length() > 2) {
        push(tmpReg);
      }
    }
    inputFile.close();
  }
}

template <class T>
// Complejidad temporal: O(n)
void PriorityQueue<T>::exportar(std::string fileName) {
  std::ofstream outputFile(fileName);
  for (int i = 0; i < numElements; i++) {
    outputFile << data[i] << std::endl;
  }
  outputFile.close();
}

template <class T>
// Complejidad temporal O(n)
std::vector<int> PriorityQueue<T>::contReps() {
  if (numElements > 0) {
    std::vector<int> reps;
    int cont = 1;
    for (int i = 0; i < numElements - 1; i++) {
      if (data[i] == data[i + 1]) {
        cont++;
      } else {
        reps.push_back(cont);
        cont = 1;
      }
    }
    return reps;
  } else {
    throw std::out_of_range("[ERROR: No hay elementos]");
  }
}

template <class T>
// Complejidad temporal O(n)
std::vector<std::string> PriorityQueue<T>::nonRepeatedData() {
  if (numElements > 0) {
    std::vector<std::string> info;
    for (int i = 0; i < numElements - 1; i++) {
      if (data[i] != data[i + 1]) {
        info.push_back(data[i].getIpAddress());
      }
    }
    // para revisar el último elemento
    if (data[size() - 1] != data[size() - 2]) {
      info.push_back(data[size() - 1].getIpAddress());
    }
    return info;
  } else {
    throw std::out_of_range("[ERROR: No hay elementos]");
  }
}

template <class T>
// Complejidad computacional: O(n)
// Hay que hacer un top pop. Complejidad del pop log
void PriorityQueue<T>::printtop5() {
  std::ofstream outputFile("ips_con_mayor_acceso.txt");
  for (int i = 0; i < 5; i++) {
    std::cout << data[i] << " accesos" << std::endl;
    outputFile << data[i] << " accesos" << std::endl;
  }
  outputFile.close();
}

#endif // _PriorityQueue_H_