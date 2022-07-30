#include "DireccionIP.h"

DireccionIP::DireccionIP() {
  ip = "";
  repeticiones = 0;
}

DireccionIP::DireccionIP(std::string ip, int repeticiones) {
  this->ip = ip;  
  this->repeticiones = repeticiones;
}

std::string DireccionIP::getAll() {
  return ip + " " + std::to_string(repeticiones);
}

int DireccionIP::getRepeticiones(){
  return this->repeticiones;
}

void DireccionIP::setRepeticiones(int nuevoValor){
  this->repeticiones = nuevoValor;
}

bool DireccionIP::operator==(const DireccionIP &other) const {
  return this->repeticiones == other.repeticiones;
}

bool DireccionIP::operator!=(const DireccionIP &other) const {
  return this->repeticiones != other.repeticiones;
}

bool DireccionIP::operator>(const DireccionIP &other) const {
  return this->repeticiones > other.repeticiones;
}

bool DireccionIP::operator<(const DireccionIP &other) const {
  return this->repeticiones < other.repeticiones;
}

bool DireccionIP::operator<=(const DireccionIP &other) const {
  return this->repeticiones <= other.repeticiones;
}

bool DireccionIP::operator>=(const DireccionIP &other) const {
  return this->repeticiones >= other.repeticiones;
}

std::ostream& operator<<(std::ostream& os, const DireccionIP& dt)
{
  os << dt.ip + " " + std::to_string(dt.repeticiones);
  return os;
}