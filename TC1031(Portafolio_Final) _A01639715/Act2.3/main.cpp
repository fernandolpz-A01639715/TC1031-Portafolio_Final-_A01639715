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

#include "Bitacora.h"

using std::endl;
using std::cout;
using std::cin;
using std::string;

// Complejidad temporal: O(1)
Registro userInput(string inputString){
  string month, day, hour, minute, second;
  // Convertir la cadena a un stream
  std::stringstream inputStream(inputString);
  getline(inputStream, month, ' ');
  getline(inputStream, day, ' ');
  getline(inputStream, hour, ':');
  getline(inputStream, minute, ':');
  getline(inputStream, second, ' ');
  Registro tempRegistro(month, day, hour, minute, second, " ", " ", " ");
  return tempRegistro;
};

int main() {
  
  // Iniciamos el conteo del tiempo de ejecución
  auto startTime = std::chrono::high_resolution_clock::now();
  cout << "Por favor espere . . . " << endl;
  
  // Inicializar bitacora e importar datos
  Bitacora myBitacora;
  myBitacora.lecturaDatos("bitacora.txt");
  
  // Ordenar bitácora
   //myBitacora.ordenaBitacora(0, myBitacora.getListaRegistros().size() -1);
  myBitacora.mergeSort();
  // std::cout << myBitacora.getListaRegistros().getNumElements() << std::endl;
  
  // Exportar bitácora
  myBitacora.exportaBitacora("bitacora_ordenada.txt");
  
  
  
  // Input de registros de rango
  string fechaInicio, fechaFinal;
  // Ejemplo 1: Jun 01 00:22:36 - Jun 01 08:23:57
  cout << "\nIngrese fecha de inicio y final \n(en formato Jan 01 01:01:01): \n" << endl;
  cout << "Fecha de inicio: ";
  getline(cin, fechaInicio);
  cout << "Fecha final: ";
  getline(cin, fechaFinal);
  cout << endl;
  // Crear registros con fechas ingresadas
  Registro registroInicio, registroFinal;
  registroInicio = userInput(fechaInicio);
  registroFinal = userInput(fechaFinal);

  
  myBitacora.printRango(registroInicio, registroFinal);

  
   std::cout<<std::endl;
  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;
  //cout << "Tiempo de ejecución en ms: " << totalTime / std::chrono::milliseconds(1) << endl;


}