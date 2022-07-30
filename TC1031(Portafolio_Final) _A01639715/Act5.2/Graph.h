#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "HashTable.h"
#include "LinkedList.h"
#include "ipAddress.h"
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template <class T> class Graph {
private:
  int numNodes;
  int numEdges;
  // Cada nodo tiene una llave y un objeto de datos tipo T
  std::map<int, T> nodesInfo;
  // mapea IPs por string a los objetos de la clase IpAddress
  std::map<unsigned int, ipAddress> mapIP;
  // Lista de adyacencia, vector de listas ligadas de pares (vertice, peso)
  std::vector<LinkedList<std::pair<int, int>>> adjList;
  // Tabla hash con el resumen de las IPs
  HashTable<unsigned int, ipAddress> tableH;

  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void readGraph(std::string fileName);
  void print();
  void printIpPos(ipAddress pos);
  void fillHashTable();
  ipAddress getIPSummary();

  // void outDegrees(std::string arch,std::string arch2);
  // void bootMasterDist(std::string arch);
};

// Complejidad computacional: O(1)
template <class T> Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
}

// Complejidad computacional: O(1)
template <class T> Graph<T>::~Graph() {
  adjList.clear();
  nodesInfo.clear();
  numNodes = 0;
  numEdges = 0;
}

// Complejidad computacional: O(n)
template <class T>
void Graph<T>::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// Complejidad computacional: O(n)
template <class T> void Graph<T>::readGraph(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  } else {
    while (std::getline(file, line)) {
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // std::cout << "numNodes " << numNodes << std::endl;
        // std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones
        // de la lista de adyacencia (renglon 0 no utilizado)
        adjList.resize(numNodes + 1);
        LinkedList<std::pair<int, int>> tmpList; // en ponderado lista de pares
        adjList[i] = tmpList;
      } else if (i > 0 && i <= numNodes) {
        T data = line; // ATENCION: convertir al tipo de dato adecuado
        nodesInfo.insert(std::make_pair(i, data));
        ipAddress tmpIP(line, "0", i);
        mapIP.insert(std::make_pair(
            tmpIP.getIpValue(),
            tmpIP)); // map <ipString, ipAddress> con los nodos indexados
        LinkedList<std::pair<int, int>> tmpList; // en ponderado lista de pares
        adjList[i] = tmpList;
        // std::cout << "i: " << i << " IP: " << line << " " <<
        // tmpIP.getIpIndex() << std::endl;
      } else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found - 15);
        std::size_t found2 = line.find(" ", found + 1);
        std::size_t found3 = line.find(":", found2 + 1);
        ip2 = line.substr(found2, found3 - found2);
        std::size_t found4 = line.find(" ", found3 + 1);
        std::size_t found5 = line.find(" ", found4 + 1);
        peso = line.substr(found4, found5 - found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        std::map<unsigned int, ipAddress>::iterator it1;
        int ip1Index;
        it1 = mapIP.find(tmpIP1.getIpValue());
        if (it1 != mapIP.end()) {
          ip1Index = it1->second.getIpIndex();
        } else {
          std::cout << "Not found 1: " << ip1 << std::endl;
        }
        std::map<unsigned int, ipAddress>::iterator it2;
        int ip2Index;
        it2 = mapIP.find(tmpIP2.getIpValue());
        if (it2 != mapIP.end()) {
          ip2Index = it2->second.getIpIndex();
        } else {
          std::cout << "Not found 2: " << ip2 << std::endl;
        }
        // agregar una arista mas a la ip en ip1Index
        // std::cout << "ip1Index: " << ip1Index << " ip2Index: " << ip2Index <<
        // std::endl;
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});
        it1->second.addToOutDegree();
        it2->second.addToInDegree();
      }
      i++;
    }
    file.close();
  }
}

template <class T> void Graph<T>::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++) {
    std::cout << "vertex " << u << ": ";
    LLNode<std::pair<int, int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "}  ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Grados de las IPS" << std::endl;
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); ++it)
    std::cout << "IP: " << it->second.getIp()
              << " Grado salida: " << it->second.getOutDegree()
              << " Grado entrada: " << it->second.getInDegree() << std::endl;
}

template <class T> void Graph<T>::printIpPos(ipAddress pos) {
	int u = pos.getIpIndex();
	std::cout << "Vertex: " << u << std::endl;

	std::cout << "Lista de direcciones accesadas:" << std::endl;
	LLNode<std::pair<int, int>>* ptr = adjList[u].getHead();
	while (ptr != nullptr) {
		std::pair<int, int> par = ptr->data;

		std::cout <<  nodesInfo.at(par.first)  << std::endl;
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

template <class T> void Graph<T>::fillHashTable() {
  // se fija el tamaño de la tabla hash
  // tableH.setMaxCapacity(22739);   // test 1: (13370 * 1.7) = 22729 al primo
  // más cercano
  tableH.setMaxCapacity(
      26777); // test 1: (13370 * 2.0) = 26740 al primo más cercano

  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); ++it) {
    tableH.add(it->second.getIpValue(), it->second);
  }

  std::cout << "Numero total de colisiones: " << tableH.getNumCollisions()
            << std::endl;
}

// Complejidad computacional: O(n)
template <class T> ipAddress Graph<T>::getIPSummary() {
	// usar para getIPSummary
	std::string ipSearch;
	ipAddress ipRes;
	int hashIndex = -1;
	while (true)
	{
		std::cout << "\nIngrese la IP que desea buscar: " << std::endl;
		std::cin >> ipSearch;
		ipAddress tmpIp(ipSearch, "0", 0);
		ipRes = tableH.find(tmpIp.getIpValue());
		hashIndex = tableH.getHashIndex(tmpIp.getIpValue());

		if (ipRes.getIpValue() != 0)
			break;
		else
			std::cout << "IP no valida " << std::endl;
	}
	std::cout << "\nIP: " << ipRes.getIp() << std::endl
		<< "Total de direccion accesadas desde la IP: " << ipRes.getOutDegree() << std::endl
		<< "Total de direccion que intentaron acceder a la IP: " << ipRes.getInDegree() << std::endl
    << "Hash: " << hashIndex << std::endl;
	return ipRes;
}

/*
template<class T>
void Graph<T>::outDegrees(std::string arch,std::string arch2){
  MaxHeap <ipAddress> ipsOrdenadas(numNodes);
  // Escribimos el TXT
    std::ofstream archivo(arch);
    if (!archivo.is_open()){
        std::cout<<"Error al abrir"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::ofstream archivo2(arch2);
    if (!archivo2.is_open()){
        std::cout<<"Error al abrir"<<std::endl;
        exit(EXIT_FAILURE);
    }
    archivo<< "Grados de las IPS" << std::endl;
    std::map<unsigned int, ipAddress>::iterator it;
    for (it = mapIP.begin(); it != mapIP.end(); ++it){
      archivo << "ip: " << it->second.getIp()<< " grado: " <<
it->second.getDegree() << std::endl; ipsOrdenadas.push(it->second);
    }
  archivo<< std::endl;

    for (int i = 0; i < 5; i++)
    {
      ipAddress current=ipsOrdenadas.pop();
      if (i==0)
      {
        RootMaster=current;
        std::cout<<"RootMaster -> "<<current.getIp()<<" grados:
"<<current.getDegree()<<std::endl;
      }
      archivo2<<"ip: "<<current.getIp()<<" grados:
"<<current.getDegree()<<std::endl;
    }
}

template<class T>
void Graph<T>::bootMasterDist(std::string arch){
  MaxHeap<ipAddress> distanciaDelRootMaster(numNodes);
  std::ofstream archivo(arch);
  if (!archivo.is_open()){
    std::cout<<"Error al abrir"<<std::endl;
    exit(EXIT_FAILURE);
  }
  int src=RootMaster.getIpIndex();
// Create a priority queue to store vertices that
  // are being preprocessed. This is weird syntax in C++.
  // Refer below link for details of this syntax
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  // pares (distancia, vertice)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  // Create a vector for distances and initialize all
  // distances as infinite (INF)
  std::vector<int> dist(numNodes + 1, INF);

  // Insert source itself in priority queue and initialize
  // its distance as 0.
  pq.push(std::make_pair(0, src));
  dist[src] = 0;

  // Looping till priority queue becomes empty (or all
  //distances are not finalized)
  while (!pq.empty()) {
    // The first vertex in pair is the minimum distance
    // vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted distance (distance must be first item
    // in pair)
    int u = pq.top().second;
    pq.pop();

    // 'i' is used to get all adjacent vertices of a
    // vertex
    // Recorremos los vertices vecinos de v
    LLNode<std::pair<int, int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int v = par.first;
      int weight = par.second;
      // If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight) {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(std::make_pair(dist[v], v));
      }
      ptr = ptr->next;
    }
  }
  std::map<unsigned int, ipAddress>::iterator it=mapIP.begin();
  // Print shortest distances stored in dist[]
  archivo<< "Vertex Distance from Source" << std::endl;
  for (int i = 1; i <= numNodes; ++i) {
    archivo << "vertice " << i << ":"<<it->second.getIp() <<" distancia:" <<
dist[i] << std::endl; it->second.setDist(dist[i]); it->second.setState();
    distanciaDelRootMaster.push(it->second);
    it++;
  }
  archivo<< std::endl;

  std::cout<<"Ip mas alejada o menos vulnerable:
"<<distanciaDelRootMaster.pop().getIp()<<std::endl;
}
*/

#endif // _GRAPH_H_
