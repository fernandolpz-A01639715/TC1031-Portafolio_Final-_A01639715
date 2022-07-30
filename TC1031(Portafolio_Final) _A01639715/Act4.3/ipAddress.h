#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <cmath>
#include <iostream>
#include <vector>

class ipAddress {
    private:
      std::string ipString;
      std::string ipPort;
      int ipIndex;
      unsigned int ipValue;
      int degree;
    public:
      ipAddress();
      ipAddress(std::string _ip, std::string _port, int idx);
      std::string getIp();
      unsigned int getIpValue();
      int getIpIndex();
      void addToDegree();
      int getDegree();
      bool operator ==(const ipAddress&);
      bool operator !=(const ipAddress&);
      bool operator >(const ipAddress&);
      bool operator >=(const ipAddress&);
      bool operator <(const ipAddress&);
      bool operator <=(const ipAddress&);
      friend std::ostream& operator<<(std::ostream& os, const ipAddress& dt);
};


#endif
