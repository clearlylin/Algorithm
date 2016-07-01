#include "binaryTree.h"
#include "queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


TreeNode* createNode(int key, int value)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	assert(node != NULL);
	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void insertNode(TreeNode* root, TreeNode* node)
{
	if (NULL == node || NULL == root)
		return;
	TreeNode *p = root;
	while (root) {
		p = root;
		if (root->key >= node->key)
			root = root->left;
		else 
			root = root->right;
	}
	if (p->key >= node->key)
		p->left = node;
	else
		p->right = node;
}

TreeNode* findMin(TreeNode* root)
{
	if (NULL == root)
		return NULL;
	while (root->left)
		root = root->left;
	return root;
}

TreeNode* findMax(TreeNode* root)
{
	if (NULL == root)
		return NULL;
	while (root->right)
		root = root->right;
	return root;
}

TreeNode* findNode(TreeNode* root, int key)
{
	while (root) {
		if (root->key > key)
			root = root->left;
		else if (root->key < key)
			root = root->right;
		else if (root->key == key)
			return root;
	}
	return NULL;
}

void deleteNode(TreeNode* root, int key)
{
	TreeNode *p, *parent;
	p = root, parent = root;
	while (p) {
		if (p->key > key) {
			parent = p;
			p = p->left;
		}
		else if (p->key < key) {
			parent = p;
			p = p->right;
		}
		else if (p->key == key)
			break;
	}

#define setChild(child)		if (parent->left == p) \
								parent->left = child; \
							else \
								parent->right = child;
	if (p->left && p->right) {
		TreeNode *ss, *ps;
		ps = p->left, ss = p->left;
		while (ss->right) {
			ps = ss;
			ss = ss->right;
		}
		ps->right = NULL;
		ss->left = p->left;
		ss->right = p->right;
		setChild(ss)
	}
	else if (p->left) {
		setChild(p->left)
	}
	else if (p->right) {
		setChild(p->right)
	}
	free(p);
}

void freeTree(TreeNode* node)
{
	if (node) {
		freeTree(node->left);
		freeTree(node->right);
		free(node);
	}
}

void firstTraversal(TreeNode* root, void(*funcPtr)(TreeNode*))
{
	if (root) {
		(*funcPtr)(root);
		firstTraversal(root->left, funcPtr);
		firstTraversal(root->right, funcPtr);
	}
}

void middleTraversal(TreeNode* root, void(*funcPtr)(TreeNode*))
{
	if (root) {
		middleTraversal(root->left, funcPtr);
		(*funcPtr)(root);
		middleTraversal(root->right,funcPtr);
	}
}

void lastTraversal(TreeNode* root, void(*funcPtr)(TreeNode*))
{
	if (root) {
		lastTraversal(root->left, funcPtr);
		lastTraversal(root->right, funcPtr);
		(*funcPtr)(root);
	}
}

void levelTraversal(TreeNode* root, void(*funcPtr)(TreeNode*))
{  
	if (NULL == root)
		return;
	ArrayQueue* que = initQueue();
	enQueue(que, root);
	TreeNode *p;
	while (0 == isEmpty(que)) {
		deQueue(que, &p);
		(*funcPtr)(p);
		if (p->left)
			enQueue(que, p->left);
		if (p->right)
			enQueue(que, p->right);
	}
	delQueue(que);
}