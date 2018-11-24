/* Jake Kroner
 * Graph.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation of the template Graph class
 *
 */

#include <iostream>
#include "Graph.h"
#include "Stack.h"
using namespace std;

// Function: Default constructor
// Parameters: None
// Returns: None
// Does: default constructor. Initializes with zero vertices
template<class Vertex>
Graph<Vertex>::Graph()
{
    curr_vertex = 0;
    edges = NULL;
    path = NULL;
    vertices = NULL;
    marks = NULL;
}

// Function: Parametrized constructor
// Parameters: integer (size of graph)
// Returns: nothing
// Does: parametrized constructor. Initializes with num_v vertices
template<class Vertex>
Graph<Vertex>::Graph(int num_v)
{
    initialize_graph(num_v);
}

// Function: Copy constructor
// Parameters: a Graph that is passed in by reference
// Returns: nothing
// Does: copy constructor. Deep copies the information from source
template<class Vertex>
Graph<Vertex>::Graph(const Graph<Vertex> &source)
{
    copy_graph(source);
}

// Function: Assignment overload
// Parameters: a Graph that is passed in by reference
// Returns: nothing
// Does: assignment overload. Deep copies the information from source
//       into an already existing instance of a graph
template<class Vertex>
Graph<Vertex> &Graph<Vertex>::operator=(const Graph<Vertex> &source)
{
    if(this != &source){
        delete_graph();

        copy_graph(source);
    }

    return *this;
}

// Function: Destructor
// Parameters: None
// Returns: nothing
// Does: destrutctor. Deletes information from the graph
template<class Vertex>
Graph<Vertex>::~Graph()
{
    delete_graph();
}

// Function: copy_graph
// Parameters: a Graph that is passed in by reference
// Returns: None
// Does: Performs a deep copy from source
template<class Vertex>
void Graph<Vertex>::copy_graph(const Graph<Vertex> &source)
{
    num_vertices = source.get_num_vertices();
    initialize_graph(num_vertices);

    for(int i = 0; i < num_vertices; i++){
        Vertex v = source.get_vertex(i);
        cerr << v;
        add_vertex(source.get_vertex(i));
    }

    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j< num_vertices; j++){
            if(i != j)
                add_edge(source.get_vertex(i), source.get_vertex(j), source.get_edge(i, j));
        }
    }
}

// Function: delete_graph
// Parameters: None
// Returns: None
// Does: Deletes all info from the source
template<class Vertex>
void Graph<Vertex>::delete_graph()
{
    delete [] vertices;

    for(int i = 0; i < num_vertices; i++)
        delete [] edges[i];

    num_vertices = 0;
    curr_vertex = 0;
    delete [] path;
    delete [] marks;
}

// Function: get_vertex
// Parameters: An integer representing the index of a vertex
// Returns: The vertex at that index in vertices array
// Does: Returns the vertex at this index
template<class Vertex>
Vertex Graph<Vertex>::get_vertex(int index) const
{
    return vertices[index];
}

// Function: get_edge
// Parameters: Two integers, representing a row and a column of the edges matrix
// Returns: The string associated with a given edge
// Does: Returns the string associated with the given edge
template<class Vertex>
string Graph<Vertex>::get_edge(int row, int col) const
{
    return edges[row][col];
}

// Function: get_num_vertices
// Parameters: None
// Returns: An integer representing the number of vertices in the graph
// Does: Returns the number of vertices in the graph
template<class Vertex>
int Graph<Vertex>::get_num_vertices() const
{
    return num_vertices;
}

// Function: initialize_graph
// Input: integer, number of vertices
// Returns: void
// Does: dynamically allocates all memory
//       for a graph of num_v vertices 
//       without any vertices
//       and prepares all DFS,BFS variables
template<class Vertex>
void Graph<Vertex>::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }
}

// Function: add_vertex
// Parameters: Vertex, by value
// Returns: void
// Does: Add a new vertex to the end of the 2d array
//       Initializes every from/to edge to be NULL
template<class Vertex>
void Graph<Vertex>::add_vertex(Vertex v)
{
    vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++)
     {
        edges[curr_vertex][i] = NULL_EDGE;
        edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }

// Function: add_edge
// Parameters: Two vertices, and string (movie)
// Returns: void
// Does: Adds an edge between the two vertices and 
//       assigns their movie equal to the given string
//       (in case the edge did not exist) 
 template<class Vertex>
 void Graph<Vertex>::add_edge(Vertex f, Vertex t, string movie)
 {
     int row;
     int col;

     row = index_is(vertices, f);
     col = index_is(vertices, t);
     if (edges[row][col] == NULL_EDGE)
         edges[row][col] = movie;
 }


// Function: print_matrix
// Parameters: ostream
// Returns: void
// Does: Prints the 2d adjacency matrix of the graph
template <class Vertex>
void Graph<Vertex>::print_matrix(ostream & out) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
            out << edges[i][j] << " ";
        out << endl;
    }
}


// Function: clear_marks
// Parameters: none
// Returns: none
// Does: sets all the marks to be false
//       For algorithms that need to mark vertices (BFS, DFS)
template<class Vertex>
void Graph<Vertex>::clear_marks()
{
    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
    }
}

// Function: initialize_path
// Parameters: none
// Returns: none
// Does: sets every value in the predecessor path to be NULL edge
template<class Vertex>
void Graph<Vertex>::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

// Function: update_predecessor
// Parameters: Two vertices
// Returns: None
// Does: sets pred as the predecessor of curr in the path
//       (in case that curr did not have any predecessor)
//       Nothing otherwise.
template<class Vertex>
void Graph<Vertex>::update_predecessor(Vertex pred, Vertex curr)
{
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == pred)
            pred_index = i;
        if (vertices[i] == curr)
            curr_index = i;
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

// Function: report_path
// Parameters: ostream to print, start and end vertices
// Returns: none
// Does: finds path from start to end and prints it
//       uses the information stored on predecessor path 
template<class Vertex>
void Graph<Vertex>::report_path(ostream &out, Vertex start, Vertex end) const
{
    Stack<Vertex> s;
    int index = index_is(vertices, end);
    s.push(vertices[index]);

    bool done = false;
    while (!done)
    {
        index = path[index];

        //An index of -1 means that there's no path between the two vertices
        if(index == -1){
            out << start << " and " << end << ": No connection" << endl;
            return;
        }

        if (vertices[index] == start)
            done = true;
        s.push(vertices[index]);
    }

    //Size of the stack - 1 is the costar distance (since you subtract one to
    //find the distance from the top of the stack to the bottom of it)
    out << start << " and " << end << " have a costar distance of "
        << s.get_size() - 1 << endl;

    int from, to;

    //Vertex v1;
    //Vertex v2;
    //Report the edge between the top element of the stack and the second
    //element of the stack, until there's only 1 element left in the stack
    while (s.get_size() > 1)
    {
        //First vertex is top of stack
        Vertex v1 = s.top();
        from = index_is(vertices, v1);

        s.pop();

        //Second vertex is next element in the stack
        Vertex v2 = s.top();
        to = index_is(vertices, v2);

        out << v1 << " was in " << get_edge(from, to) <<
        " with " << v2 << "" << endl;
    }
}

// Function: mark_vertex
// Parameters: Vertex
// Returns: none
// Does: sets the mark of the given vertex to true
template<class Vertex>
void Graph<Vertex>::mark_vertex(Vertex v)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

// Function: is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns true if the vertex is marked
//       false otherwise
template<class Vertex>
bool Graph<Vertex>::is_marked(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

// Function: is_vertex
// Parameters: vertex
// Returns: bool
// Does: returns true if vertex exists in the graph,
//       false otherwise.
template <class Vertex>
bool Graph<Vertex>::is_vertex(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

// Function: get_to_vertices
// Parameters: Vertex, queue of vertices by reference
// Returns: void
// Does: Finds all neighbors of the the given vertex
//       enqueues all of its neighbors to the queue
 template<class Vertex>
 void Graph<Vertex>::get_to_vertices(Vertex v, Queue<Vertex> &adj) const
 {
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++)
        if (edges[from][to] != NULL_EDGE)
            if (vertices[to] != vertices[from])
                   adj.enqueue(vertices[to]);
}


// wrapper function definitions
// Function: index_is
// Parameters: array of vertices, Vertex
// Returns: integer
// Does: Finds the target vertex in the list of vertices
//       returns the index of v
template<class Vertex>
int index_is(Vertex *vertices, Vertex v)
{
    int index = 0;
    while (!(v == vertices[index])){
        index++;
    }

    return index;
}

template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
