#include <iostream>
#include "graph.h"

int main()
{
	graph m("export.txt");
	//m.print();
	//if(m.DFS() == false) //std::cout << "(DFS)Not all vertices where visited\n";
	//else std::cout << "(DFS)All verices where visited\n";
	//m.reset();
	//if(m.BFS() == false) //std::cout << "(BFS)Not all vertices where visited\n";
	//else std::cout << "(BFS)All verices where visited\n";
	//m.reset();
	//m.fixBroken();



	//m.printEdge();

	//m.print();

	m.findPath("Nackstavägen Axvägen 1","Förrådet");
	std::cout << "\n\n";
	//m.newFindPath("Nackstavägen Axvägen 1","Förrådet");
	m.findPath("Nackstavägen Axvägen 1","Skyddsrum");
	//m.findPath("L319","D025");
	std::cout << "\n\n";
	//m.findPath("Storgatan Rondell Universitetet","Bite Line West");
}
