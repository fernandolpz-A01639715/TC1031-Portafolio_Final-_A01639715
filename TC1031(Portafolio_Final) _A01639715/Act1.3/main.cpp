/* 
TC1031.570
Equipo 4
- Fernando López Gómez (A01639715)
- Fausto Alejandro Palma Cervantes (A01639224)
- Lautaro Gabriel Coteja (A01571214)
Compilar: g++ -std=c++17 -Wall -o main *.cpp
Ejecutar: ./main
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
  myBitacora.ordenaBitacora(0, myBitacora.getListaRegistros().size() -1, 1); // 1 = Merge Sort (cualquier otro número es bubble sort)
  // Exportar bitácora
  myBitacora.exportaBitacora("bitacora_ordenada.txt");
  // Input de registros de rango
  string fechaInicio, fechaFinal;
  /* Ejemplo 1: Jun 01 00:22:36 - Jun 01 08:23:57 */
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
  //Comparación de registros y obtención de rango
  if (registroInicio >= myBitacora.getListaRegistros()[0] && registroFinal <= myBitacora.getListaRegistros() [myBitacora.getListaRegistros().size()-1]  && registroInicio < registroFinal){
    int indiceInicio = myBitacora.buscar(registroInicio);
    int indiceFin = myBitacora.buscar(registroFinal);
    if(indiceInicio != -1 && indiceFin != -1){
      cout << "Registros encontrados: "<<indiceFin-indiceInicio+1 << endl;
    myBitacora.printRango(indiceInicio, indiceFin); 
    } else {
      cout << "Fecha de inicio o final inexistente" << endl;
    }
  } else {
    cout << "Fecha de inicio o final inexistente" << endl;
  }
  // Terminamos conteo del tiempo de ejecución
  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;
  //cout << "Tiempo de ejecución en ms: " << totalTime / std::chrono::milliseconds(1) << endl;
  return 0;
}