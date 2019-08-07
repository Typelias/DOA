#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <limits>
#include <stack>
#include <queue>
#include <map>
struct vertex
{
	int id;
	std::string name;
	bool visited = false;
};

struct edge
{
	std::vector<vertex>::iterator id1, id2;
	float distance;
	std::string name;
    bool walked = false;
};

using Edges = std::vector<edge>;
using Vertices = std::vector<vertex>;
using Matrix = std::vector<std::vector<Edges::iterator> >;
using Road = std::pair<double, Vertices::iterator>;

class graph
{
    public:
    graph(std::string filename);
    void print();
    bool DFS();
    bool BFS();
    void reset();
    void findPath(std::string start, std::string end);
    bool fixBroken();
    void newFindPath(std::string start, std::string end);

    void printEdge()
    {
        std::for_each(edges.begin(),edges.end(),[&](auto e)
        {
            std::cout << e.name << " from: " << e.id1->id << " to: "<< e.id2->id << "\n";
        });
    }

    private:
    Matrix _matrix;
    Edges edges;
    Vertices vertices;
    Matrix createMatrix();
    void readFile(std::string file);
    
};