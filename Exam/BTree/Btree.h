#pragma once
#include<iostream> 

using namespace std;
template <typename T>
class BTree;
template <typename T>
class BTreeNode
{
    T* keys;  // An array of keys 
    int t;      // Minimum degree (defines the range for number of keys) 
    BTreeNode<T>** C; // An array of child pointers 
    int n;     // Current number of keys 
    bool leaf; // Is true when node is leaf. Otherwise false 
public:
    BTreeNode(int t1, bool leaf1) {
        // Copy the given minimum degree and leaf property 
        t = t1;
        leaf = leaf1;

        // Allocate memory for maximum number of possible keys 
        // and child pointers 
        keys = new int[2 * t - 1];
        C = new BTreeNode<T> * [2 * t];

        // Initialize the number of keys as 0 
        n = 0;
    }// Constructor 

    // A function to search a key in the subtree rooted with this node.     
    BTreeNode<T>* search(int k) {
        // Find the first key greater than or equal to k 
        int i = 0;
        while (i < n && k > keys[i])
            i++;

        // If the found key is equal to k, return this node 
        if (keys[i] == k)
            return this;

        // If the key is not found here and this is a leaf node 
        if (leaf == true)
            return NULL;

        // Go to the appropriate child 
        return C[i]->search(k);
    }// returns NULL if k is not present.  
    // Function to traverse all nodes in a subtree rooted with this node 
    void BTreeNode::traverse()
    {
        // There are n keys and n+1 children, traverse through n keys 
        // and first n children 
        int i;
        for (i = 0; i < n; i++)
        {
            // If this is not leaf, then before printing key[i], 
            // traverse the subtree rooted with child C[i]. 
            if (leaf == false)
                C[i]->traverse();
            cout << " " << keys[i];
        }

        // Print the subtree rooted with last child 
        if (leaf == false)
            C[i]->traverse();
    }
    // A utility function to insert a new key in the subtree rooted with 
    // this node. The assumption is, the node must be non-full when this 
    // function is called 
    void insertNonFull(T k);

    // A utility function to split the child y of this node. i is index of y in 
    // child array C[].  The Child y must be full when this function is called 
    void splitChild(int i, BTreeNode<T>* y);
    friend class BTree<T>;
};

template <typename T>
class BTree
{
    BTreeNode<T>* root; // Pointer to root node 
    int t;  // Minimum degree 
public:

    // Constructor (Initializes tree as empty) 
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }
    // function to traverse the tree 
    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    // function to search a key in this tree 
    BTreeNode<T>* search(T k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
    // The main function that inserts a new key in this B-Tree 
    void insert(T k);
};