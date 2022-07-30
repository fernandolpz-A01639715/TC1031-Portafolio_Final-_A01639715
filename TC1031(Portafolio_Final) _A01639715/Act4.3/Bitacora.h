#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Graph.h"

class Bitacora {

  private:
    Graph<std::string> graph; //Declarando un objeto grafo
    int bootMasterIndex;
  public:
    Bitacora(); //Constructor
    Bitacora(std::string fileName); //lectura de archivo
    ~Bitacora(); //Destructor
};

#endif  // _BITACORA_H_