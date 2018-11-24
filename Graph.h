#include "Queue.h"
#include <iostream>
#include <ostream>

#ifndef GRAPH_H_
#define GRAPH_H_

class FullGraph : public exception {
public:
  const char *what() const throw() { return "My graph is full";}
};

class EmptyGraph : public exception {
public:
  const char *what() const throw() { return "My graph is empty";}
};

const int NULL_EDGE = -1;
const int NULL_PRED = -1;

// wrapper functions
template<class Vertex>
int index_is(Vertex *vertices, Vertex v);

template<class Vertex>
class Graph
{
public:
    //Constructor functions
    Graph();
    Graph(int);

    // Functions needed to modify the graph
    void initialize_graph(int);         //allocates space for vertices
    void add_vertex(Vertex);            //adds a single vertex to the graph
    void add_edge(Vertex, Vertex, int); //adds an edge to the graph

    void print_matrix(ostream &) const; //reports the edges of the graph

    // Helpers functions for implementing BFS and DFS
    bool is_vertex(Vertex) const;                        //checks if exists
    void get_to_vertices(Vertex, Queue<Vertex> &) const; //enqueues neighbors
    void clear_marks();                                  //clears all marks
    void mark_vertex(Vertex);                            //marks a vertex
    bool is_marked(Vertex) const;                        //checks if marked
    void initialize_path();                              //clears path info
    void update_predecessor(Vertex, Vertex);             //stores predecessor
    void report_path(ostream &, Vertex, Vertex) const;   //reports path

private:
    int num_vertices;       // number of vertices of the graph
    Vertex *vertices;       // stores label of vertices, if any
    int **edges;            // weighted 2-D array to store edges 


    int *path;              // array used to store a path
    int curr_vertex;        // variable to track current vertex in DFS
    bool *marks;            // 2-D array of vertices to 
};

#endif


