#include "Bitacora.h"

//Constructor
// Complejidad computacional: O(1)
Bitacora::Bitacora() { }

//Agregando metodos de graph para cargar los archivos
// Complejidad computacional: O((E + V)(ElogV)(E + V))
Bitacora::Bitacora(std::string fileName) {
  graph.readGraph(fileName); // Punto 1
  bootMasterIndex = graph.outDegrees("grados_ips.txt"); // Puntos 2, 3
  graph.shortestPath(bootMasterIndex, "distancia_bootmaster.txt"); // Puntos 5
}

//Destructor
// Complejidad computacional: O(1)
Bitacora::~Bitacora() { }