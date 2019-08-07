#include "graph.h"

graph::graph(std::string filename)
{
    readFile(filename);
    if(!vertices.empty() && !edges.empty()) _matrix = createMatrix();
    else std::cout << "File not found\n";
}

void graph::readFile(std::string file)
{
    std::fstream in;
    in.open(file);

    vertex tempv;
	edge tempe;

	std::string temp;
	while (std::getline(in,temp, ' '))
	{
		if (temp == "#")
		{
			in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			continue;
		}
		if (temp == "M")
		{
			std::getline(in, temp, ' ');
			tempv.id = std::stoi(temp);
			std::getline(in, temp, '\n');
			tempv.name = temp;
			vertices.push_back(tempv);
		}
		else
		{
			int i = std::stoi(temp);
			tempe.id1 = std::find_if(vertices.begin(), vertices.end(),[&](auto e)
			{
				return (i == e.id);
			}); 
			std::getline(in, temp, ' ');
			i = std::stoi(temp);
			tempe.id2 = std::find_if(vertices.begin(), vertices.end(), [&](auto e)
			{
				return (i == e.id);
			});
			std::getline(in, temp, ' ');
			tempe.distance = std::stof(temp);
			std::getline(in, temp, '\n');
			tempe.name = temp;
			edges.push_back(tempe);
		}
	}
}

Matrix graph::createMatrix()
{
    Matrix matrix(vertices.size(), std::vector<Edges::iterator>(vertices.size(), edges.end()));

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		matrix[it->id1->id][it->id2->id] = it;
	}

    return matrix;
}

void graph::print()
{
    Edges::iterator it = edges.end();
    std::cout << "   ";
	for (int i = 0; i < _matrix.size(); i++)
	{
		std::cout << i << "   ";
	}
	std::cout << "\n";
	int i = 0;
	std::for_each(_matrix.begin(), _matrix.end(), [&](auto e)
	{
		std::cout << i << "   ";
		std::for_each(e.begin(), e.end(), [&](auto f)
		{
			if(f != it ) std::cout << f->distance << "   ";
			else std::cout << "   ";
		});
		std::cout << "\n";
		i++;
	});
}

bool graph::DFS()
{
    std::stack<Vertices::iterator> s;
	vertices[0].visited = true;
	s.push(vertices.begin() );
	while(!s.empty())
	{
        auto edge = edges.end();
        for(auto &c : _matrix[s.top()->id])
        {
            if(c != edges.end() && !c->id2->visited) edge = c;
        }

       if(edge != edges.end() )
        {
            edge->id2->visited = true;
            s.push(edge->id2);
        }
        else s.pop(); 
	}

	/*std::cout << "{";
	for(auto &g : vertices)
	{
		std::cout << g.visited << " ";
	}
	std::cout << "}\n";*/

    for(auto &v : vertices) 
	{
		if(v.visited == false)
		{
			//std::cout << "ID: " << v.id << " With the name: " << v.name << " was not visited, returning false.\n";
			return false;
		}
	}

	return true;
}

void graph::reset()
{
	for(auto &v : vertices)
	{
		v.visited = false;
	}
}

bool graph::BFS()
{
	std::queue<Vertices::iterator> q;
	q.push(vertices.begin());
	while(!q.empty())
	{
		q.front()->visited = true;
		for(auto &c : _matrix[q.front()->id])
		{
			if(c != edges.end() && !c->id2->visited) q.push(c->id2);
		}
		q.pop();
	}

	/*std::cout << "{";
	for(auto &g : vertices)
	{
		std::cout << g.visited << " ";
	}
	std::cout << "}\n";*/

	for(auto &g : vertices)
	{
		if(g.visited == false) 
		{
			//std::cout << "ID: " << g.id << " With the name: " << g.name << " was not visited, returning false.\n"; 
			return false;
		}
	}

	return true;
}

void graph::findPath(std::string start, std::string end)
{
	this->reset();
	for(auto &e:edges)
	{
		e.walked = false;
	}
	Vertices::iterator _start = std::find_if(vertices.begin(), vertices.end(), [&](auto e)
	{
		return (e.name == start);
	});

	//std::cout << _start->name << ", " << _start->id << "\n";
	Vertices::iterator _end = std::find_if(vertices.begin(), vertices.end(), [&](auto e)
	{
		return (e.name == end);
	});
	std::cout << _end->name << ", " << _end->id << "\n";

	if(_start == _end)
	{
		std::cout << "Distance: 0, start = end\n";
		return;
	}
	if(!this->DFS())
	{
		bool temp = this->fixBroken();
		if(!temp)
		{
			return;
		}
	}
	std::map<Vertices::iterator, std::pair<float,Vertices::iterator>> distances;
	for(auto i = vertices.begin(); i != vertices.end(); i++)
	{
		distances[i] = Road((std::numeric_limits<float>::max()),i);
	}
	distances[_start] = Road(0.f,_start);
	std::stack<Vertices::iterator> s;
	s.push(_start);

	while(!s.empty())
	{
		auto road = std::find_if(edges.begin(),edges.end(),[&](auto e)
		{
			return s.top()->id == e.id1->id && e.walked == false;
		});
		if(road != edges.end())
		{
			//std::cout << road->id1->id << "\t" << road->name << "\t" << road->id2->id << "\n";
			road->walked = true;
			if(distances[road->id2].first > road->distance + distances[s.top()].first)
			{
				distances[road->id2] = Road(road->distance + distances[s.top()].first,s.top());
			}
			s.push(road->id2);
		}
		else s.pop();
	}
	std::vector<Edges::iterator> path;
	Vertices::iterator temp = _end;
	while(temp != _start)
	{
		auto edge = std::find_if(edges.begin(),edges.end(),[&](auto f)
		{
			//std::cout << f.name << "\n";
			return f.id2 == temp && distances[temp].second == f.id1;
		});

		if(edge != edges.end())
		{
			//std::cout << edge->name << "\n";
			path.push_back(edge);
		}
		temp = edge->id1;
	}
	//std::cout << path.size() << "\n";
	std::reverse(path.begin(),path.end());
	std::cout << "Distance from: " << _start->name << " To: " << _end->name << " Is: " << distances[_end].first << "\n";
	std::cout << "The path is: \n";
	std::for_each(path.begin(),path.end(),[&](auto k)
	{
		std::cout <<"From: " << k->id1->name << /*" Via: " << k->name <<*/ " To: " << k->id2->name <<" then ";
	});
	std::cout << "you are there \n";

	/*for(auto i = vertices.begin(); i!= vertices.end(); i++)
	{
		std::cout << distances[i].first << "\t" << i->id << "\n";
	}*/

	

}

bool graph::fixBroken()
{
	if(this->BFS() == true)
	{
		std::cout << "Nothing is broken\n";
		return false;
	}

	edge temp;

	
	std::stack<vertex> brokenVert;

	std::for_each(vertices.begin(), vertices.end(), [&](auto e)
	{
		if(e.visited == false)
		{
			brokenVert.push(e);
		}
	});
	int i = 0;
	while(!brokenVert.empty())
	{
		Edges::iterator iter = std::find_if(edges.begin(),edges.end(),[&](auto e){return e.id1->id == brokenVert.top().id;});
		if(iter !=edges.end())
		{
			//std::cout << "Found road from " << brokenVert.top().name << "\n";
			temp.id1 = iter->id2;
			temp.id2 = iter->id1;
			temp.distance = iter->distance;
			temp.name = "Reverse of "+iter->name;
			edges.push_back(temp);
			brokenVert.pop();
		}
		else
		{
			std::cout << "No road from vertex " << brokenVert.top().name << " was found, not able to create new road\n";
			brokenVert.pop(); 
		}
		i++;
		
	}

	//std::cout << i << "\n";

	if(this->DFS() == true)
	{
		//std::cout << "All roads where patched\n";
		return true;

	}

	return false;

	

	

}

void graph::newFindPath(std::string start, std::string end)
{
	if(!this->DFS())
	{
		if(!this->fixBroken())
		{
			return;
		}
	}
	
	this->reset();

	Vertices::iterator _start = std::find_if(vertices.begin(), vertices.end(), [&](auto e)
	{
		return (e.name == start);
	});
	Vertices::iterator _end = std::find_if(vertices.begin(), vertices.end(), [&](auto e)
	{
		return (e.name == end);
	});

	if(_start == _end)
	{
		std::cout << "Distance 0: start is the same as end\n";
		return;
	}



}
