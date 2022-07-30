#include <iostream>
#include <vector>
#include "Bitacora.h"

// Complejidad temporal: O(n log n)
// Complejidad espacial: O(n)
void merge(std::vector<Registro> &vector, int low, int m, int high) {
  int i, j, k;
  int n1 = m - low +1;
  int n2 = high - m;
  std::vector<Registro> L(n1);
  std::vector<Registro> R(n2);
  for (i = 0; i < n1; i++) L[i] = vector[low+i];
  for (j = 0; j < n2; j++) R[j] = vector[m + 1 +j];
  i = j = 0; 
  k = low;
  while (i < n1 && j < n2) {
    if (L[i] < R[j]) {
      vector[k] = L[i];
      i++;
    } 
    else {
      vector[k] = R[j];
      j++;
    }
    k++;
  }
  // Se encargan de los elementos sobrantes
  while (i < n1) {
    vector[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    vector[k] = R[j];
    j++;
    k++;
  }
}

Bitacora::Bitacora() {
  listaRegistros.resize(0);
}

Bitacora::~Bitacora() {
  listaRegistros.clear();
}

std::vector<Registro> Bitacora::getListaRegistros(){
  return this -> listaRegistros;
}

// Complejidad temporal: O(n)
void Bitacora::lecturaDatos(std::string fileName) {
  std::string month, day, hour, minute, second, ipAdd, port, message;
  std::ifstream inputFile(fileName);
  if (!inputFile.good()) {
    inputFile.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!inputFile.eof()) {
      // to-do validar que la longitud de month sea mayor a cero
      std::getline(inputFile, month, ' ');
      std::getline(inputFile, day, ' ');
      std::getline(inputFile, hour, ':');
      std::getline(inputFile, minute, ':');
      std::getline(inputFile, second, ' ');
      std::getline(inputFile, ipAdd, ':');
      std::getline(inputFile, port, ' ');
      std::getline(inputFile, message);
      // crear un objeto de la clase Registro
      Registro tmpReg(month, day, hour, minute, second, ipAdd, port, message);
      // agragar el objeto al vector
      if(month.length()>2) {
      listaRegistros.push_back(tmpReg);
        }
    }
    inputFile.close();
  }
}

// Complejidad temporal: O(n)
void Bitacora::print() {
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    std::cout << listaRegistros[i].getAll() << std::endl; 
  }
}

// Complejidad temporal usando merge: O(n log n)
// Complejidad temporal usando Bubble: O(n^2)
// Complejidad espacial: O(n)
void Bitacora::ordenaBitacora(int low, int high, int algorithm) {
  if(algorithm != 1){
      // Bubble sort 
    for(int i = 0; i < int(this -> listaRegistros.size()) - 1; i++) {
      for(int j = 0; j < int(this -> listaRegistros.size()) - i - 1; j++) {
        if(listaRegistros[j]  > listaRegistros[j + 1]) {
          std::swap(listaRegistros[j], listaRegistros[j + 1]);
        }
      }
    }
  }
  else{
    //Usando Merge Sort
    if (low < high){
      int m = (low + high) / 2;
      // Ordena recursivamente las dos mitades
      ordenaBitacora(low, m, 1);
      ordenaBitacora(m+1, high, 1);
      // fusiona las dos mitades
      merge(this -> listaRegistros, low, m, high);
    }
  }
}

// Complejidad temporal: O(n)
void Bitacora::exportaBitacora(std::string fileName) {
  std::ofstream outputFile(fileName);
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
  outputFile << listaRegistros[i].getAll() << std::endl;
  }
  outputFile.close();
}

//Complejidad temporal: O(log n)
//Complejidad espacial: O(1)
int Bitacora::buscar(Registro key){
  int low = 0;
  int high = int(this -> listaRegistros.size())-1;
  int mid = 0;
  while (low <= high){
    mid = low + (high-low)/2;
    if (key == this -> listaRegistros[mid]) return mid;
    else if (key < this -> listaRegistros[mid]) high = mid-1;
    else low = mid+1;
  } 
  return -1;
}

// Complejidad temporal: O(n)
void Bitacora::printRango(int inicio,int fin) {
    if (fin > (int)listaRegistros.size()){
        fin = (int)listaRegistros.size();
    }
    for (int i = inicio; i <= fin; i++) {
        std::cout << listaRegistros[i].getAll() << std::endl;
    }
}
