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
#include "Bitacora.h"

int main() {
  std::cout << "\nActividad 4.3 - Equipo 4" << std::endl;
  // try
  try {Bitacora myBitacora("bitacoraGrafos.txt");} 
  // catch
  catch (std::invalid_argument e) {std::cout << "ERROR: " << e.what() << std::endl;}
  catch (std::out_of_range e) {std::cout << "ERROR: " << e.what() << std::endl;}
  // Puntos 4
  std::cout << "\n\x1b[1m¿En qué dirección IP presumiblemente se encuentra el boot master?\x1b[0m" << std::endl;
  std::cout << "El boot master presumiblemente se encuentra en la dirección impresa ya que tiene el mayor número de conexiones con otras direcciones IP. En el caso de esta bitácora, existen dos direccioens IP con el máximo número de conexiones con otras direcciones (18)." << std::endl;
  // Puntos 6
  std::cout << "\n\x1b[1m¿Cuál es la dirección IP que presumiblemente requiere más esfuerzo para que el boot master la ataque?\x1b[0m" << std::endl;
  std::cout << "La dirección IP que presumiblemente requiere más esfuerzo es la dirección con mayor distancia del boot master. En este caso, la dirección impresa tiene el mayor valor de distancia de todas las direcciones en la bitácora (922)." << std::endl;
  // return
  std::cout << std::endl;
  return 0;
}