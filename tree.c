/*
 * tree.c
 * ------
 * Implements a binary tree defined by interface tree.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include <assert.h>
struct tree{
	int data;
	struct tree *left, *right, *parent;
};

/*
 * detach: O(1)
 * ------------
 * Detaches a given tree from its parent
 */
void detach(struct tree *tp)
{
	//Left	
	if(tp->parent != NULL && tp->parent->left == tp){
		tp->parent->left = NULL;
	}
	//Right
	else if(tp->parent != NULL && tp->parent->right == tp){
		tp->parent->right = NULL;
	}
	
	return;
}

/*
 * createTree: O(1)
 * ----------------
 * Allocates memory for and initializes a tree 
 * with given data and children. Returns a tree pointer.
 */
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	struct tree *root;
	root = malloc(sizeof(struct tree));
	assert(root != NULL);

	root->data = data;
	root->right = right;
	root->left = left;
	root->parent = NULL;

	//Detach old parents
	if(left != NULL){
		detach(left);
		root->left->parent = root;
	}
	if(right != NULL){
		detach(right);
		root->right->parent = root;
	}

	return root;
}

/*
 * destroyTree: O(n)
 * ----------------
 * Uses a post-order traversal to free all
 * subtree pointers under the given root
 */
void destroyTree(struct tree *root)
{
	if(root->left != NULL)
		destroyTree(root->left);
	if(root->right != NULL)
		destroyTree(root->right);
	
	//No children -> free 
	free(root);

	return;
}

/*
 * getData: O(1)
 * -------------
 * Returns the root's data
 */
int getData(struct tree *root)
{
	return root->data;
}

/*
 * getLeft: O(1)
 * -------------
 * Returns the left child of the given root
 */
struct tree *getLeft(struct tree *root)
{
	return root->left;
}

/*
 * getRight: O(1)
 * -------------
 * Returns the right child of the given root
 */
struct tree *getRight(struct tree *root)
{
	return root->right;
}

/*
 * getParent: O(1)
 * -------------
 * Returns the parent of the given tree
 */
struct tree *getParent(struct tree *root)
{
	return root->parent;
}

/*
 * setLeft: O(1)
 * -------------
 * Updates the left child of the given root
 * with the given new left tree
 */
void setLeft(struct tree *root, struct tree *left)
{
	if(left != NULL)
		detach(left);
	if(root->left != NULL)
		root->left->parent = NULL;
	
	root->left = left;
	left->parent = root;
	
	return;
}

/*
 * setRight: O(1)
 * -------------
 * Updates the right child of the given root
 * with the given new right tree
 */
void setRight(struct tree *root, struct tree *right)
{
	if(right != NULL)
		detach(right);
	if(root->right != NULL)
		root->right->parent = NULL;
	root->right = right;
	right->parent = root;
	
	return;
}
