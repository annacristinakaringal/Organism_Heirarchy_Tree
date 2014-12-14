/*****************************************************************************
 Title:             tree_node.h
 Author:            Anna Cristina Karingal
 Created on:        December 6, 2014
 Description:       Tree Node Class Definition (Header File)
                    - Constructor for empty tree node
                    - Constructor for tree node with organism data for single
                    organism
                    - Destructor
                    - Friend Class: Binary Tree
 
 Last Modified:     December 14, 2014
 
 *****************************************************************************/


#ifndef ___TREE_NODE__
#define ___TREE_NODE__

#include <iostream>
#include <string>

using namespace std;

class tree_node {
    
private:
    
/******************************************************************************
     Private member variables
******************************************************************************/
    
    // Data stored in node
    string name;
    float score;
    
    // Pointers to left and right children of node (if any)
    tree_node *left;
    tree_node *right;

/******************************************************************************
     Private Constructors and Destructors
******************************************************************************/
    
    tree_node();
    
    tree_node(const string &n, const float &s, tree_node *left_tree = NULL, tree_node *right_tree = NULL);
    
    ~tree_node();
    
    
/******************************************************************************
     Friend classes and functions
******************************************************************************/
    
    /* friend class binary_tree;
     Allows binary_tree class to read/write tree node data and left/right
     children. As the tree_node class constructors and destructors are private,
     the binary_tree class is the only class allowed to create/destroy new 
     tree_node objects.
     */
    
    friend class binary_tree;
};

#endif