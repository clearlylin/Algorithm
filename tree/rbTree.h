#ifndef _RBTREE_H
#define _RBTREE_H

typedef enum
{
	RED = 1,
	BLACK
} NodeColor;

typedef struct RBNode
{
	int key;
	void* value;
	NodeColor color;
	struct RBNode *parent;
	struct RBNode *left, *right;
} RBNode;

typedef struct RBTree
{
	RBNode *nil;
	RBNode *root;
} RBTree;

RBTree* initTree();

void insertKey(RBTree*, int, void*);

RBNode* findNode(RBTree*, int);

void* deleteKey(RBTree*, int);

#endif