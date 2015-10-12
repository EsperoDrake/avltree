/************************************************
	AVL tree implementation / source file (avl.c)
	Author: Kondakov I.A., M3106
	Created: $Date: 8:28 PM, October 5, 2015 UTC$
*************************************************
*///Edited: $Date: 10:41 PM, October 6, 2015 UTC$

#include "avl.h"

// Node constructor
node *make_node(int k)
{
	node *item = (node *)malloc(sizeof(node));
	item->left = item->right = NULL;
	item->key = k;
	item->height = 1;

	return item;
}

// Height of the node
// NULL branches have 0 height
unsigned char height(node* p)
{
	return p ? p->height : 0;
}

// Balance factor of the current node
int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

// Recalculate height after rotating
void fixheight(node* p)
{
	p->height = max(height(p->left), height(p->right)) + 1;
}

// Simple right rotate
node *ror(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

// Simple left rotate
node *rol(node* q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

// Balance the node by applying big right/left rotate if necessary + fixing height
node *balance(node* p)
{
	fixheight(p);
	if (bfactor(p) == 2)				// always equil to > 1
	{
		if (bfactor(p->right) < 0)		// ror if right less
			p->right = ror(p->right);	// Right Left Case
		return rol(p);					// 
	}
	if (bfactor(p) == -2)				// always equil to < -1
	{
		if (bfactor(p->left) > 0)		// rol if left less
			p->left = rol(p->left);		// Left Right Case
		return ror(p);					//
	}
	return p;							// no rotate required
}

// Insert node into the tree
node *insertNode(node *p, int k)
{
	if (!p)
		return make_node(k);			// The tree is empty or end just reached

	if (k < p->key)
		p->left = insertNode(p->left, k);
	else if (k > p->key) 				// (!) Repeat is not allowed
		p->right = insertNode(p->right, k);

	return balance(p);					// (!) New root of the tree
}

// Get the node with minimum value (the leftmost leaf)
node *findmin(node *p)
{
	return p->left ? findmin(p->left) : p;
}

// Remove the leftmost leaf
node *removemin(node* p)
{
	if (p->left == NULL)
		return p->right;

	p->left = removemin(p->left);

	return balance(p);
}

// Remove node from the tree
node *removeNode(node* p, int k)
{
	if (p == NULL)
		return p;

	// Choose the subtree to continue
	if (k < p->key)
		p->left = removeNode(p->left, k);
	else if (k > p->key)
		p->right = removeNode(p->right, k);
	// Target node is here
	else
	{
		node *left = p->left, *right = p->right;
		free(p);
		// If node is list - return branch
		if (right == NULL)
			return left;
		if (left == NULL)
			return right;

		// Replace by min value from right branch
		node *tmp = findmin(right);
		tmp->right = removemin(right);
		tmp->left = left;
		return balance(tmp);
	}

	return balance(p);		// (!) New root of the tree
}

// Search key in the tree
node *searchNode(node* p, int k)
{
	if (p == NULL || p->key == k)
		return p;

	return k < p->key ? searchNode(p->left, k) : k > p->key ? searchNode(p->right, k) : NULL;
}