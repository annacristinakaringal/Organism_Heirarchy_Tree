/*******************************************************************************
 Title          : main.cpp
 Author         : Anna Cristina Karingal
 Created on     : December 6, 2014
 
 Description    :
 
 Purpose        : Demonstrate an implementation of a binary tree class
 
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

int main(int argc, const char * argv[]) {

    if (argc == 2) {
    
        // Open file
        string fName = argv[1];''
        ifstream readf;
        readf.open("organisms.txt");
        
        
        // If file open fails
        if (readf.fail()){
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        list<binary_tree> all_single_org_trees;
        
        if (readf.is_open()) {
            
            string org_line;
            
            // Reads each line of the file
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
                    cerr << "ERROR: Failure to allocate memory while reading file" << endl;
                    exit(-1);
                }
                catch (invalid_argument& ia){
                    cerr << "ERROR: Invalid Organism. " << ia.what() << endl;
                }
                catch (...) {
                    cerr << "ERROR: Undefined."<< endl;
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
            cerr << "ERROR: Failure to allocate memory while constructing tree." << endl;
            exit(-1);
        }
        catch (invalid_argument &ia) {
            cerr << "ERROR: Unable to construct tree. " << ia.what() << endl;
        }
        catch (out_of_range &oor) {
            cerr << "ERROR: Out of Range. " << oor.what() << endl;
        }
    }

    else { // Invalid number of command line arguments. Exit with errors
        cerr << "ERROR: Invalid number of arguments" << endl;
        cerr << "Please run the program by typing into the terminal" << endl;
        cerr << "     ./binary_tree organisms.txt" << endl;
        cerr << "where organisms.txt is the name of your input file." << endl;

        exit(-1)''
    }
    
    return 0;
}
