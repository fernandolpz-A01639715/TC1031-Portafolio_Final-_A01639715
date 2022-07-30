#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// #include <utility> 
#include <map>
// #include <set>
#include <queue>
#include "LinkedList.h"
#include "ipAddress.h"
#include "PriorityQueue.h"

#define INF 0x3f3f3f3f

template <class T>
class Graph {
  private:
    int numNodes;
    int numEdges; 
    // Cada nodo tiene una llave y un objeto de datos tipo T
    std::map<int, T> nodesInfo;
    // mapea IPs por string a los objetos de la clase IpAddress
    std::map<unsigned int, ipAddress> mapIP;
    // Lista de adyacencia, vector de listas ligadas de pares (vertice, peso)
    std::vector<LinkedList<std::pair<int, int>>> adjList;
    void split(std::string line, std::vector<int> &res);
    ipAddress bootMaster;
    
  public:
    Graph();
    ~Graph();
    void readGraph(std::string fileName);
    int outDegrees(std::string fileName);
    void shortestPath(int src, std::string fileName);
};

template <class T>
// Complejidad computacional: O(1)
Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
}

// Complejidad computacional: O(1)
template <class T>
Graph<T>::~Graph() {
  adjList.clear();
  nodesInfo.clear();
  numNodes = 0;
  numEdges = 0;
}

template <class T>
// Complejidad computacional: O(n)
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

template <class T>
// Complejidad computacional: O(V + E)
void Graph<T>::readGraph(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) {
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        //std::cout << "numNodes " << numNodes << std::endl;
        //std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones 
        // de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
        adjList[i] = tmpList;
      }
      else if (i > 0 && i <= numNodes) {
        T data = line; // ATENCION: convertir al tipo de dato adecuado
        nodesInfo.insert(std::make_pair(i, data));  
        ipAddress tmpIP(line, "0", i); 
        mapIP.insert(std::make_pair(tmpIP.getIpValue(), tmpIP)); // map <ipString, ipAddress> con los nodos indexados
        LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
        adjList[i] = tmpList;
        //std::cout << "i: " << i << " IP: " << line << " " << tmpIP.getIpIndex() << std::endl;
      }
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);      
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        std::map<unsigned int, ipAddress>::iterator it1;
        int ip1Index;
        it1 = mapIP.find(tmpIP1.getIpValue());     
        if(it1 != mapIP.end()) {
          ip1Index = it1->second.getIpIndex();
        }
        else {
          std::cout << "IP Not Found (1): " << ip1 << std::endl;
        }
        std::map<unsigned int, ipAddress>::iterator it2;
        int ip2Index;
        it2 = mapIP.find(tmpIP2.getIpValue());     
        if(it2 != mapIP.end()) {
          ip2Index = it2->second.getIpIndex();
        }
        else {
          std::cout << "IP Not Found (2): " << ip2 << std::endl;
        }
        // agregar una arista mas a la ip en ip1Index
        //std::cout << "ip1Index: " << ip1Index << " ip2Index: " << ip2Index << std::endl;
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});         
        it1->second.addToDegree();
      }
      i++;
    }
    file.close();
  }
}

template <class T>
// Complejidad computacional: O(V + E)
int Graph<T>::outDegrees(std::string fileName) {
  std::ofstream outputFile(fileName);
  std::map<unsigned int, ipAddress>::iterator it;
  PriorityQueue<ipAddress> GradosIP(mapIP.size()); 
  // CREATE QUEUE PriorityQueue(int capacity)
  for (it= mapIP.begin(); it != mapIP.end(); ++it){
    GradosIP.push(it->second);
    outputFile << "(" << it->second.getIp() << ", " << it->second.getDegree() << ")" << std::endl;
  }
  outputFile.close();
  // EXPORTAMOS
  //GradosIP.exportar("mayores_grados_ips.txt", 5);
  std::ofstream destinyFile("mayores_grados_ips.txt");
  for (int i = 0; i < 6; i++) {
    ipAddress ipTmp = GradosIP.top(); // top
    destinyFile << ipTmp << std::endl;
    if(i == 0){
      bootMaster = ipTmp;
    }
    GradosIP.pop(); // pop
  }
  destinyFile.close();
  // BOOT MASTER
  // Referencia: https://www.codegrepper.com/code-examples/cpp/c%2B%2B+bold+text
  std::cout << "\n\x1b[1mBoot Master: \x1b[0m" << bootMaster;
  return bootMaster.getIpIndex();
}

template <class T>
// Complejidad computacional: O(E log V)
// Prints shortest paths from src to all other vertices
void Graph<T>::shortestPath(int src, std::string fileName) {
  // Create a priority queue to store vertices that are being preprocessed. This is weird syntax in C++. Refer below link for details of this syntax: https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  // pares (distancia, vertice)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
  // Create a vector for distances and initialize all distances as infinite (INF)
  std::vector<int> dist(numNodes+1, INF);
  // Insert source itself in priority queue and initialize its distance as 0.
  pq.push(std::make_pair(0, src));
  dist[src] = 0;
  /* Looping till priority queue becomes empty (or all
  distances are not finalized) */
  while (!pq.empty()) {
    // The first vertex in pair is the minimum distance vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it has to be done this way to keep the vertices sorted distance (distance must be first item in pair)
    int u = pq.top().second;
    pq.pop();
    // 'i' is used to get all adjacent vertices of a vertex
    // Recorremos los vertices vecinos de v
    LLNode<std::pair<int, int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      std::pair<int,int> par = ptr->data;
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
  // Export shortest distances stored in dist[]
  std::ofstream outputFile(fileName);
  int lejos = 1;
  for (int i = 1; i <= numNodes; ++i){ 
    outputFile << "(" << nodesInfo[i] << ", " << dist[i] << ")" << std::endl; 
    if(dist[i] > dist[lejos]) {lejos = i;}
  }
  outputFile.close();
  // ESFUERZO BOOT MASTER
  // Referencia: https://www.codegrepper.com/code-examples/cpp/c%2B%2B+bold+text
  std::cout << "\n\x1b[1mIP de mayor esfuerzo: \x1b[0m(" << nodesInfo[lejos] << ", " << dist[lejos] << ")" << std::endl;  
}

#endif  // _GRAPH_H_
