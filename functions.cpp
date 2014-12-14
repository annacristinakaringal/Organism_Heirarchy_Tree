

#include "functions.h"

binary_tree string_to_single_node_tree(string o) {
    
    istringstream orgss(o);
    
    // Splits each line into name and score
    string name, score_string;
    getline(orgss, name, ' ');
    getline(orgss, score_string);
    
    // Throw exception if name is empty
    if (name.empty()) { throw 0; }
    
    // TODO: strip score_string of whitespaces
        
    // Verify score is a number
    istringstream scoress(score_string);
    float score;
    // TODO: How to throw exception if this doesn't work?
    scoress >> score;
    
    if (!score_string.empty()) {
        // Verify score is a number, else throw excep?
        if (score < 0) {
            throw score;
        }
    }
    else {
        // Throw exception if score is empty
        throw 0;
    }
    
    // create and return new single node binary tree
    binary_tree tree(name,score);
    return tree;

}