#include "Bitacora.h"



Bitacora::Bitacora() {
  //listaRegistros.resize(0);
}

Bitacora::~Bitacora() {
  //listaRegistros.clear();
}

DoubleLinkedList<Registro> Bitacora::getListaRegistros(){
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
        listaRegistros.addLast(tmpReg);
        //listaRegistros.push_back(tmpReg);
      }
    }
    inputFile.close();
  }
}

// Complejidad temporal: O(n)
void Bitacora::print() {
  for (int i = 0; i < (int)listaRegistros.getNumElements(); i++) {
    std::cout << listaRegistros.getData(i).getAll() << std::endl; 
  }
}


// Complejidad espacial: O(n)
// Complejidad temporal :O(n)
/*
void Bitacora::merge(int low, int m, int high) {
  int i, j, k;
  int n1 = m - low +1;
  int n2 = high - m;
  std::vector<Registro> L(n1);
  std::vector<Registro> R(n2);
  for (i = 0; i < n1; i++) L[i] = this -> listaRegistros[low+i];
  for (j = 0; j < n2; j++) R[j] = this -> listaRegistros[m + 1 +j];
  i = j = 0; 
  k = low;
  while (i < n1 && j < n2) {
    if (L[i] < R[j]) {
      this -> listaRegistros[k] = L[i];
      i++;
    } 
    else {
      this -> listaRegistros[k] = R[j];
      j++;
    }
    k++;
  }
  // Se encargan de los elementos sobrantes
  while (i < n1) {
    this -> listaRegistros[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    this -> listaRegistros[k] = R[j];
    j++;
    k++;
  }
  
}*/
/*
void Bitacora::ordenaBitacora(int low, int high) {
  //Usando Merge Sort
  if (low < high){
    int m = (low + high) / 2;
    // Ordena recursivamente las dos mitades
    ordenaBitacora(low, m);
    ordenaBitacora(m+1, high);
    // fusiona las dos mitades
    merge(low, m, high);
  }
}
*/


  void Bitacora::mergeSort(){
  listaRegistros.sort();
}




// Complejidad temporal: O(n)
void Bitacora::exportaBitacora(std::string fileName) {
  std::ofstream outputFile(fileName);
  for (int i = 0; i < (int)listaRegistros.getNumElements(); i++) {
  outputFile << listaRegistros.getData(i).getAll() << std::endl;
  }
  outputFile.close();
}

//Complejidad temporal: O(log n)
//Complejidad espacial: O(1)
  /*
int Bitacora::buscar(Registro key){

  int low = 0;
  int high = int(this -> listaRegistros.getNumElements())-1;
  int mid = 0;
  while (low <= high){
    mid = low + (high-low)/2;
    if (key == this -> listaRegistros[mid]) return mid;
    else if (key < this -> listaRegistros[mid]) high = mid-1;
    else low = mid+1;
  } 
  return -1;
 */
/*
// Complejidad temporal: O(n)
void Bitacora::printRango(int inicio,int fin) {
    if (fin > (int)listaRegistros.getNumElements()){
        fin = (int)listaRegistros.getNumElements();
    }
    for (int i = inicio; i <= fin; i++) {
        std::cout << listaRegistros.getData(i).getAll() << std::endl;
    }
}
*/

//Complejidad Computacional: O(n)
void Bitacora::printRango(Registro inicio, Registro fin) {
  DLLNode<Registro>* pointerInicio;
  DLLNode<Registro>* pointerFin;

  /*
  indiceInicio= listaRegistros.findData(inicio);
  indiceFin= listaRegistros.findData(fin);
  */
  
  pointerInicio = listaRegistros.searchFor(inicio);
  pointerFin = listaRegistros.searchFor(fin);

  if (pointerInicio == nullptr || pointerFin == nullptr){
    std::cout << "Fecha inicial o Fecha Final inexistentes. " << std::endl;
  }  
  /*
  if(indiceInicio != -1 && indiceFin != -1){
    std::cout << "Registros encontrados: "<<indiceFin-indiceInicio+1 << std::endl;
  }
  */
  //listaRegistros.printSublist(indiceInicio, indiceFin);
  listaRegistros.printRange(pointerInicio,pointerFin);
}