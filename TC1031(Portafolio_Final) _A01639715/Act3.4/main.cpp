/* 
TC1031.570
Equipo 4
- Fernando López Gómez (A01639715)
- Fausto Alejandro Palma Cervantes (A01639224)
- Lautaro Gabriel Coteja (A01571214)
Compilación para debug:  
  g++ -std=c++17 -g -o main *.cpp
Ejecución con valgrind:
  nix-env -iA nixpkgs.valgrind
  valgrind --leak-check=full ./main
Compilación con warnings:
  g++ -std=c++17 -Wall *.cpp
Compilación sin warnings: 
  g++ -std=c++17 -O3 -o main *.cpp
Ejecución:
  ./main
*/

#include <iostream>
#include <sstream>
#include <chrono>

#include "PriorityQueue.h"
#include "Registro.h"
#include "DireccionIP.h"

using std::endl;
using std::cout;
using std::cin;
using std::string;

int main() {
// - - - REGISTROS - - -
  std::cout << "\nOrdenar los registros de la bitácora por IP:" << std::endl;
  // Crear bitácora
  PriorityQueue<Registro> bitacoraHeap(20000);

  // Leer registros
  cout << "Por favor espere . . . ";
  bitacoraHeap.leerBitacora("bitacoraHeap.txt");
  cout << "¡Bitacora leída!" << endl;
  
  // Ordenar bitácora
  bitacoraHeap.heapSort();
  cout << std::boolalpha << "Successful Heap Sort: " << bitacoraHeap.successfulHeapSort() << std::endl;

  // Exportar bitácora
  bitacoraHeap.exportar("bitacora_ordenada.txt");

// - - - DIRECCIONES IP - - -
  std::cout << "\nEncontrar las cinco IPs con más accesos:" << std::endl;
  PriorityQueue<DireccionIP> repeticionesHeap(20000);
  //Extraemos información limpia de la bitácora
  std::vector<int> ipRepeticiones = bitacoraHeap.contReps();
  std::vector<std::string> ipLimpia = bitacoraHeap.nonRepeatedData();
  for(int i = 0; i<(int)ipRepeticiones.size(); i++){
    //Creamos una dirección Ip temporal para almacenarla en repeticionesHeap
    DireccionIP tempDir(ipLimpia[i], ipRepeticiones[i]);
    repeticionesHeap.push(tempDir);
  }
  repeticionesHeap.heapSort();
  cout << std::boolalpha << "Successful Heap Sort: " << repeticionesHeap.successfulHeapSort() << std::endl;
  std::cout << std::endl;
  /*
  std::cout << "IPs con mayor acceso: " << std::endl;
  repeticionesHeap.printtop5();
  std::cout << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  */
  std::cout << "IPs con mayor acceso: " << std::endl;
  std::ofstream outputFile("ips_con_mayor_acceso.txt"); 
  for(int i=0 ;i<5;i++)
  {
      std::cout << repeticionesHeap.top() << " accesos" <<  std::endl;
      outputFile << repeticionesHeap.top() << " accesos" << std::endl;
      repeticionesHeap.pop();
      repeticionesHeap.heapSort();
  }
  std::cout << std::endl;
  outputFile.close();
  
  return 0;
}