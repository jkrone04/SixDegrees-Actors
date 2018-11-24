#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "Graph.h"
#include "Actor.h"

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_

class SixDegrees {
public:

	//Default constructor
	SixDegrees();
	//Destructor
	~SixDegrees();

	//Public function declarations
	void populate_graph_from_file();
	void run(istream &in, ostream &out);


private:

	//Private function declarations
	void BFS(Actor a1, Actor a2, ostream &out);
	Actor get_actor(string name);
	Actor* expand(Actor *curr);

	//Private variables
	int num_actors;
	int capacity;
	Actor *actors;
	Graph<string> g;
};

#endif
