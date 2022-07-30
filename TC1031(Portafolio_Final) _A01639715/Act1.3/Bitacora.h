#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <sstream>

#include "Registro.h"

class Bitacora {
  private:
    // vector de objetos Registro (cada celda es un renglon de bitacora.txt)
    std::vector<Registro> listaRegistros;

  public:
    Bitacora();
    ~Bitacora();
    std::vector<Registro> getListaRegistros();
    void lecturaDatos(std::string fileName);
    void print();
    void printRango(int inicio, int fin);
    // ordenamiento y búsqueda
    void ordenaBitacora(int low, int high, int algorithm);
    int buscar(Registro);
    // exportar a .txt
    void exportaBitacora(std::string fileName);
};

#endif // _BITACORA_H_