/* Jake Kroner
 * test-graph.cpp
 * COMP15
 * Fall 2018
 *
 * Driver for HW5
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Graph.h"

using namespace std;

void BFS(string s1, string s2);
Graph<string> g;

int main() 
{
    g.initialize_graph(12); //12 vertices to be added

    //ADD VERTICES TO GRAPH
    g.add_vertex("Pizza");
    g.add_vertex("Scrambled Eggs w/ Cheese");
    g.add_vertex("Sushi");
    g.add_vertex("Carrots");
    g.add_vertex("Mac and Cheese");
    g.add_vertex("Bread");
    g.add_vertex("Bagels w/ Smoked Salmon");
    g.add_vertex("Spinach");
    g.add_vertex("Pancakes");
    g.add_vertex("Chicken Parm");
    g.add_vertex("Rice Bowl");
    g.add_vertex("Tomatoes");

    //ADD EDGES TO GRAPH
    //Hot food (assume that the chicken parm was left out and got cold)
    g.add_edge("Pizza", "Scrambled Eggs w/ Cheese", "Hot food");

    g.add_edge("Pizza", "Mac and Cheese", "Hot food");
    g.add_edge("Mac and Cheese", "Pizza", "Hot food");
    g.add_edge("Pizza", "Pancakes", "Hot food");
    g.add_edge("Pancakes", "Pizza", "Hot food");
    g.add_edge("Scrambled Eggs w/ Cheese", "Mac and Cheese", "Hot food");
    g.add_edge("Mac and Cheese", "Scrambled Eggs w/ Cheese", "Hot food");
    g.add_edge("Scrambled Eggs w/ Cheese", "Pancakes", "Hot food");
    g.add_edge("Pancakes", "Scrambled Eggs w/ Cheese", "Hot food");
    g.add_edge("Mac and Cheese", "Pancakes", "Hot food");
    g.add_edge("Pancakes", "Mac and Cheese", "Hot food");

    //Breakfast food
    g.add_edge("Scrambled Eggs w/ Cheese", "Pancakes", "Breakfast foods");
    g.add_edge("Pancakes", "Scrambled Eggs w/ Cheese", "Breakfast foods");
    g.add_edge("Scrambled Eggs w/ Cheese", "Bagels w/ Smoked Salmon", "Breakfast foods");
    g.add_edge("Bagels w/ Smoked Salmon", "Scrambled Eggs w/ Cheese", "Breakfast foods");
    g.add_edge("Bagels w/ Smoked Salmon", "Pancakes", "Breakfast foods");
    g.add_edge("Pancakes", "Bagels w/ Smoked Salmon", "Breakfast foods");

    //Cheese and Marinara Sauce
    g.add_edge("Chicken Parm", "Pizza", "Cheese and Marinara Sauce");
    g.add_edge("Pizza", "Chicken Parm", "Cheese and Marinara Sauce");

    //Cheesy
    g.add_edge("Scrambled Eggs w/ Cheese", "Mac and Cheese", "Cheesy");
    g.add_edge("Mac and Cheese", "Scrambled Eggs w/ Cheese", "Cheesy");
    g.add_edge("Scrambled Eggs w/ Cheese", "Chicken Parm", "Cheesy");
    g.add_edge("Chicken Parm", "Scrambled Eggs w/ Cheese", "Cheesy");
    g.add_edge("Chicken Parm", "Mac and Cheese", "Cheesy");
    g.add_edge("Mac and Cheese", "Chicken Parm", "Cheesy");

    //Fish
    g.add_edge("Sushi", "Bagels w/ Smoked Salmon", "Fish");
    g.add_edge("Bagels w/ Smoked Salmon", "Sushi", "Fish");

    //Rice
    g.add_edge("Rice Bowl", "Sushi", "Rice");
    g.add_edge("Sushi", "Rice Bowl", "Rice");

    //Healthy
    g.add_edge("Carrots", "Spinach", "Healthy");
    g.add_edge("Spinach", "Carrots", "Healthy");
    g.add_edge("Spinach", "Tomatoes", "Healthy");
    g.add_edge("Tomatoes", "Spinach", "Healthy");
    g.add_edge("Tomatoes", "Carrots", "Healthy");
    g.add_edge("Carrots", "Tomatoes", "Healthy");



    //TESTING WITH BFS - BFS uses most of the functions in Graph.cpp, so this
    //is testing many Graph functions inside one function.

    //Case 1: Path from Pizza to Mac and Cheese - should have costar distance of 1
    //This tests for vertices that are connected to each other via a common edge
    BFS("Pizza", "Mac and Cheese");
    cout << endl;

    //Case 2: Path from Rice Bowl to Pancakes - should have costar distance of 3
    //This tests for vertices that are connected via only one valid path
    BFS("Rice Bowl", "Pancakes");
    cout << endl;

    //Case 3: Path from Rice Bowl to Chicken Parm - should have costar distance of 4
    //  Many valid paths - shortest is: Rice Bowl - Sushi - Bagels w/ Smoked Salmon - 
    //                                  Scrambled Eggs w/ Cheese - Chicken Parm
    //  A couple other paths: Rice Bowl - Sushi - Bagels w/ Smoked Salmon - Pancakes - Pizza - 
    //                          Chicken Parm (costar distance of 5)
    //                Rice Bowl - Sushi - Bagels w/ Smoked Salmon - Scrambled Eggs w/ Cheese -
    //                          Pizza - Mac and Cheese - Chicken Parm (costar distance of 6)
    //This tests for vertices that are connected via many possible paths - it makes sure that
    //BFS chooses the shortest one
    BFS("Rice Bowl", "Chicken Parm");
    cout << endl;

    //Case 4: Path from Tomatoes to Pancakes - should have no connection
    //This tests for vertices that have no connection to each other
    BFS("Tomatoes", "Pancakes");
    cout << endl;

    //Case 5: Path from Pancakes to Steak - should cout "Sorry, Steak is not in the list"
    //This tests for vertices that don't exist in the graph
    BFS("Pancakes", "Steak");
    cout << endl;


    //TESTING with populate_graph_from_file is done in main. It was originally
    //tested with smaller input files and eventually tested with actors.txt

    //TESTING with copy constructor and assignment operator
    cout << "\n\n\n\nG2 Matrix: \n\n" << endl;
    Graph<string> g2(g);
    g2.print_matrix(cout);

    cout << "\n\n\n\nG3 Matrix: \n\n" << endl;
    Graph<string> g3(g);
    g3 = g2;
    g3.print_matrix(cout);

    return 0;
}

// Function BFS
// Parameters: a starting Vertex, an ending Vertex, and a reference to an ostream
// Returns: None
// Does: Searches for the shortest path from starting Vertex to ending Vertex
//       using Breadth First Search and reports the path if it found one
void BFS(string s1, string s2)
{
    if(!g.is_vertex(s1)){
        cout << "Sorry, " << s1 << " is not in the list\n\n";
        return;
    }

    if(!g.is_vertex(s2)){
        cout << "Sorry, " << s2 << " is not in the list\n\n";
        return;
    }

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
    g.report_path(cout, s1, s2);
}