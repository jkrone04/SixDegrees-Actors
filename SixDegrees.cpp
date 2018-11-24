#include "SixDegrees.h"
#include "Queue.h"

using namespace std;

const int DEFAULT_CAPACITY = 50;

// Function: Default constructor
// Parameters: None
// Returns: None
// Does: Default constructor. Initializes actor array with the default capacity
//       with no actors in it
SixDegrees::SixDegrees()
{
    num_actors = 0;
    capacity = DEFAULT_CAPACITY;
    actors = new Actor[capacity];
}

// Function: Destructor
// Parameters: None
// Returns: None
// Does: Destrutctor. Deletes information from the SixDegrees instance
SixDegrees::~SixDegrees()
{
    delete [] actors;
    num_actors = 0;
    capacity = 0;
}

// Function populate_graph_from_file
// Parameters: None
// Returns: None
// Does: inserts actors into the dynamic array of actors
//       creates one vertex for each actor
//       creates an edge between actors if they participated in the same movie
void SixDegrees::populate_graph_from_file()
{
    ifstream in;

    //Open file
    in.open("actors.txt");
    if (!in.is_open())
    {
        cerr << "Could not open file for reading\n";
        exit(1);
    }

    //Populate actors array
    string prev_line = "*"; //Starts out as asterisk so Case 1 is initially satisfied
    string line = "";
    while (getline(in, line)) {
        //Case 1: The line is the name of an actor
        if(line != "*" && prev_line == "*"){
            //Expand dynamic array if necessary
            if(num_actors == capacity)
                actors = expand(actors);

            //Add an actor to the array and increment
            actors[num_actors] = Actor(line);
            num_actors++;
        }
        //Case 2: The line is a movie that the actor participated in
        else if(line != "*" && prev_line != "*"){
            actors[num_actors - 1].insert(line);
        }
        //Case 3: The line is a '*' --> do nothing

        prev_line = line;
    }

    g.initialize_graph(num_actors);

    //Add vertices to the graph
    for(int i = 0; i < num_actors; i++){
        g.add_vertex(actors[i].get_name());
    }

    //Add edges to the graph
    for(int i = 0; i < num_actors; i++){
        for(int j = 0; j < num_actors; j++){
            if(j != i && actors[i].connect(actors[j]) != ""){
                g.add_edge(actors[i].get_name(), actors[j].get_name(), 
                    actors[i].connect(actors[j]));
             }
        }
    }

    in.close();
}

// Function: run
// Parameters: References to an istream and an ostream object
// Returns: None
// Does: Continually prompts for the names of two actors and then calls the BFS function
//       If istream is cin, then it enters interactive mode (via stdin)
//       If istream is not cin, then it enters file-based mode (collects info from a file)
void SixDegrees::run(istream &in, ostream &out)
{
    out << "Enter two actor names separated by a new line." << endl;
    out << "Press ctrl-D to quit" << endl;

    //compare is true when two actors have been entered/processed, and the program
    //is ready to call BFS. It is false when only one actor has been entered, in
    //which case it will hold off on calling BFS until another is entered.
    bool compare = false;

    string line = "";
    string a1, a2; //Represents names of the actors
    while(!in.eof()){
        //Get the name of the actor
        getline(in, line);

        //Set the first actor to the given line
        if(!compare){
             a1 = line;
             compare = true;
        }
        //Set the second actor to the given line
        else{
           a2 = line;
           compare = false;


            if(!g.is_vertex(a1) || !g.is_vertex(a2)){
                if(!g.is_vertex(a1))
                    out << "Sorry, " << a1 << " not in the list\n\n";
                else
                    out << "Sorry, " << a2 << " not in the list\n\n";
                    }
            else{
                //Call BFS with the two actors' names
                BFS(get_actor(a1), get_actor(a2), out);
                out << endl;
            }
        }
    }
}

// Function BFS
// Parameters: a starting Vertex, an ending Vertex, and a reference to an ostream
// Returns: None
// Does: Searches for the shortest path from starting Vertex to ending Vertex
//       using Breadth First Search and reports the path if it found one
void SixDegrees::BFS(Actor a1, Actor a2, ostream &out)
{
    string s1 = a1.get_name();
    string s2 = a2.get_name();

    g.clear_marks();
    g.initialize_path();

    //Create the two queues that are needed for a BFS
    Queue<string> primary;
    Queue<string> neighbors;

    string curr;
    string neighbor;
    bool found = false;

    //Step 1: Enqueue the source vertex onto the first queue
    primary.enqueue(s1);

    //Keep looping until the primary queue is empty or until the ending vertex is found
    while(!primary.is_empty() && !found){
        //Step 2: Dequeue a vertex from the primary queue.
        // If it's not the ending vertex, enqueue its neighbors onto the secondary queue
        primary.dequeue(curr);
        g.mark_vertex(curr);

        if(curr == s2)
            found = true;

        else{
            g.get_to_vertices(curr, neighbors);

            //Keep looping until the secondary queue is empty
            while(!neighbors.is_empty()){
                //Step 3: Dequeue each vertex from the secondary queue
                //If we haven't visited it yet, check if it's the ending vertex.
                //If not, then enqueue it into the primary queue.
                neighbors.dequeue(neighbor);

                if(!g.is_marked(neighbor)){
                    //Mark vertex and update its predecessor
                    g.mark_vertex(neighbor);
                    g.update_predecessor(curr, neighbor);

                    if(neighbor == s2)
                        found = true;
                    else{
                        primary.enqueue(neighbor);
                        //Step 4: Repeat step 2 with this next vertex in the primary queue
                    }
                }
            }
        }
    }

    //Step 5: Reconstruct & report the path
    g.report_path(out, s1, s2);
}

// Function: get_actor
// Parameters: A string representing the name of an actor
// Returns: The actor that has this name
// Does: Finds and returns the actor that has this name
Actor SixDegrees::get_actor(string name)
{
    for(int i = 0; i < num_actors; i++){
        if(actors[i].get_name() == name)
            return actors[i];
    }

    return actors[0];
}

// Function: expand
// Parameters: A pointer to an Actor array
// Returns: A pointer to an Actor array that has twice the capacity of the original
// Does: Deletes the old array and creates a new array with double the capacity
//       Moves elements from the original array to the new array
Actor* SixDegrees::expand(Actor *curr)
{
    int new_capacity = capacity * 2;
    Actor *more = new Actor[new_capacity];

    //Transfer elements
    for(int i = 0; i < capacity; i++)
        more[i] = curr[i];

    //Delete original array
    delete [] curr;

    capacity = new_capacity;

    return more;
}
