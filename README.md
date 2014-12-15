Organism Heirarchy Tree
=======================

Creates a binary tree from a list of organisms and their "genome scores". This tree depicts how closely the organisms are related to one another.

**Date Created:** December 6, 2014

**Last Modified:** December 14, 2014

Background
----------
Suppose we can associate a unique numeric value to each species in a collection of organisms whose genomes are known. The value can be thought of some type of encoding of the genome. We can form a sort of evolutionary tree based on these genome "scores" that can represent how closely related a species is to another. Our job is to create this tree from a set of input data that includes a species and its genome score.

Input 
-----
A file in which each line contains the name of a species and a positive decimal number as its genome score, separated by some amount of white space. 

For example:
````
ape   11.0
tiger 50.0
lion 55.0
human   9.0
elephant 76.0
monkey 14.0
````

Output 
------
The program outputs a string that is representative of the evolutionary tree it builds. This string can be described recursively as a function of the height of the tree: 

1. A tree of height 1 consisting of a root and a left node containing the string `a` and a right node containing the string `b` is represented by the string `(a,b)`.
2. If T1 and T2 are non-empty trees whose string representations are `s1` and `s2` respectively, then the tree T which has T1 as its left subtree and T2 as its right has the string representation `(s1, s2)`. 

In this way, the name of each organism is printed and the structure of the tree is illustrated by the set of balanced parentheses.

For example, the output of the example data set above would be: 
`(((ape,human),monkey),((tiger,lion),elephant)) `

Build
-----
The program is built from the command line using `g++ -o binary_tree main.cpp binary_tree.cpp tree_node.cpp` in the working directory.

Usage 
----- 
The program is run from the command line using `./binary_tree organisms.txt` where organisms.txt is the input file with the list of species and their genome scores. 

To Do
-----
* Include score of each species in string representation output
* Introduce some sort of ordering to the evolutionary tree
