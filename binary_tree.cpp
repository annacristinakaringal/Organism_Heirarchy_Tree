/*****************************************************************************
 Title:             binary_tree.cpp
 Author:            Anna Cristina Karingal
 Created on:        December 6, 2014
 Description:       Binary Tree Class Implementation
 
 Last Modified:     December 14, 2014
 
 *****************************************************************************/

#include "binary_tree.h"

binary_tree::binary_tree() { root = NULL; }

binary_tree::binary_tree(string organism) throw(invalid_argument, bad_alloc) {
    
    istringstream orgss(organism);
    
    // Splits each line into name and score
    string name, score_string;
    getline(orgss, name, ' ');
    getline(orgss, score_string);
    
    // Throw exception if name is empty
    if (name.empty()) {
        string reason = "'" + organism + "' has empty name field";
        throw invalid_argument(reason);
    }
    
    // Verify score is a number
    istringstream scoress(score_string);
    float score;
    scoress >> score;
    if (scoress.fail()) {
        string reason = "'" + organism + "' has invalid score";
        throw invalid_argument(reason);
    }
    
    if (!score_string.empty()) {
        // Verify score is positive, else throw excep
        if (score < 0) {
            string reason = "'" + organism + "' has invalid non-positive score";
            throw invalid_argument(reason);
        }
    }
    else {
        // Throw exception if score is empty
        string reason = "'" + organism + "' has empty score";
        throw invalid_argument(reason);
    }
    
    // Create new single node binary tree
    tree_node *r = new tree_node(name,score);
    
    // If new node allocation failed, throw exception
    if (r == NULL) {
        throw bad_alloc();
    }
    
    root = r;
}

binary_tree::binary_tree (list<binary_tree> &trees) throw (invalid_argument, bad_alloc){
    
    if (trees.empty()){
        // Empty list, throw exception
        throw invalid_argument("Empty list");
    }
    
    // Find closest trees and combine until one tree left in list
    while (trees.size() > 1){
        // Find trees in list with closest scores in root, remove from list.
        // Combines trees and adds combined tree back to list
        find_and_combine_closest_trees(trees);
    }
    
    // One tree in list left, this is is the consolidated tree
    // Allocate space and make a new copy of this tree
    binary_tree *consolidated_tree = new binary_tree(trees.front());
    
    // If allocation failed, throw exception
    if (consolidated_tree == NULL) {
        throw bad_alloc();
    }
    
    // Make this the root of your tree
    root = consolidated_tree->get_root_ptr();

}

/* Creates new tree with given tree node as root and input trees as subtrees */
binary_tree::binary_tree (tree_node *tn_ptr, binary_tree &left_tree, binary_tree &right_tree) {
    
    // root node ptr points to object tn_ptr is pointing to
    root = tn_ptr;
    
    // root node points to left and right trees
    root->left = left_tree.get_root_ptr();
    root->right = right_tree.get_root_ptr();
}


/* Creates new tree with combined values of the root nodes of the two input
 trees as its root node. Attaches input trees as its left & right subtrees */
binary_tree::binary_tree(binary_tree &tree1, binary_tree &tree2)  throw (bad_alloc){
    
    // Create & allocate new root node with combined name and average score of two trees.
    float avg_score = (tree1.get_root_score() + tree2.get_root_score())/2;
    string combined_name = tree1.get_root_name().substr(0,3) + tree2.get_root_name().substr(0,3);
    tree_node *new_root = new tree_node(combined_name, avg_score);
    
    // Make copies of input binary trees
    binary_tree *left = new binary_tree(tree1);
    binary_tree *right = new binary_tree(tree2);
    
    // Check to see if space for new node and/or new trees was allocated
    if (new_root == NULL || left == NULL || right == NULL) {
        throw bad_alloc();
    }
    
    // Constructor sets newly created node as root and copies of input trees as
    // left and right subtrees.
    root = new_root;
    root->left = left->get_root_ptr();
    root->right = right->get_root_ptr();
    
}

/* A protected copy constructor function that traverses the tree in pre-order 
 and creates a new copy of each node */
void binary_tree::copy_tree(tree_node *tn_ptr, tree_node *&new_ptr) const  throw (bad_alloc){

    // A non-empty tree
    if (tn_ptr != NULL){
        
        // Allocate space for a new pointer with new organism data
        new_ptr = new tree_node (tn_ptr->name, tn_ptr->score);
        
        // Check to see if new node was allocated
        if (new_ptr == NULL) {
            throw bad_alloc();
        }
        
        // Recursively copy left and right subtrees
        copy_tree(tn_ptr->left, new_ptr->left);
        copy_tree(tn_ptr->right, new_ptr->right);
    }
    
    // Copy an empty tree
    else {
        new_ptr = NULL;
    }
}

/* A public wrapper copy constructor function */
binary_tree::binary_tree(const binary_tree &tree){
    copy_tree(tree.get_root_ptr(), root);
}

/* A protected destructor function that traverses the tree in post-order and 
 destroys each node */
void binary_tree::destroy(tree_node *&tn_ptr){
    
    // If tree node is not emtpy
   if (tn_ptr != NULL){
        // Recursively destroy left and right subtrees
        destroy (tn_ptr->left);
        destroy (tn_ptr->right);
       
        // Delete root tree node
        delete tn_ptr;
        tn_ptr = NULL;
    }
}

/* A public wrapper destructor function*/
binary_tree::~binary_tree() { destroy(root); }

/* Returns a pointer to the tree's root */
tree_node* binary_tree::get_root_ptr() const { return root; }

/* Returns a copy of the root node's score value */
float binary_tree::get_root_score() const { return root->score; }

/* Returns a copy of the root node's name value */
string binary_tree::get_root_name() const { return root->name; }

/* Returns height of a node in the tree */
int binary_tree::height_of_node(tree_node *tn_ptr) const {
    
    // If both subtrees are NULL, tn_ptr points to a leaf node
    if (tn_ptr->left== NULL && tn_ptr->right == NULL) {
        return 0;
    }
    else {
    // Recursively get the largest of the heights of the node's subtrees and
    // add one for the edge from the node to the subtrees.
        return 1 + max(height_of_node(tn_ptr->left), height_of_node(tn_ptr->right));
    }
}

void binary_tree::find_and_combine_closest_trees(list<binary_tree> &trees) throw(invalid_argument, bad_alloc) {

    if (trees.empty()){
        // Empty list, throw exception
        throw invalid_argument("Empty list");
    }

    // Score difference can't be zero, because this means it's the same species
    // So we set zero as the initial amount as we expect it to change
    float smallest_diff = 0;
    
    // Iterators to keep track where trees with smallest difference are in list
    list<binary_tree>::iterator it_tree1, it_tree2;

    // For each node in the list
    list <binary_tree>::iterator it1;
    for (it1=trees.begin(); it1!=trees.end(); it1++){;

        // Compare to nodes after current node
        // We've already compared nodes before current node to each other
        list <binary_tree>::iterator it2;
        for (it2=next(it1, 1); it2!=trees.end(); it2++){
            
            // Two different organisms have same name. Throw exception.
            if (it1->get_root_name() == it2->get_root_name()) {
                throw invalid_argument ("Multiple organisms with same name. Check input file for duplicates.");
            }
            
            // Absolute difference between current node & comparing node
            float diff = abs(it1->get_root_score() - it2->get_root_score());
            
            // Two different organisms have the same score. Throw exception.
            if (diff == 0) {
                throw invalid_argument ("Multiple organisms with same score. Check input file for duplicates.");
            }

            // If at the beginning of the list: set new value for smallest
            // difference. Update smallest tree iterators.
            if (smallest_diff == 0 && it1 == trees.begin()){
                smallest_diff = diff;
                it_tree1 = it1;
                it_tree2 = it2;
            }
            
            // Found smallest difference so far. Set current difference as
            // smallest difference. Update smallest trees iterators.
            if (diff < smallest_diff) {
                smallest_diff = diff;
                it_tree1 = it1;
                it_tree2 = it2;
            }
            else {
                // Current difference > smallest difference: do nothing
            }

        }

    }
    
    // Copy trees with smallest difference because they will be erased from list
    binary_tree smallest1(*it_tree1);
    binary_tree smallest2(*it_tree2);
    
    // Combine trees with smallest difference into new tree
    binary_tree combined_tree(smallest1, smallest2);
        
    // Remove smallest trees from list
    trees.erase(it_tree1);
    trees.erase(it_tree2);
    
    // Add copy of combined tree to list
    // Will throw bad_alloc if unsuccessful
    trees.push_back(combined_tree);
    
}

/* A protected function that */
string binary_tree::print_tree(tree_node *tn_ptr) const throw (out_of_range){
    
    // If tree node is not a leaf node, recursively call the print function on
    // its left and right subtrees until reach a leaf node
    if (height_of_node(tn_ptr) > 0){
        return "(" + print_tree(tn_ptr->left) + "," + print_tree(tn_ptr->right) + ")";
    }
    // Single node tree or leaf node: Print name of organism
    else if (height_of_node(tn_ptr) == 0) {
        return tn_ptr->name;
    }
    // Invalid height, throw exception
    else {
        throw out_of_range("Invalid tree height");
    }
}

/* A friend function that overloads the << operator to print out the names of
 the leaf nodes in the tree */
ostream & operator << (ostream &os, const binary_tree &tree){
    
    os << tree.print_tree(tree.get_root_ptr()) << endl;
    
    return os;
}

