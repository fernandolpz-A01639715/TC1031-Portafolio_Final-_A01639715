  #ifndef _DoubleLinkedList_H_
#define _DoubleLinkedList_H_

#include "DLLNode.h"
#include <iostream>
#include <fstream>

template <class T>
class DoubleLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;

    DLLNode<T>*merge(DLLNode<T> *first, DLLNode<T> *second);
    DLLNode<T>*split(DLLNode<T> *head);
    DLLNode<T>*mergeSort(DLLNode<T> *head);
    void clearMemory();

  public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    // retorna el numero de elementos de la lista
    int getNumElements();
    // imprime lista completa
    void printList();
    // agrega un elemento a la lista al inicio
    void addFirst(T value);
    //  agrega un elemento a la lista al fin
    void addLast(T value);
    // borra elemento de la lista
    bool deleteData(T value);
    // borra indice de la lista
    bool deleteAt(int posicion);
    // obtiene el elemento de un indice de la lista
    T getData(int position);
    // actualiza un elemento de la lista 
    void updateData(T value, T newValue);
    // actualiza un indice de la lista
    void updateAt(int posicion, T newValue);
    // obtiene el indice de un elemento 
    int findData(T value);
    void operator=(const DoubleLinkedList<T> &other); // se llama asi:  lista1 = lista2
    void ordenaQuick(DLLNode<T>* low, DLLNode<T>* high);
    // ordena lista 
    void sort();
    // invierte lista
    void invert();

    // crea una lista inversa a partir de la original, con el indice de inicio y fin 
    DoubleLinkedList<T> getReversedSublist(int inicio, int fin);
    // crea una lista a partir de la original, con el indice de inicio y fin 
    DoubleLinkedList<T> getSublist(int inicio, int fin);
    // imprime lista desde un indice de inicio y fin
    void printSublist(int inicio, int fin);

    DLLNode<T>* searchFor(T value);
    void printRange(DLLNode<T>* inicio, DLLNode<T>* fin);
};

template<class T>
DoubleLinkedList<T>::DoubleLinkedList() {
  std::cout << " - * - Lista vacía creada - * - \n  Apuntador Head: " << &head << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  std::cout << " - * - Liberando memoria de lista - * - \n  Apuntador Head: " << &head << std::endl;
  DLLNode<T> *prev, *q;
  prev = head;
  while (prev != nullptr) {
    q = prev->next;
    delete prev;
    prev = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
//Complejidad O(n)
void DoubleLinkedList<T>::clearMemory() {
  DLLNode<T> *prev, *q;
  prev = head;
  while (prev != nullptr) {
    q = prev->next;
    delete prev;
    prev = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
//Complejidad computacional: O(1)
int DoubleLinkedList<T>::getNumElements() {
  return numElements;
}

template<class T>
//Complejidad computacional: O(n)
void DoubleLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
}

template<class T>
//Complejidad computacional: O(1)
void DoubleLinkedList<T>::addFirst(T value) {
  // creando un nuevo nodo de la lista
  DLLNode<T> *newDLLNode = new DLLNode<T>(value);
  // Si la lista esta vacia if(head == nullptr)
  if (numElements == 0) {
    head = newDLLNode;
    tail = newDLLNode; 
  } 
  else {
    newDLLNode->next = head;
    head->prev = newDLLNode;
    head = newDLLNode;
  }
  numElements++;
}

template<class T>
//Complejidad computacional: O(1)
void DoubleLinkedList<T>::addLast(T value) {
  // Si la lista esta vacia if(head == nullptr)
  if (numElements == 0) {
    addFirst(value);
  }
  else {
    // creando un nuevo nodo de la lista
    DLLNode<T> *newDLLNode = new DLLNode<T>(value);
    tail->next = newDLLNode;
    newDLLNode->prev = tail;
    tail = newDLLNode;
    numElements++;
  }
}

template<class T>
//Complejidad computacional: O(n)
bool DoubleLinkedList<T>::deleteData(T value) {
  bool estado = false;
  // Si la lista esta vacia
  if (numElements == 0) {
    return estado;
  }
  else {
    DLLNode<T> *p = head;
    DLLNode<T> *previo = nullptr;
    // buscar value en la lista
    while (p != nullptr && p->data != value) {
      previo = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return estado;
    // Si debe borrarse el primer elemento de la lista
    if (p == head) {
      head = p->next;
      if (head != nullptr)
        head->prev = nullptr;
    } else if (p->next == nullptr) { // borrar ultimo en la lista
      previo->next = nullptr;
      tail = previo;     
    } else { // cualquier otro elemento de la lista
      previo->next = p->next;
      p->next->prev = p->prev;
    }
    delete p;
    numElements--;
    estado = true;
    return estado;
  }
}

template<class T>
//Complejidad computacional: O(n)
bool DoubleLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else if (position == 0) { // Si debe borrarse el primer elemento
    DLLNode<T> *p = head;
    // Si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    }
    else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    numElements--;
    return true; 
  }
  else { // Si position > 0 
    DLLNode<T> *p = head, *q = nullptr;
    int index = 0;
    // Se busca el indice del elemento a borrar
    while (index != position) {
      q = p;
      p = p->next;
      index++;
    }
    // Si debe borrarse el último elemento
    if (p->next == nullptr) {
      q->next = nullptr;
      tail = q;
    }
    else { // Cualquier otro elemento en medio de la lista 
      q->next = p->next;
      p->next->prev = q;
    }
    delete p;
    numElements--;
    return true;
  }
}

template<class T>
//Complejidad computacional: O(n)
T DoubleLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else {
    if (position == 0)
      return head->data;
    DLLNode<T> *p = head;
    int index = 0;
    while (p != nullptr) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return {};
  }
}

template<class T>
//Complejidad computacional: O(n)
void DoubleLinkedList<T>::updateData(T value, T newValue) {
  if (numElements > 0) {
    DLLNode<T> *p = head;
    DLLNode<T> *prev = nullptr;
    // buscar value en la lista
    while (p != nullptr && p->data != value) {
      prev = p;
      p = p->next;
    }
    // si existe value en la lista
    if (p != nullptr)
      p->data = newValue;
    else
      throw std::out_of_range("No se encontró el valor en la lista");
  }  
}

template<class T>
//Complejidad computacional: O(n)
void DoubleLinkedList<T>::updateAt(int position, T newValue){
  if (numElements > 0) {
    if (position < 0 || position >= numElements){
      throw std::out_of_range("Indice fuera de rango");
    }
    else{
      DLLNode<T> *p = head, *prev = nullptr;
      int index = 0;
      // Se busca el indice ingresado
      while (index != position) {
        prev = p;
        p = prev->next;
        index++;
      }
      p -> data= newValue;
    }
  }
  else{
    throw std::out_of_range("Lista vacía");
  }
}

template<class T>
//Complejidad computacional: O(n)
int DoubleLinkedList<T>::findData(T value) {
  int indice = 0;
// Si la lista esta vacia
  if (numElements == 0) {
    return -1;
  }
  else {
    DLLNode<T> *p = head;
    // buscar value en la lista
    while (p != nullptr && p->data != value) {
      p = p->next;
      indice += 1;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return -1;
    return indice;
  }
}

template<class T>
//Complejidad Computacional: O(n)
void DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other) {
  clearMemory();
  DLLNode<T>* ptr = other.head;
  while (ptr != nullptr) {
    this->addLast(ptr->data);
    ptr = ptr->next;
  }
}


// -----------------  INICIO QUICK SORT ---------------------

template<class T>
DLLNode<T>* partition(DLLNode<T>* low, DLLNode<T>* high){
  // Referencia: GeeksforGeeks et al. (2022). QuickSort on Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/quicksort-for-linked-list/
  // set pivot as h element 
  int pivot = high->data; 
  // similar to i = l-1 for array implementation 
  DLLNode<T> *i = low->prev; 
  // Similar to "for (int j = l; j <= h- 1; j++)" 
  for (DLLNode<T> *j = low; j != high; j = j->next){ 
    if (j->data <= pivot){ 
      // Similar to i++ for array 
      i = (i == NULL)? low : i->next;
      std::swap(i->data, j->data); 
    } 
  } 
  i = (i == NULL)? low : i->next; // Similar to i++ 
  std::swap(i->data, high->data); 
  return i; 
}

/*  Método "Quick Sort"
Complejidad temporal: O(n^2) */
template<class T>
void DoubleLinkedList<T>::ordenaQuick(DLLNode<T>* low, DLLNode<T>* high){
  // Referencia: GeeksforGeeks et al. (2022). QuickSort on Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/quicksort-for-linked-list/
  if (high != NULL && low != high && low != high->next){
    DLLNode<T>* p = partition(low, high);
    ordenaQuick(low, p -> prev);
    ordenaQuick(p ->next, high);
  }
}

// -----------------  FIN QUICK SORT ---------------------

// -----------------  INICIO MERGE SORT ---------------------



template<class T>
// Function to merge two linked lists 
//Complejidad temporal: O(n)
DLLNode<T>*DoubleLinkedList<T>::merge(DLLNode<T> *first, DLLNode<T> *second) { 
    // If first linked list is empty 
    if (!first) 
        return second; 
  
    // If second linked list is empty 
    if (!second) 
        return first; 
  
    // Pick the smaller value 
    if (first->data < second->data) { 
        first->next = merge(first->next,second); 
        first->next->prev = first; 
        first->prev = NULL; 
        return first; 
    } 
    else{ 
        second->next = merge(first,second->next); 
        second->next->prev = second; 
        second->prev = NULL; 
        return second; 
    } 
} 

template<class T>
//Complejidad temporal: O(n)
  // Split a doubly linked list (DLL) into 2 DLLs of half sizes 
DLLNode<T>*DoubleLinkedList<T>::split(DLLNode<T> *head) { 
    DLLNode<T> *fast = head,*slow = head; 
    while (fast->next && fast->next->next) { 
        fast = fast->next->next; 
        slow = slow->next; 
    } 
    DLLNode<T> *temp = slow->next; 
    slow->next = NULL; 
    return temp; 
} 

template<class T>
// Function to do merge sort 
// Complejidad temporal: Θ(nLogn)
DLLNode<T>*DoubleLinkedList<T>::mergeSort(DLLNode<T> *head) { 
    if (!head || !head->next) 
        return head; 
    DLLNode<T> *second = split(head); 
  
    // Recur for left and right halves 
    head = mergeSort(head); 
    second = mergeSort(second); 
  
    // Merge the two sorted halves 
    return merge(head,second); 
} 

// -----------------  FIN MERGE SORT ---------------------



template<class T>
//Complejidad O(1)
void DoubleLinkedList<T>::sort(){
  /*
  ordenaQuick(head, tail);
// Referencia: GeeksforGeeks et al. (2022). QuickSort on Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/quicksort-for-linked-list/
  */
  head = mergeSort(head);
  // Referencia: GeeksforGeeks et al. (2022) Merge Sort for Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
}




template<class T>
//Complejidad computacional: O(n)
void DoubleLinkedList<T>::invert() {
  // invertir apuntadores de elementos
  DLLNode<T> *ptr;
  ptr = head;
  while (ptr != nullptr) {
    std::swap(ptr->prev, ptr->next);
    ptr = ptr->prev;
  }
  // cambiar head & tail
  std::swap(head, tail);
}

template<class T>
//Complejidad Computacional: O(n)
DoubleLinkedList<T> DoubleLinkedList<T>::getReversedSublist(int inicio, int fin) {
  DoubleLinkedList<T>* out = new  DoubleLinkedList<T>();;
  if (inicio < 0 || inicio >= numElements){
    throw std::out_of_range("Inicio fuera de rango");
  } else if (fin < inicio){
    throw std::out_of_range("Fin menor a inicio");
  } else if (fin > numElements) {
    throw std::out_of_range("Fin mayor a número de elementos");
  } else {
    DLLNode<T>* p = head;
    int index = 0;
    while (p != nullptr) {
      if (index >= inicio) {
        out->addFirst(p->data);
      }
      if (index == fin) {
        break;
      }
    index++;
    p = p->next;
    }
  }
  return *out;
}

template<class T>
//Complejidad temporal: O(n)
DoubleLinkedList<T> DoubleLinkedList<T>::getSublist(int inicio, int fin) {
    DoubleLinkedList<T>* out = new  DoubleLinkedList<T>();;
  if (inicio < 0 || inicio >= numElements){
    throw std::out_of_range("Inicio fuera de rango");
  } else if (fin < inicio){
    throw std::out_of_range("Fin menor a inicio");
  } else if (fin > numElements) {
    throw std::out_of_range("Fin mayor a número de elementos");
  } else {
    DLLNode<T>* p = head;
    int index = 0;
    while (p != nullptr) {
      if (index >= inicio) {
        out->addLast(p->data);
      }
      if (index == fin) {
        break;
      }
    index++;
    p = p->next;
    }
  }
  return *out;
}

template<class T>
//Complejidad temporal: O(n)
void DoubleLinkedList<T>::printSublist(int inicio, int fin) {
    std::ofstream outputFile("resultado_busqueda.txt");  
    if (inicio < 0 || inicio >= numElements){
      throw std::out_of_range("Inicio fuera de rango");
    } 
    else if (fin < inicio){
      throw std::out_of_range("Fin menor a inicio");
    } 
    else if (fin > numElements) {
      throw std::out_of_range("Fin mayor a número de elementos");
    }  
    else {
      DLLNode<T>* p = head;
      int index = 0;
      while (p != nullptr) {
        if (index >= inicio) {
           std::cout << p->data << " " << std::endl;
          outputFile << p->data << std::endl;
        }
        if (index == fin) {
          break;
        }
        index++;
        p = p->next;
      }
    }
  outputFile.close();
}


template<class T>
// Complejidad temporal O(n)
void DoubleLinkedList<T>::printRange(DLLNode<T>* inicio, DLLNode<T>* fin){
  std::ofstream outputFile("resultado_busqueda.txt");
  while(inicio != fin->next){
    std::cout << inicio -> data << " " << std::endl;
    outputFile << inicio -> data << std::endl;
    inicio = inicio->next;
  }
  outputFile.close();
}

// -----------------  INICIO BINARY SEARCH ---------------------
//KunalDhyani(2022) Binary Search on Linked List. Geeks For Geeks https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/

template<class T>
//Complejidad temporal: O(n log n) 
DLLNode<T>* middle(DLLNode<T>* start, DLLNode<T>* last){
    if (start == nullptr)
        return nullptr;
  
    DLLNode<T>* slow = start;
    DLLNode<T>* fast = start -> next;
  
    while (fast != last){
        fast = fast -> next;
        if (fast != last){
          slow = slow -> next;
          fast = fast -> next;
        }
    }
    return slow;
}
  
// Function for implementing the Binary
// Search on linked list
// Complejidad temporal O(n log n)
template<class T>
DLLNode<T>* binarySearch(DLLNode<T> *head, T value){
    DLLNode<T>* start = head;
    DLLNode<T>* last = nullptr;
    do{
        // Find middle
        DLLNode<T>* mid = middle(start, last);
  
        // If middle is empty
        if (mid == nullptr)
            return nullptr;
  
        // If value is present at middle
        if (mid -> data == value)
            return mid;
  
        // If value is more than mid
        else if (mid -> data < value)
            start = mid -> next;
  
        // If the value is less than mid.
        else
            last = mid;
  
    } while (last == nullptr ||
             last != start);
  
    // value not present
    return nullptr;
}

template<class T>
//Complejidad computacional: O(1)
DLLNode<T>* DoubleLinkedList<T>::searchFor(T value) {
  return binarySearch(head, value);
}
#endif // _DoubleLinkedList_H_