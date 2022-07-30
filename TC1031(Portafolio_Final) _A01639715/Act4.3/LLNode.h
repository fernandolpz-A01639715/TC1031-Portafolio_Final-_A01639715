#ifndef _NODE_H_
#define _NODE_H_

template <class T>
class LLNode { 
  public: 
    T data; 
    LLNode<T> *next;
    LLNode();
    LLNode(T val);        
}; 

// Complejidad computacional: O(1)
template<class T>
LLNode<T>::LLNode() : data{}, next{nullptr} {}

// Complejidad computacional: O(1)
template<class T>
LLNode<T>::LLNode(T val){
  data = val;
  next = nullptr;
}

#endif // _NODE_H_