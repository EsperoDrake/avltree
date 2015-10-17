/************************************************
	AVL tree implementation / main file (main.c)
	Author: Kondakov I.A., M3106
	Created: $Date: 8:28 PM, October 5, 2015 UTC$
*************************************************
*///Edited: $Date: 11:11 AM, October 17, 2015 UTC$
#include <stdio.h>
#include "avl.h"


#define OUTPUT_MODE 0
//ifndef OUTPUT_MODE the first input number assumes as mode
typedef enum {
	SORTED_PRINTOUT,
	UNSORTED_PRINTOUT,
	DOT_PRINTOUT
}MODE;

// Sorted printout
void sprintout(node *tree) 
{
	if (tree->left) 
		sprintout(tree->left);

	printf("%d\n", tree->key);

	if (tree->right) 
		sprintout(tree->right);
}

// Unsorted printout
void usprintout(node *tree)
{
	printf("%d\n", tree->key);

	if (tree->left)
		usprintout(tree->left);

	if (tree->right)
		usprintout(tree->right);
}

// Format dot graph utility 
// Using by dotprintout(node *tree)
int bfactor(node*); // bfactor signature
void dotgraph(node *tree)
{
	printf("    %d [shape=record, label=\"{%d|{%d|%d}}\"];\n", tree->key, tree->key, tree->height, bfactor(tree));
	if (tree->left)
	{
		dotgraph(tree->left);
		printf("    %d -> %d [label=\" < \"];\n", tree->key, tree->left->key);
	}
	if (tree->right)
	{
		dotgraph(tree->right);
		printf("    %d -> %d [label=\" > \"];\n", tree->key, tree->right->key);
	}
}

// Dot graph printout
void dotprintout(node *tree)
{
	printf("#Graphviz js implementation: https://mdaines.github.io/viz.js/ \n"
		"/*****************\n"
		"    Output format:\n"
		"        key\n"
		"    height|bfactor\n"
		"*****************/\n\n"
		"digraph G {\n"
		"    graph [ranksep=0.3];\n");
	dotgraph(tree);
	puts("}");
}

// Read keys from stdin and return filled tree
node *makeTree()
{
	int key;
	node *avlTree = NULL;

	while (scanf("%d", &key) != EOF)
		avlTree = insertNode(avlTree, key);	

	return avlTree;
};

// Entry point
int main(int argc, char *argv[])
{
	node *avlTree = NULL;
	MODE mode;
	
	if (argc > 1)			// If input file specified freopen streams
	{
		if (!freopen(argv[argc - 1], "r", stdin) ||
			!freopen("output.txt", "w+", stdout))
			return EXIT_FAILURE;
	}
	
#ifdef OUTPUT_MODE
	mode = OUTPUT_MODE;
#else
	scanf("%d", &mode);	// First line - output mode
#endif
	
	avlTree = makeTree();	// Make tree from file

	switch (mode)			// Printout
	{
	case SORTED_PRINTOUT:
		sprintout(avlTree); break;
	case UNSORTED_PRINTOUT:
		usprintout(avlTree); break;
	case DOT_PRINTOUT:
		dotprintout(avlTree); break;
	default:
		return EXIT_FAILURE;
	}
	
	return 0;
}