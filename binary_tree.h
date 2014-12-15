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

/******************************************************************************
    Protected Constructors
 ******************************************************************************/
   
    /* binary_tree(binary_tree &tree1, binary_tree &tree2) throw(bad_alloc);
    Creates a new binary_tree from two input trees whose root node contains the
    combined name and the average score of the two trees' root organisms. The
    left and right subrees of the new tree are tree1 and tree2 respectively.
        @param      binary_tree &tree1  [in]
        @param      binary_tree &tree2  [in]
        @pre        tree1 and tree2 are both intialized non-empty binary_trees
                    whose roots each contain the valid string names n1 and n2
                    and valid float scores s1 and s2 of an organism.
        @post       Tree created contains root whose score s = (s1+s2)/2 and 
                    whose name is the first 3 letters of n1 concatenated by the 
                    first 3 letters of n2. tree1 and tree2 are the left and
                    right subtrees of the tree respectively and the data and
                    structure they contain remain unchanged.
   */
    binary_tree (binary_tree &tree1, binary_tree &tree2) throw(bad_alloc);
    
/******************************************************************************
    Protected Helper Functions for Public Constructors and Destructors
 ******************************************************************************/
    
    /* void destroy(tree_node *&tn_ptr);

        @param      tree_node *&tn_ptr;
        @pre 
        @post       
   */
    void destroy(tree_node *&tn_ptr);

    /* void copy_tree(tree_node *tn_ptr, tree_node *&new_ptr) const throw(bad_alloc);

        @param      tree_node *tn_ptr
        @param      tree_node *&new_ptr
        @pre 
        @post       
   */
    void copy_tree(tree_node *tn_ptr, tree_node *&new_ptr) const throw(bad_alloc);

    /* void find_and_combine_closest_trees(list<binary_tree> &trees) throw(invalid_argument, bad_alloc);

        @param      list<binary_tree> &trees
        @pre 
        @post       
   */
    void find_and_combine_closest_trees(list<binary_tree> &trees) throw(invalid_argument, bad_alloc);
    
/******************************************************************************
    Protected Accessors
 ******************************************************************************/
    
    /* tree_node* get_root_ptr() const;
    Returns a pointer to the root of the tree
        @return      tree_node *    pointer to root of tree
        @pre        There exists an initialized tree_node at the root
        @post       Returns a pointer to the root of the tree, if is non-empty.
                    Else returns NULL.
   */
    tree_node* get_root_ptr() const;

    /* float get_root_score() const;
    Returns the genome score of the organism stored at the root of the tree
        @return     float       score of organism stored at root of tree
        @pre        A non-empty, initialized tree_node exists at root pointer
                    that contains a valid organism score s of type float
        @post       Returns s
   */   
    float get_root_score() const;
    
    /* string get_root_name() const;
    Returns the genome score of the organism stored at the root of the tree
        @return     string      name of organism stored at root of tree
        @pre        A non-empty, initialized tree_node exists at root pointer
                    that contains a valid organism name string n
        @post       Returns n
   */
    string get_root_name() const;
    
    /* int height_of_node(tree_node *tn_ptr) const;
    Returns the height of the tree with tn_ptr as its root. 
        @param      tree_node *tn_ptr  root of tree to get height of
        @return     int                height of tree with root at tn_ptr
        @pre        tn_ptr is a non-empty, initialized pointer to an initialized
                    tree node tn, which is the root of an empty or non-empty
                    tree t.
        @post       Returns the height of t.
   */
    int height_of_node(tree_node *tn_ptr) const;

    
/******************************************************************************
    Protected Helper for Printing Tree to Console
 ******************************************************************************/
    
    /* string print_tree(tree_node *tn_ptr) const;
    Prints the binary tree rooted at tn_ptr as a string that depicts the
    relationships between organisms as sets of pairs inside balanced
    parentheses.
        @param      tree_node *tn_ptr   root of tree to convert to string
        @return     string              string that depicts relationships
                                        between all organisms in tree
        @pre        tree t is non-empty tree of at least one node
        @post       Returns a string that depicts the relationships between all
                    organisms inside the tree. If t1 and t2 are left and right
                    subtrees of a node n of height h >= 1, their string
                    representations are s1 and s2 and function prints (s1, s2).
                    n's string representation is then (s1, s2). If h == 0, t1
                    & t2 are single node trees and their string representations
                    are the names of the organisms contained in their root. 
   */
    string print_tree(tree_node *tn_ptr) const throw(invalid_argument);
    
public:   

/******************************************************************************
    Public Constructors and Destructors
 ******************************************************************************/
    
    /* binary_tree();
    Creates a new, empty binary_tree whose root = NULL;
        @pre        None.
        @post       A new binary tree is created with root = NULL.
   */
    binary_tree ();
    
    /* binary_tree(string organism) throw(invalid_argument, bad_alloc);
    Parses a string that contains the name and the score of a single organism
    separated by white space and creates a new single node binary tree where
    the root contains the name and score of the organism.
        @param      string organism         string containing name and genome
                                            score of a single organism
        @pre        organism is a valid, single-line, non-empty string that
                    contains a string name and a positive float score (in that
                    order) separated by an unspecified number of spaces.
        @post       Root of the tree created contains the name and score
                    contained in organism string. Else, throws exception.
   */
    binary_tree (string organism) throw(invalid_argument, bad_alloc);
    
    /* binary_tree (list<binary_tree> &trees) throw(invalid_argument, bad_alloc);
    Takes a list of single node binary trees that each represent a single
    organism, and creates a single binary tree that groups all organisms in the
    list together by the closeness of their genome scores.
        @param      list<binary> &trees     [in/out] list of single node binary
                                            trees, each containing the valid
                                            name and score of a valid organism   
        @pre        trees is an initialized, non-empty, list of unique non-empty, 
                    initialized single node binary trees. Each binary tree in
                    the list contains the valid name and score of a single
                    organism. 
        @post       Tree created, master_tree, represents how close the
                    genome scores of all organism trees in list tress are to
                    each other. Each single node organism tree is a leaf node of
                    master_tree. The root of each subtree in master_tree 
                    contains the average score of its two child nodes and the 
                    combined name made up of the first three letters of its left
                    child concatenated by the first three letters of its right
                    child. The two children of any subtree are those nodes whose
                    scores are the closest to each other of all nodes in 
                    master_tree.
   */
    binary_tree (list<binary_tree> &trees) throw(invalid_argument, bad_alloc);
    
    /* binary_tree (const binary_tree &tree);
    Creates new tree that contains the same data and strucure as input tree
        @param      binary_tree &tree   [in] tree to make a copy of    
        @pre        tree is an intialized binary_tree
        @post       Tree created contains same data and structure of input tree
   */
    binary_tree (const binary_tree &tree);
    
    /* ~binary_tree();
    Destroys tree and deallocates any memory.
        @pre        tree is an intialized, non-empty binary_tree
        @post       Tree data is purged, memory used to store tree is
                    deallocated. There are no memory leaks or dangling pointers.
   */
    ~binary_tree ();
    

/******************************************************************************
    Friend: Overloaded Operator to Print Tree to Console
 ******************************************************************************/

    /* friend ostream &operator << (ostream &os, const binary_tree &tree);
    Overloading operator << to display tree contents and structure to console.
    Exists outside binary_tree class as a friend function.
        @param      ofstream &os        [in/out] stream to write out to
        @param      binary_tree &tree   [in] playlist to display in console
        @return     ofstream &os        [in/out] stream to write out to
        @pre        &os initialized, open, and writes to console. tree is
                    initialized and non-empty.
        @post       prints tree to console as a string on a single line that
                    depicts the relationships between all organisms inside the
                    tree. If t1 and t2 are left and right subtrees of a node n
                    of height h >= 1, their string representations are s1 and s2
                    and function prints (s1, s2). n's string representation is
                    then (s1, s2). If h == 0, t1 & t2 are single node trees and
                    their string representations are the names of the organisms
                    contained in their root. 
     */
    friend ostream &operator << (ostream &os, const binary_tree &tree);
};

#endif