#include <iostream>
#include <ostream>
#include <string>
#include "LinkedList.h"

#ifndef ACTOR_H_
#define ACTOR_H_

class Actor {
public:

	//Constructors
	Actor(); //Default
	Actor(string name); //Parameterized
	Actor(const Actor &source); //Copy

	//Asignment overload
    Actor &operator=(const Actor &source);

    //Destructor
    ~Actor();
    
    //Public function declarations
	void insert(string movie);
	bool is_in_movie(string movie);
	string connect(Actor a);

	//Getters
	string get_name() const;
	LinkedList<string> get_movies() const;

	//Overload of operators
	bool operator==(const Actor source);
	bool operator!=(const Actor source);
	void operator<<(ostream & out);


private:

	//Private function declarations
    void copy_actor(const Actor &source);
    void delete_actor();

    //Private variables and data structures
	string name;
	LinkedList<string> movies;
};

#endif
