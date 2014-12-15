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
    
    /* tree_node();
    Creates a new, empty tree_node whose left = NULL and right = NULL.
        @pre        None.
        @post       A new tree_node whose left and right pointers = NULL and 
                    whose name and score member variables are empty.
   */
    tree_node();
    
    /* tree_node(const string &n, const float &s, tree_node *left_tree = NULL, tree_node *right_tree = NULL);
    Creates a new tree_node with name n, score s, and whose left and right
    pointers point to left_tree and right_tree respectively (by default, NULL).
        @param      const string &n     [in] name of organism
        @param      const float &s      [in] organism's genome score
        @param      tree_node *left_tree = NULL     [in] node new tree_node is
                                                    to point left to
        @param      tree_node *right_tree = NULL    [in] node new tree_node is
                                                    to point right to
        @pre        &n and &s are non-empty and initialized. left_tree and
                    right_tree are either NULL or non-empty tree_nodes.
        @post       A new tree_node whose name and score variables are n and s
                    respectively and whose left and right pointers point to
                    left_tree and right_tree respectively.
   */
    tree_node(const string &n, const float &s, tree_node *left_tree = NULL, tree_node *right_tree = NULL);
    
    /* ~tree_node();
    Destroys tree_node data and deallocates any memory.
        @pre        tree_node is an intialized, non-empty tree_node
        @post       Tree_node data is purged, memory used to store tree_node is
                    deallocated to ensure no memory leaks or dangling pointers.
    */
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