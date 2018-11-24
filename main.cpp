/*
 * Driver
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	//Create instance of SixDegrees class and populate the graph with given file
    SixDegrees sd;
    sd.populate_graph_from_file();

    //Case 1: 0 command line arguments are provided
    //Read from cin and write to cout
    if(argc == 1){
    	sd.run(cin, cout);
    }
    //Case 2: 1 command line argument is provided
    //Call an ifstream that reads from the file provided, and write to cout
 	else if(argc == 2){
 		//Create ifstream object and open the file
 		ifstream infile;
 		string inputFile = argv[1];
    	infile.open(inputFile.c_str());

   		//Gives error if it has trouble opening the input file
    	if (!infile.is_open())
    		cerr << "ERROR: File does not exist\n";

		sd.run(infile, cout);

		infile.close();
 	}
 	//Case 3: More than one command line argument is provided
 	//Inform the user that too many arguments were provided, and quit
 	else{
 		cout << "Too many arguments provided!" << endl;
 	}

    return 0;
}
