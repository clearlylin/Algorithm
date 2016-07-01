#include "bsTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <assert.h>



BSTree* initTree(int m)
{
	BSTree* bsTree = (BSTree*)malloc(sizeof(BSTree));
	assert(bsTree);
	bsTree->mOrder = m;
	bsTree->root = NULL;
	return bsTree;
}

static void deleteNode(BSNode* node)
{
	if (node) {
		free(node->keys);
		free(node->values);
		int i  = 0;
		for(; i < node->keyNum; ++i)
			deleteNode(node->children[i]);
		free(node->children);
		free(node);
	}
}

void deleteTree(BSTree* tree)
{
	deleteNode(tree->root);
	free(tree);
}

static BSNode* findPosition(BSNode* node, int key)
{
	if (node) {
		if (NULL == node->children[0])
			return node;
		int i = 1;
		for(; i <= node->keyNum; ++i)
			if (node->keys[i] >= key)
				return findPosition(node->children[i-1], key);
		return findPosition(node->children[i-1], key);
	}
	else
		return NULL;
}

static BSNode* _initNode(int m)
{
	++m;
	BSNode* node = (BSNode*)malloc(sizeof(BSNode));
	node->keys = (int*)malloc(sizeof(int)*m);
	node->values = (void**)malloc(sizeof(void*)*m);
	node->children = (BSNode**)malloc(sizeof(BSNode*)*m);
	node->parent = NULL;
	node->keyNum = 0;
	int i;
	for(i = 0; i < m; ++i) {
		node->keys[i] = INT_MIN;
		node->values[i] = NULL;
		node->children[i] = NULL;
	}
	return node;
}

static BSNode* initNode(int m, int key, void* value)
{
	BSNode* node = _initNode(m);
	node->keyNum = 1;
	node->keys[1] = key;
	node->values[1] = value;
	return node;
}

static inline void insertKey(BSNode* p, int key, void* value, BSNode* node)
{
	int i = 0;
	for (i = p->keyNum; i > 0; --i) {
		if (p->keys[i] >= key) {
			p->keys[i+1] = p->keys[i];
			p->values[i+1] = p->values[i];
			p->children[i+1] = p->children[i];
		}
		else
			break;
	}
	p->keys[i+1] = key;
	p->values[i+1] = value;
	p->children[i+1] = node;
	p->keyNum += 1;
}

static void splitNode(BSTree* tree, BSNode* node)
{
	int m = (int)ceil((float)node->keyNum / 2);
	int mKey = node->keys[m];
	void* mValue = node->values[m];
	BSNode* nNode = _initNode(tree->mOrder);
	int j = 0, i = 0;
	for(i = m + 1; i <= node->keyNum; ++i) {
		++j;
		nNode->keys[j] = node->keys[i];
		nNode->values[j] = node->values[i];
		nNode->children[j] = node->children[i];
		if (node->children[i])
			node->children[i]->parent = nNode;
		node->keys[i] = INT_MIN;
		node->values[i] = NULL;
		node->children[i] = NULL;
	}
	nNode->children[0] = node->children[m];
	if (nNode->children[0])
		nNode->children[0]->parent = nNode;
	nNode->keyNum  = j;

	node->keys[m] = INT_MIN;
	node->children[m] = NULL;
	node->values[m] = NULL;
	node->keyNum = m - 1;

	BSNode* p = node->parent;
	if (p) {
		insertKey(p, mKey, mValue, nNode);
		nNode->parent = p;
		if (p->keyNum > tree->mOrder -1)
			splitNode(tree, p);
	}
	else {
		BSNode* nNode2 = initNode(tree->mOrder, mKey, mValue);
		nNode2->children[0] = node;
		nNode2->children[1] = nNode;
		node->parent = nNode2;
		nNode->parent = nNode2;
		tree->root = nNode2;
	}
}

static void _updateNode(BSTree* tree, BSNode* node, int key, void* value)
{
	insertKey(node, key, value, NULL);
	if (node->keyNum  > tree->mOrder - 1 )
		splitNode(tree, node);
}

void insertNode(BSTree* tree, int key, void* value)
{
	BSNode* node = findPosition(tree->root, key);
	if (node) {
		_updateNode(tree, node, key, value);
	}
	else {
		node = initNode(tree->mOrder, key, value);
		tree->root = node;
	}
}

static BSNode* _findNode(BSNode* node, int m, int key)
{
	if (node) {
		int i = 0;
		for(; i < m - 1; ++i) {
			if (key == node->keys[i])
				return node;
			else if (key < node->keys[i])
				return _findNode(node->children[i], m, key);
		}
		return _findNode(node->children[m-1], m, key);
	}
	return NULL;
}

BSNode* findNode(BSTree* tree, int key)
{
	return _findNode(tree->root, tree->mOrder, key);
}

static void _deleteKey(BSNode* node, int key, int m)
{
	int min = (int)ceil((float)m/2) - 1;
	if (node->keyNum - 1 >= min) {
		int i = 2;
		for(; i <= node->keyNum; ++i) {
			node->keys[i-1] = node->keys[i];
			node->values[i-1] = node->values[i];
		}
		node->keyNum -= 1;
	}
	else {
	}
}

void deleteKey(BSTree* tree, int key)
{
	BSNode* node = findNode(tree, key);
	if (node) {
		if (node->children[0]) { //not leaf node
			int i = 1;
			for(; i <= node->keyNum; ++i)
				if (node->keys[i] == key)
					break;
			BSNode* replace = node->children[i];
			while(replace->children[0])
				replace = replace->children[0];
			void* value = node->values[i];
			node->values[i] = replace->values[1];
			node->keys[i] = replace->keys[1];
			replace->keys[1] = key;
			replace->values[1] = value;
			node = replace;
		}
		void* value = node->values[1];
		_deleteKey(node, key, tree->mOrder);
		return value;
	}
	return NULL;
}