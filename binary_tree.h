/*****************************************************************************
 Title:             binary_tree.h
 Author:            Anna Cristina Karingal
 Created on:        December 6, 2014
 Description:       Binary Tree Class Definition (Header File)

 
 Last Modified:     December 14,, 2014
 
 *****************************************************************************/

#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <cmath>
#include <new>
#include <stdexcept>

#include "tree_node.h"

using namespace std;

class binary_tree {
    
private:
    tree_node *root;
    
protected:
    
    // Protected constructors
    binary_tree (tree_node *tn_ptr, binary_tree &left_tree, binary_tree &right_tree);
    
    binary_tree (binary_tree &tree1, binary_tree &tree2) throw(bad_alloc);
    
    // Helpers for destructors and constructors
    void destroy (tree_node *&tn_ptr);
    
    void copy_tree (tree_node *tn_ptr, tree_node *&new_ptr) const throw(bad_alloc);

    void find_and_combine_closest_trees (list<binary_tree> &trees) throw(invalid_argument, bad_alloc);
    
    // Getters
    tree_node* get_root_ptr () const;
        
    float get_root_score () const;
    
    string get_root_name () const;
    
    int height_of_node (tree_node *tn_ptr) const;

    // Helps overloaded friend function
    string print_tree (tree_node *tn_ptr) const throw (out_of_range);
    
public:
    
    // Creates empty tree
    binary_tree ();
    
    // Parses input data
    binary_tree (string organism) throw(invalid_argument, bad_alloc);
    
    // Consolidates trees from list
    binary_tree (list<binary_tree> &trees) throw(invalid_argument, bad_alloc);
    
    // Copy constructor
    binary_tree (const binary_tree &tree);
    
    // Destructor
    ~binary_tree ();
    
    friend ostream &operator << (ostream &os, const binary_tree &tree);
};

#endif