#include "ipAddress.h"

// Complejidad computacional: O(1)
ipAddress::ipAddress(){
  ipString = "0.0.0.0";
  ipPort = "0000";
  ipIndex = 0;
  degree = 0;
  ipValue = 0;
}

// Complejidad computacional: O(n)
ipAddress::ipAddress(std::string _ip, std::string _port, int idx){
  ipString=_ip;
  ipPort=_port;
  ipIndex = idx;
  degree = 0;
  // Convertir IP
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  int partA = std::stoi(results[0]);
  int partB = std::stoi(results[1]);
  int partC = std::stoi(results[2]);
  int partD = std::stoi(results[3]);
  ipValue = partA*(pow(256,3)) + partB*(pow(256,2)) + partC*(pow(256,1)) + partD;
  

}

// Complejidad computacional: O(1)
std::string ipAddress::getIp(){
  return ipString;
}

// Complejidad computacional: O(1)
unsigned int ipAddress::getIpValue(){
  return ipValue;
}

// Complejidad computacional: O(1)
int ipAddress::getIpIndex(){
  return ipIndex;
}

// Complejidad computacional: O(1)
bool ipAddress::operator==(const ipAddress &other) {
  return this->degree == other.degree;
}

// Complejidad computacional: O(1)
bool ipAddress::operator!=(const ipAddress &other) {
  return this->degree != other.degree;
}

// Complejidad computacional: O(1)
bool ipAddress::operator>(const ipAddress &other) {
  return this->degree > other.degree;
}

// Complejidad computacional: O(1)
bool ipAddress::operator>=(const ipAddress &other) {
  return this->degree >= other.degree;
}

// Complejidad computacional: O(1)
bool ipAddress::operator<(const ipAddress &other) {
  return this->degree < other.degree;
}

// Complejidad computacional: O(1)
bool ipAddress::operator<=(const ipAddress &other) {
  return this->degree <= other.degree;
}

//Complejidad O(1)
void ipAddress::addToDegree(){
  degree++;
}

//Complejidad O(1)
int ipAddress::getDegree(){
  return degree;
}

// Complejidad computacional: O(1)
std::ostream& operator<<(std::ostream& os, const ipAddress& dt) {
  // Referencia: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
  os << "(" << dt.ipString + ", " + std::to_string(dt.degree) << ")";
  return os;
}