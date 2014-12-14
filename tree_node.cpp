/*****************************************************************************
 Title:             tree_node.cpp
 Author:            Anna Cristina Karingal
 Created on:        December 6, 2014
 Description:       Tree Node Implementation
 
 Last Modified:     December 14, 2014
 
 *****************************************************************************/

#include "tree_node.h"

/* Creates an empty tree node */
tree_node::tree_node(){
    left = NULL;
    right = NULL;
};

/* Creates a tree node containing containing the name and score for a single
organism and optional pointers to left and right subtrees */
tree_node::tree_node(const string &n, const float &s, tree_node *left_tree, tree_node *right_tree):name(n), score(s), left(left_tree), right(right_tree){
};

/* Properly destroys a tree node */
tree_node::~tree_node() {
    delete left;
    delete right;
};