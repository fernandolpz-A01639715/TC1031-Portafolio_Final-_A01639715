#include <iostream>
#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {

}

//Agregando metodos de graph para cargar los archivos
Bitacora::Bitacora(std::string fileName) {
  graph.readGraph(fileName);
  graph.print();
  graph.fillHashTable();
  ipAddress ip =graph.getIPSummary();
  graph.printIpPos(ip);
  //graph.outDegrees("grados_ips.txt","mayores_grados_ips.txt");
  //graph.bootMasterDist("distancia_bootmaster.txt");
}

//Destructor
Bitacora::~Bitacora() {

}