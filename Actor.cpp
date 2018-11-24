#include <iostream>
#include "Actor.h"

using namespace std;

// Function: Default constructor
// Parameters: None
// Returns: None
// Does: Default constructor. Initializes actor's name with an empty string
Actor::Actor()
{
	name = "";
}

// Function: Parametrized constructor
// Parameters: A string representing the name of an actor
// Returns: None
// Does: Parametrized constructor. Initializes actor's name with the given name
Actor::Actor(string name)
{
	this -> name = name;
}

// Function: Copy constructor
// Parameters: An Actor that is passed in by reference
// Returns: None
// Does: Copy constructor. Deep copies the information from source
Actor::Actor(const Actor &source)
{
    copy_actor(source);
}

// Function: Assignment overload
// Parameters: An Actor that is passed in by reference
// Returns: None
// Does: Assignment overload. Deep copies the information from source
//       into an already existing instance of an Actor
Actor &Actor::operator=(const Actor &source)
{
    if(this != &source){
        delete_actor();

        copy_actor(source);
    }

    return *this;
}

// Function: Destructor
// Parameters: None
// Returns: None
// Does: Destrutctor. Deletes information from the Actor
Actor::~Actor()
{
    delete_actor();
}

// Function: copy_graph
// Parameters: An Actor that is passed in by reference
// Returns: None
// Does: Performs a deep copy from source
void Actor::copy_actor(const Actor &source)
{
	name = source.get_name();

	for(int i = 0; i < source.get_movies().get_length(); i++)
		insert(source.get_movies().get_value_at(i));
}

// Function: delete_graph
// Parameters: None
// Returns: None
// Does: Deletes all info from the source
void Actor::delete_actor()
{
	name = "";
	movies.make_empty();
}

// Function: insert
// Parameters: A string representing a movie that the actor played in
// Returns: None
// Does: Inserts the movie into the Linked List of the movies that the actor
//		 has played in
void Actor::insert(string movie)
{
	movies.insert(movie);
}

// Function: is_in_movie
// Parameters: A string representing a movie
// Returns: A boolean representing whether or not the actor played in this movie
// Does: Finds and returns whether or not the actor played in this movie
bool Actor::is_in_movie(string movie)
{
	for(int i = 0; i < movies.get_length(); i++){
		if(movies.get_value_at(i) == movie)
			return true;
	}

	return false;
}

// Function: connect
// Parameters: An Actor
// Returns: A string representing a movie that the actor has in common with this actor
// Does: Finds a movie that both actors have played in and returns the name of the movie
string Actor::connect(Actor a)
{
	string commonMovie = "";

	for(int i = 0; i < movies.get_length(); i++){
		if(a.is_in_movie(movies.get_value_at(i))){
			commonMovie = movies.get_value_at(i);
			break;
		}
	}

	return commonMovie;
}

// Function: get_name
// Parameters: None
// Returns: A string representing the name of the actor
// Does: Returns the actor's name
string Actor::get_name() const
{
	return name;
}

// Function: get_movies
// Parameters: None
// Returns: A linked list of the movies the actor played in
// Does: Returns the movies that the actor played in
LinkedList<string> Actor::get_movies() const
{
	return movies;
}

// Function: Overload for == operator
// Parameters: An Actor that is passed in by reference
// Returns: A boolean representing whether the actors have the same name
// Does: Returns true if the names of both actors is the same, false otherwise
bool Actor::operator==(const Actor source)
{
	return name == source.get_name();
}

// Function: Overload for != operator
// Parameters: An Actor that is passed in by reference
// Returns: A boolean representing whether the actors have different names
// Does: Returns true if the names of both actors are different, false otherwise
bool Actor::operator!=(const Actor source)
{
	return name != source.get_name();
}

// Function: Overload for != operator
// Parameters: A reference to an ostream object
// Returns: None
// Does: Prints the name of the actor
void Actor::operator<<(ostream & out)
{
	out << name << endl;
}
