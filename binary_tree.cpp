/*****************************************************************************
 Title:             binary_tree.cpp
 Author:            Anna Cristina Karingal
 Created on:        December 6, 2014
 Description:       Binary Tree Class Implementation
 
 Last Modified:     December 14, 2014
 
 *****************************************************************************/

#include "binary_tree.h"

/******************************************************************************
    Constructors
 ******************************************************************************/
 
/* Constructs an empty tree */
binary_tree::binary_tree() { root = NULL; }

/* Constructs a single node tree from a single string organism containing the
name and score of a single organism separated by whitespace. 
    Creates a stringstream from organism and splits string into name and score.
Verifies both name and score are non-empty and that score is a positive decimal
number. Else, throws exceptions. Creates and allocates space for a new tree_node
containing name and score and sets the new tree's root pointer to point to this
new tree_node.
*/
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

/* Takes a non-empty list of single node binary trees. Finds the two trees, t1
and t2 whose roots have scores that are the closest together from all the trees
in the list. Removes these trees, combines them together into a tree whose root
node contains the average of their two scores and a combined name consisting of
the first 3 letters of each tree's roots name. This new tree also contains a 
copy of t1 and t2 as its left and right subtrees. The new tree is appended to
the input list of binary trees. 
    Function keeps combining the two closest trees in the list until the list
only contains one tree. This tree is a representation of the closeness and
relationships between all the original single node trees. Space for a new copy 
of this tree is allocated and the root of our tree is set to point to the root
of this new tree.
*/
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


/* A protectd constructor that creates a new tree with combined values of the
root nodes of the two input trees as its root node. The root score is an
average of the scores of the roots of the two trees and the root name is created
by concatening the first three letters of t1 with the first three letters of t2.
A copy of the input trees are attached to the new tree as its left & right
subtrees */
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

/* A copy constructor function that recursively traverses the tree rooted at
tn_ptr in pre-order. Creates a new copy of each node to create a new tree
identical to the one rooted at tn_ptr in data and structure, but rooted at
new_ptr instead.
*/
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

/* A public wrapper for the copy constructor function */
binary_tree::binary_tree(const binary_tree &tree){
    copy_tree(tree.get_root_ptr(), root);
}

/******************************************************************************
    Destructors
 ******************************************************************************/

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

/******************************************************************************
    Variable/Characteristic Accessors
 ******************************************************************************/

/* Returns a pointer to the tree's root */
tree_node* binary_tree::get_root_ptr() const { return root; }

/* Returns a copy of the root node's score value */
float binary_tree::get_root_score() const { return root->score; }

/* Returns a copy of the root node's name value */
string binary_tree::get_root_name() const { return root->name; }

/* Returns height of the tree rooted at tn_ptr. Recursively obtains the largest
height of each subtree and increments by 1 edge to account for the path from the
node to the subtree */
int binary_tree::height_of_node(tree_node *tn_ptr) const {
    
    // Base case: If both subtrees are NULL, tn_ptr points to a leaf node
    if (tn_ptr->left== NULL && tn_ptr->right == NULL) {
        return 0;
    }
    else {
    // Recursively get the largest of the heights of the node's subtrees and
    // add one for the edge from the node to the subtrees.
        return 1 + max(height_of_node(tn_ptr->left), height_of_node(tn_ptr->right));
    }
}

/******************************************************************************
    Constructor Helper Functions
 ******************************************************************************/

/* Iterates through the list of binary trees, compares the score in the root of
each tree to the scores in the roots of the trees after it in the list. In this
way, the root score of each tree is compared to that of every other tree in the
list by taking the absolute value of the difference between the scores.
    The variable smallest_diff is initially set to 0 as two species can't have
the same score. Two iterators it_tree1 and it_tree2 keep track of the positions
in the list of the trees with the smallest difference.
    As the function iterates through this list and makes comparisons,
smallest_diff is updated, first to the value of the first difference, then
consequently only if the value of the difference between any two trees' roots'
scores is smaller than smallest_diff. The two iterators are also updated to
point to the two trees with the smallest difference.
    When each tree has been compared to every other tree, we have the true
value of smallest_diff and pointers to the two trees in the list whose root's
scores are closest together. Copies are made of these trees and they are removed
from the list. The copies are combined together into one tree using a protected
constructor that creates a new root node using combined data from the two trees
(average score and a combined name concatenating the first 3 letters of the name
of the root of each tree) and attaches the two trees to this new root as its
left and right subtrees. This combined copy is added to the end of the list.
*/
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

        // Set second iterator to position after first iterator
        list <binary_tree>::iterator it2 = it1;
        it2++;

        // Compare to nodes after current node
        // We've already compared nodes before current node to each other
        for (it2; it2!=trees.end(); it2++){
            
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

/******************************************************************************
    Functions to print the tree to console
 ******************************************************************************/

/* A protected function that outputs the contents and structure of the tree as a
single line string. Any trees with height > 0 make recursive calls to the
print_tree function with its left and right subtrees. These recursive calls are
nested within balanced parentheses and the calls with the left and right
subtrees are separated by a comma. The function keeps making recursive calls
until a subtree of height 0 (i.e. a leaf node) which simply prints out the name
stored in the node. This allows the function to return a string that contains
the name of each organism originally inputted into the tree, and shows the
structure of the trees using balanced parentheses.
*/
string binary_tree::print_tree(tree_node *tn_ptr) const throw(invalid_argument) {
    
    // If tree node is not a leaf node, recursively call the print function on
    // its left and right subtrees until reach a leaf node
    if (height_of_node(tn_ptr) > 0){
        return "(" + print_tree(tn_ptr->left) + "," + print_tree(tn_ptr->right) + ")";
    }
    // Single node tree or leaf node: Print name of organism
    else if (height_of_node(tn_ptr) == 0) {
        return tn_ptr->name;
    }
    else {
        throw invalid_argument("Nothing to print");
    }
}
 
/* A friend function that overloads the << operator to print out the names of
 the leaf nodes in the tree using the print_tree() function*/
ostream & operator << (ostream &os, const binary_tree &tree){
    
    os << tree.print_tree(tree.get_root_ptr()) << endl;
    
    return os;
}

