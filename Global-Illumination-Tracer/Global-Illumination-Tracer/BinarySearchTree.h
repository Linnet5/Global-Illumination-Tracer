#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root); 
        return *this;
    } //O(1)

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            preorder(root, out, 2);
        }
    }

    //Additional funtcion to print in order.
    void inOrderPrintTree(std::ostream& out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        }
        else {
            inorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root, nullptr);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    } //O(1)

    const Comparable get_parent(const Comparable& i) const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        //Uses contains to find the node for the searched comparable
        Node* result = contains(i,root);
        if(result != nullptr && result->parent != nullptr){
            //Return parent if it exists
            return result->parent->element;
        }
        //Returns default comparable if node or parent node doesn't exist
        return Comparable{};
    } //Complexity of private contains
    
    const std::pair <Comparable, Comparable> find_pred_succ(const Comparable& x) const{     
        return find_pred_succ(x, root);
    }

    Iterator begin(){
        return Iterator(findMin(root),this);
    }

    Iterator end(){
        return Iterator(nullptr,this);
    }

    Iterator find(const Comparable& x) {
        Node* temp = contains(x, root);
        if (temp != nullptr) {
            //Returns the iterator pointing at the node that has the value of comparable x
            return Iterator(temp, this);
        }
        else {
            //Returns nullptr iterator (end of tree)
            return end();
        }
    } //Complexity of O(logn)
    
private:
    Node *root;

    Node* find_successor(Node* t) const{
        auto p = find_pred_succ(t->element, root);
        
        //If we find that find_pred_succ returns the same as the searched node
        //We instead return nullptr. This prevents endless loop in operator++()
        if (p.second != t->element) {
            return contains(p.second, root);
        }
        else return nullptr;
    } //Complexity of find_pred_succ + contains => find_pred_succ larger => O(n)

    Node* find_predecessor(Node* t) const{
        auto p = find_pred_succ(t->element, root);
       
        //-||-//
        if (p.first != t->element) {
            return contains(p.first, root);
        }
        else return nullptr;
    } //Complexity of find_pred_succ + contains => find_pred_succ larger => O(n)

    //Finds the predecessor and successor of a chosen value x
    const std::pair <Comparable, Comparable> find_pred_succ(const Comparable& x, Node* t) const {
       
        Comparable pred = x; 
        Comparable succ = x;

        while (t != nullptr) {
            //We know that current position t is larger than sought for value x
            //Value x should be under the left branch
            if (t->element > x) {
                succ = t->element;
                t = t->left;
            }
            //Same logic but different direction
            else if(t->element < x){
                pred = t->element;
                t = t->right;
            }
            //We know that the closest values for predecessor and successor will exist in children or
            //it has already been found. If children exist, find min and/or max for subtree.
            else if (t->element == x){
                if(t->right != nullptr){
                    succ = findMin(t->right)->element;
                }
                if(t->left != nullptr){
                    pred = findMax(t->left)->element;
                }
                break;
            }
        }
        return (std::make_pair(pred, succ));
    } //Complexity O(n)

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t, Node *parent) {
        if (t == nullptr) {
            t = new Node{x, nullptr, nullptr, parent};
        } else if (x < t->element) {
            t->left = insert(x, t->left, t);
        } else if (t->element < x) {
            t->right = insert(x, t->right,t);
        } else {
            ;  // Duplicate; do nothing
        }
        return t;
    } //Master theorem: O(log(n)) vars b = 1, c = 2, k = 0;

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {
            t->left = remove(x, t->left);
        } else if (t->element < x) {
            t->right = remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {  // Two subtrees
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        } else {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            if(t!= nullptr){
                //Connect the elements underneath the deleted node, back up to the parent
                t->parent = oldNode->parent;     
            }
            delete oldNode;
        }
        return t;
    } //Master theorem: FindMin i called att most once per remove it has complexity O(log(n1)), 
      //remove has vars b = 1, c= 2, k = 0; 
      //Thus it has complexity O(log(n)), we know that n > n1, O(log(n)) because log(n) + log(n1) < log(n) + log(n)   
      
    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node *findMin(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call 
    } //O(logn)

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node *findMax(Node *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    } //O(logn)

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    } //O(logn)

    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }
        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    } //O(n^(log_2(2)) = O(n), b = 2, c = 2, k = 0

    /*
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, std::ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    } // b = 2, c = 2, k = 0 => O(n^(log_2(2)) = O(n)

    /*
    * Private member function to print a subtree rooted at t in sorted order.
    * Pre-order traversal is used.
    */
    void preorder(Node *t, std::ostream &out, int indent) const{
        if (t != nullptr) {
            out << std::setw(indent) << t->element << "\n";
            indent = indent + 2;
            preorder(t->left, out, indent);
            preorder(t->right, out, indent);
        }
    } // b = 2, c = 2, k = 0 => O(n^(log_2(2)) = O(n)

    /**
     * Private member function to clone subtree.
     */
    Node *clone(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            Node* cloneTree = new Node{t->element, clone(t->left), clone(t->right)};

            //We climb the tree new tree upwards (and left to right)
            //For each subtree, we connect children to the parent
            if (cloneTree->left != nullptr)
                cloneTree->left->parent = cloneTree;
            if (cloneTree->right != nullptr)
                cloneTree->right->parent = cloneTree;

            return cloneTree;
        }
    } //O(n)
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"