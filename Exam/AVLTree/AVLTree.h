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
    void deleteNode(const T& key);
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
