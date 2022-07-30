#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Graph.h"


class Bitacora {

private:
  Graph<std::string> graph; // Declarando un objeto grafo


public:
  Bitacora();                     // Constructor
  Bitacora(std::string fileName); // lectura de archivo
  ~Bitacora();                    // Destructor

};

#endif // _BITACORA_H_
