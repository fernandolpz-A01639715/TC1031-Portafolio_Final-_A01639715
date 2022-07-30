#ifndef _DIRECCIONIP_H_
#define _DIRECCIONIP_H_

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

class DireccionIP {
  private:
    std::string ip;
    // IP en decimal
    int repeticiones;
  
  public:
    DireccionIP();
    DireccionIP(std::string ip, int repeticiones);
    std::string getAll();
    int getRepeticiones();
    void setRepeticiones(int nuevoValor);
    // sobrecarga de operadores de comparacion
    // compara dos objetos de la clase DireccionIP usando su número de repeticiones (repeticiones)
    bool operator ==(const DireccionIP&) const;
    bool operator !=(const DireccionIP&) const;
    bool operator >(const DireccionIP&) const;
    bool operator <(const DireccionIP&) const;
    bool operator >=(const DireccionIP&) const;
    bool operator <=(const DireccionIP&) const;
    friend std::ostream& operator<<(std::ostream& os, const DireccionIP& dt);
  // Referencia: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
};

#endif //_DIRECCIONIP_H_