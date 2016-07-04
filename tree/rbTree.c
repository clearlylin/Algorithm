#include "rbTree.h"

#include <assert.h>
#include <stdlib.h>


static inline RBNode* initNode(int key, void* value)
{
	RBNode* node = (RBNode*)malloc(sizeof(RBNode));
	assert(node);
	node->key = key;
	node->value = value;
	node->color = RED;
	return node;
}

inline RBTree* initTree()
{
	RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
	assert(tree);
	RBNode* nil = initNode(0, NULL);
	nil->color = BLACK;
	tree->nil = nil;
	tree->root = nil;
	return tree;
}

static void rotateRight(RBTree* tree, RBNode* node)
{
	RBNode* left = node->left;
	node->left = left->right;
	if (node->left != tree->nil)
		node->left->parent = node;
	left->parent = node->parent;
	if (node->parent == tree->nil)
		tree->root = left;
	else if(node->parent->left == node)
		node->parent->left = left;
	else
		node->parent->right = left;

	left->right = node;
	node->parent = left;
}

static void rotateLeft(RBTree* tree, RBNode* node)
{
	RBNode* right = node->right;
	node->right = right->left;
	if (node->right != tree->nil)
		node->right->parent = node;
	right->parent = node->parent;
	if (node->parent == tree->nil)
		tree->root = right;
	else if (node->parent->left == node)
		node->parent->left = right;
	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}

static void insertFix(RBTree* tree, RBNode* node)
{
	while (node->parent->color == RED) {
		RBNode *p = node->parent;
		if (p->parent->left == p) { //left child tree
			RBNode *uncle = p->parent->right;
			if (uncle->color == RED) {
				p->color = BLACK;
				uncle->color = BLACK;
				p->parent->color = RED;
				node = p->parent;
				continue;
			}
			else if(node == p->right) {
				node = p;
				rotateLeft(tree, node);
				p = node->parent;
			}
			p->color = BLACK;
			p->parent->color = RED;
			rotateRight(tree, p->parent);
		}
		else {
			RBNode* uncle = p->parent->left;
			if (uncle->color == RED) {
				p->color = BLACK;
				uncle->color = BLACK;
				p->parent->color = RED;
				node = p->parent;
				continue;
			}
			else if(node == p->left) {
				node = p;
				rotateRight(tree, node);
				p = node->parent;
			}
			p->color = BLACK;
			p->parent->color = RED;
			rotateLeft(tree, p->parent);
		}
	}
	tree->root->color = BLACK;
}

void insertKey(RBTree* tree, int key, void* value)
{
	if (!tree) return;
	RBNode* node = initNode(key, value);
	node->left = tree->nil;
	node->right = tree->nil;
	node->parent = tree->nil;

	RBNode *p = tree->root, *position = tree->nil;
	while (p != tree->nil) {
		position = p;
		if (p->key > node->key)
			p = p->left;
		else
			p = p->right;
	}
	node->parent = position;
	if (position == tree->nil)
		tree->root = node;
	else if (position->key > node->key)
		position->left = node;
	else
		position->right = node;
	insertFix(tree, node);
}

RBNode* findNode(RBTree* tree, int key)
{
	RBNode *p = tree->root;
	while(p != tree->nil) {
		if (p->key == key)
			return p;
		else if (p->key > key)
			p = p->left;
		else
			p = p->right;
	}
	return NULL;
}

static void transplant(RBTree* tree, RBNode* src, RBNode* dst)
{
	if (src->parent == tree->nil)
		tree->root = dst;
	else if(src->parent->left == src)
		src->parent->left = dst;
	else
		src->parent->right = dst;
	dst->parent = src->parent;
}

static void deleteFix(RBTree* tree, RBNode* node)
{
	while (node != tree->nil && node->color == BLACK) {
		if (node == node->parent->left) {
			RBNode* right = node->parent->right;
			if (right->color == RED) {
				right->color = BLACK;
				node->parent->color = RED;
				rotateLeft(tree, node->parent);
				right = node->parent->right;
			}
			if (right->left->color ==  BLACK && right->right->color == BLACK) {
				right->color = RED;
				node = node->parent;
			}
			else if(right->right->color == BLACK) {
				right->left->color = BLACK;
				right->color = RED;
				rotateRight(tree, right);
				right = node->parent->right;
			}
			right->color = node->parent->color;
			node->parent->color = BLACK;
			right->right->color = BLACK;
			rotateLeft(tree, node->parent);
			node = tree->root;
		}
		else {
			RBNode* left = node->parent->left;
			if (left->color == RED) {
				left->color = BLACK;
				node->parent->color = RED;
				rotateRight(tree, node->parent);
				left = node->parent->left;
			}
		}
	}
	node->color = BLACK;
}

static RBNode* findMin(RBNode* node)
{
	while(node->left)
		node = node->left;
	return node;
}

void* deleteKey(RBTree* tree, int key)
{
	RBNode* node = findNode(tree, key);
	NodeColor color = node->color;
	RBNode* dst = NULL;
	if (node->left == tree->nil) {
		dst = node->right;
		transplant(tree, node, dst);
	}
	else if(node->right == tree->nil) {
		dst = node->left;
		transplant(tree, node, dst);
	}
	else {
		dst = findMin(node->right);
		NodeColor dstColor = dst->color;
		RBNode* right = dst->right;
		if (dst->parent != node) {
			transplant(tree, dst, dst->right);
			dst->right = node->right;
			dst->right->parent = dst;
		}
		transplant(tree, node, dst);
		dst->left = node->left;
		dst->left->parent = dst;
		dst->color = color;
		color = dstColor;
		dst = right;
	}
	free(node);
	if (color == BLACK)
		deleteFix(tree, dst);
}
