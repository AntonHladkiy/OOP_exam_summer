#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template <typename T>
class Node
{
public:
    T key;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int height;
    bool operator ==(Node* other) {
        return key == other->key;
    }
    bool operator !=(Node* other) {
        return key != other->key;
    }
};

template <typename T>
class AVLTreeIterator;
template <typename T>
class AVLTree {
public:
    AVLTree() {
        root = nullptr;
    }
    friend class AVLTreeIterator<T>;
    Node<T>* search(const T& key);
    void insert(const T& key);
    void remove(const T& key);
    void operator =( AVLTree<T> other) {
        root = other.root;
    }
    AVLTreeIterator<T> find(const T& key) ;
    AVLTreeIterator<T> begin() ;
    AVLTreeIterator<T> end() ;
private:
    Node<T>* root;
    int height(Node<T>* N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }
    int getBalance(Node<T>* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }
    Node<T>* newNode(T key)
    {
        Node<T>* node = new Node<T>();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return(node);
    }
    Node<T>* minValueNode(Node<T>* node)
    {
        Node<T>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }
    Node<T>* search(Node<T>* node, const T& key);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* insert(Node<T>* node, const T& key);
    Node<T>* deleteNode(Node<T>* root, const T& key);
    Node<T>* leftRotate(Node<T>* x); 
};


template <typename T>
class AVLTreeIterator {
public:
    AVLTreeIterator(Node<T>* p,
        AVLTree<T> t) {
        nodePtr = p;
        tree = t;
    }
    // comparison operators. just compare node pointers
    bool operator== (const AVLTreeIterator& rhs) const {
        return nodePtr == rhs.nodePtr;
    }

    bool operator!= (const AVLTreeIterator& rhs) const {
        return nodePtr != rhs.nodePtr;
    }

    // dereference operator. return a reference to
    // the value pointed to by nodePtr
    const T& operator* () const {
        return nodePtr->key;
    }

    // preincrement. move forward to next larger value
    AVLTreeIterator& operator++ () {
        Node<T>* p;
        if (nodePtr == nullptr)
        {// ++ from end(). get the root of the tree
            nodePtr = tree.root;

            // error! ++ requested for an empty tree
            if (nodePtr == nullptr)
                throw std::underflow_error("Tree is empty");

            // move to the smallest value in the tree,
            // which is the first node inorder
            while (nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
        }
        else
            if (nodePtr->right != nullptr)
            {
                // successor is the farthest left node of
                // right subtree
                nodePtr = nodePtr->right;

                while (nodePtr->left != nullptr) {
                    nodePtr = nodePtr->left;
                }
            }
            else
            {
                // have already processed the left subtree, and
                // there is no right subtree. move up the tree,
                // looking for a parent for which nodePtr is a left child,
                // stopping if the parent becomes NULL. a non-NULL parent
                // is the successor. if parent is NULL, the original node
                // was the last node inorder, and its successor
                // is the end of the list
                p = nodePtr->parent;
                while (p != nullptr && nodePtr == p->right)
                {
                    nodePtr = p;
                    p = p->parent;
                }

                // if we were previously at the right-most node in
                // the tree, nodePtr = nullptr, and the iterator specifies
                // the end of the list
                nodePtr = p;
            }
        return *this;
    }

private:
    friend class AVLTree<T>;
    Node<T>* nodePtr;
    AVLTree<T> tree;
};

template<typename T>
AVLTreeIterator<T> AVLTree<T>::begin()
{
    return AVLTreeIterator<T>(minValueNode(root), *this);
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::end()
{
    return AVLTreeIterator<T>(nullptr, *this);
}

template<typename T>
AVLTreeIterator<T> AVLTree<T>::find(const T& key)
{
    return AVLTreeIterator<T>(search(key),*this);
}


template <typename T>
Node<T>* AVLTree<T>::rightRotate(Node<T>* y)
{
    Node<T>* x = y->left;
    Node<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    if (T2)
        T2->parent = y;
    if (x)
        x->parent = y->parent;
    if (y)
        y->parent = x;
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;
    return x;
}

template <typename T>
Node<T>* AVLTree<T>::leftRotate(Node<T>* x)
{
    Node<T>* y = x->right;
    Node<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    if (T2)
        T2->parent = x;
    if (y)
        y->parent = x->parent;
    if (x)
        x->parent = y;
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;
    return y;
}
template<typename T>
Node<T>* AVLTree<T>::search(const T& key)
{
    return search(root, key);
}
template<typename T>
void AVLTree<T>::insert(const T& key)
{
    root = insert(root, key);
}
template<typename T>
void AVLTree<T>::remove(const T& key)
{
    root = deleteNode(root, key);
}
template <typename T>
Node<T>* AVLTree<T>::insert(Node<T>* node, const T& key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST  
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then  
    // there are 4 cases  

    // Left Left Case  
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case  
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case  
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case  
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
template<typename T>
Node<T>* AVLTree<T>::search(Node<T>* node, const T& key)
{
    if (node->key == key) return node;
    if (node->key > key) {
        if (node->right) {
            return search(node->right, key);
        }
        else {
            return nullptr;
        }
    }
    else {
        if (node->left) {
            return search(node->left, key);
        }
        else {
            return nullptr;
        }
    }

}



template<typename T>
Node<T>* AVLTree<T>::deleteNode(Node<T>* root, const T& key)
{
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {
        // node with only one child or no child  
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node<T>* temp = root->left ?
                root->left :
                root->right;

            // No child case  
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case  
                *root = *temp; // Copy the contents of  
                               // the non-empty child  
            delete temp;
        }
        else
        {
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node<T>* temp = minValueNode(root->right);

            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;

            // Delete the inorder successor  
            root->right = deleteNode(root->right,
                temp->key);
        }
    }

    // If the tree had only one node 
    // then return  
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),
        height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);

    // If this node becomes unbalanced,  
    // then there are 4 cases  

    // Left Left Case  
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case  
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case  
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case  
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}