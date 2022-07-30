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
  //Bitacora myBitacora("bitacoraGrafos.txt");
  Bitacora myBitacora("bitacoraGrafos.txt");
  
  return 0;
}