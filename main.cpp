/*******************************************************************************
 Title          : main.cpp
 Author         : Anna Cristina Karingal
 Created on     : December 6, 2014
 
 Description    : Constructs a binary tree from a given input file of organisms
                    and their genome scores. This binary tree represents how
                    closely related an organism is to others based on their 
                    genome scores.
 
 Purpose        : To demonstrate an implementation of a binary tree class.
 
 Usage          : ./binary_tree organisms.txt
 (organisms.txt is the file path and name of the songs file and is
 an optional argument. If no argument is given, program will exit with errors.)
 
 Build with     : g++ -o binary_tree main.cpp binary_tree.cpp tree_node.cpp 
 
 Last modified  : December 14, 2014
 
 *******************************************************************************/

#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <stdexcept>
#include <new>

#include "binary_tree.h"

using namespace std;


/******************************************************************************
                                MAIN PROGRAM
 ******************************************************************************/

int main(int argc, const char * argv[]) {

    if (argc == 2) { // Input file given as argument in command line
    
        // Open file from command line argument
        string fName = argv[1];
        ifstream readf;
        readf.open("organisms.txt");
        
        // If file open fails
        if (readf.fail()){
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        // A list of binary trees to store all single node trees read from file
        list<binary_tree> all_single_org_trees;
        
        if (readf.is_open()) {
            
            // Reads each line of the file
            string org_line;
            while (getline(readf,org_line)) {
                
                try {
                    
                    // Parse line in file and turn into new single node binary tree
                    binary_tree parse(org_line);
                    
                    // Create new copy of tree so won't get re-written when reading
                    // next line in the file
                    binary_tree single_organism_tree(parse);
                    
                    // Add tree to list of single organism trees
                    // Will throw bad_alloc if unsuccessful
                    all_single_org_trees.push_back(single_organism_tree);
                    
                }
                catch (bad_alloc& ba) {
                    // Catch any memory allocation errors and exit
                    cerr << "ERROR: Failure to allocate memory while reading file" << endl;
                    exit(-1);
                }
                catch (invalid_argument& ia){
                    // Catch any invalid lines from file. Print to error stream and skip over.
                    cerr << "ERROR: Invalid Organism. " << ia.what() << endl;
                }
            }
        }
        
        // Close file
        readf.close();
        
        try {
            // Create new binary tree from list of single node organism trees
            binary_tree organisms_tree(all_single_org_trees);
            
            // Output binary tree to console
            cout << organisms_tree << endl;
        }
        
        catch (bad_alloc& ba) {
            // Catch any memory allocation errors and exit
            cerr << "ERROR: Failure to allocate memory while constructing tree." << endl;
            exit(-1);
        }
        catch (invalid_argument &ia) {
            // Catch any invalid arguments, e.g. if no organisms in list. 
            // Tell user cause of error and exit.
            cerr << "ERROR: Unable to construct tree. " << ia.what() << endl;
            exit(-1);
        }
    }

    else { // Invalid number of command line arguments. Exit with errors.
        cerr << "ERROR: Invalid number of arguments" << endl;
        cerr << "Please run the program by typing into the terminal './binary_tree organisms.txt' where organisms.txt is the name of your input file." << endl;

        exit(-1);
    }
    
    return 0;
}
