/************************************************
	AVL tree implementation / header file (avl.h)
	Author: Kondakov I.A., M3106
	Created: $Date: 8:28 PM, October 5, 2015 UTC$
*************************************************
*///Edited: $Date: 10:51 PM, October 6, 2015 UTC$

#ifndef AVL_TREE_INCLUDED
#define AVL_TREE_INCLUDED

#include <stdlib.h>


// AVL tree node struct
typedef struct _node
{
	int key;
	unsigned char height;
	struct _node *right, *left;
} node;

// Insert node into the tree
node *insertNode(node*, int);

// Remove node from the tree
node *removeNode(node*, int);

// Search key in the tree
node *searchNode(node*, int);

#endif