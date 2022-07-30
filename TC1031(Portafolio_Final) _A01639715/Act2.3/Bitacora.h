#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <fstream>
#include <sstream>
#include <iostream>

#include "Registro.h"
#include "DoubleLinkedList.h"

class Bitacora {
  private:
    // Lista doblemente ligada de objetos Registro (cada celda es un renglon de bitacora.txt)
    DoubleLinkedList<Registro> listaRegistros;
    void merge(int low, int m, int high);

  public:
    Bitacora();
    ~Bitacora();
    DoubleLinkedList<Registro> getListaRegistros();
    void lecturaDatos(std::string fileName);
    void print();
    void printRango(Registro inicio, Registro fin);
    // ordenamiento y búsqueda
    void ordenaBitacora(int low, int high);
    void mergeSort();
    
    int buscar(Registro);
    // exportar a .txt
    void exportaBitacora(std::string fileName);

    
};

#endif // _BITACORA_H_