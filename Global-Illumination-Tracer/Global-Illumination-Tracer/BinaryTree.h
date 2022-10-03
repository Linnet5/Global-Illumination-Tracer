#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

#include "node.h"

template <typename Ray>
class BinaryTree {
private:
	struct Node;

public:
	BinaryTree() : root{ nullptr } {
	}

	// Destructor for the tree
	~BinaryTree() {
		makeEmpty();
	}

	// Make the tree logically empty.
	void makeEmpty() {
		root = makeEmpty(root);
	}

	// Insert x into the tree; duplicates are ignored.
	void insert(const Ray& x) {
		root = insert(x, root, nullptr);
	}

	Node* findLeaf(){
		return findLeaf(root);
	}

	/** Return total number of existing nodes
	*
	* Used for debug purposes
	*/
	static int get_count_nodes() {
		return Node::count_nodes;
	} //O(1)



	//IMPLEMENT FIND FINAL LEAF

private:
	Node* root;

	/**
	* Private member function to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Return a pointer to the node storing x.
	*/
	Node* insert(const Ray& x, Node* t, Node* parent) {
		if (t == nullptr) {
			t = new Node{ x, nullptr, nullptr, parent };
		}
		else {
			t->left = insert(x, t->left, t);
		}

		return t;
	}

	Node* findLeaf(Node* t ){
		if(t->left != nullptr){
			t = findLeaf(t->left);
		}
		return t;
	}
 //Private member function to make subtree empty.
 
	Node* makeEmpty(Node* t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			//makeEmpty(t->right);
			delete t;
		}
		return nullptr;
	}
};