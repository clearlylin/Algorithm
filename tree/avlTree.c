#include "avlTree.h"
#include "common/common.h"
#include "queue/queue.h"

#include <stdlib.h>
#include <assert.h>

#define max(a, b) (a > b ? a : b)

static int updateDiff(AVLNode* node)
{
	if (node) {
		short left = updateDiff(node->left);
		short right = updateDiff(node->right);
		node->diff = left - right;
		return max(left, right) + 1;
	}
	return 0;
}

static AVLNode* checkIsBalance(AVLNode* root)
{
	if (!root)
		return NULL;
	AVLNode* node = checkIsBalance(root->left);
	if (node)
		return node;
	node = checkIsBalance(root->right);
	if (node)
		return node;
	if (abs(root->diff) >= 2)
		return root;
	return NULL;
}

static void rotateLeft(AVLNode* node)
{
	AVLNode* right = node->right;
	right->parent = node->parent;
	node->right = right->left;
	if (right->left)
		node->right->parent = node;
	if (node->parent) {
		if (node->parent->right == node)
			node->parent->right = right;
		else
			node->parent->left = right;
	}
	node->parent = right;
	right->left = node;
}

static void rotateRight(AVLNode* node)
{
	AVLNode* left = node->left;
	left->parent = node->parent;
	node->left = left->right;
	if (left->right)
		left->right->parent = node;
	if (node->parent) {
		if (node->parent->left == node)
			node->parent->left = left;
		else
			node->parent->right = left;
	}
	node->parent = left;
	left->right = node;
}

AVLNode* createAVLNode(int key, void* value)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	assert(node);
	node->diff = 0;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->value = value;
	return node;
}

static void adjustTree(AVLNode** root)
{
	updateDiff(*root);
	AVLNode*  balance = checkIsBalance(*root);
	if (balance) {
		if (balance->diff > 0) {
			if (balance->left->diff > 0)
				rotateRight(balance);
			else {
				rotateLeft(balance->left);
				rotateRight(balance);
			}
		}
		else {
			if (balance->right->diff  > 0) {
				rotateRight(balance->right);
				rotateLeft(balance);
			}
			else
				rotateLeft(balance);
		}
		if (balance == *root)
			*root = balance->parent;
		updateDiff(*root);
	}
}

void insertAVLNode(AVLNode** root, AVLNode* node)
{
	AVLNode *p = *root, *q = *root;
	while (p) {
		q = p;
		if (p->key > node->key)
			p = p->left;
		else
			p = p->right;
	}
	if (!q) {
		*root = node;
		return;
	}
	if (q->key > node->key)
		q->left = node;
	else
		q->right = node;

	node->parent = q;
	adjustTree(root);
}

AVLNode* findAVLNode(AVLNode* root, int key)
{
	while (root) {
		if (root->key == key)
			return root;
		else if (root->key > key)
			root = root->left;
		else
			root = root->right;
	}
	return NULL;
}

void* deleteKey(AVLNode** root, int key)
{
	AVLNode* node = findAVLNode(*root, key);
	if (node) {
		AVLNode* left = NULL;
		if (node->left && node->right) {
			left = node->right;
			while (left->left)
				left = left->left;
			if (left != node->right) {
				left->right = node->right;
				left->right->parent = left;
				left->parent->left = NULL;
			}
			left->parent = node->parent;
			left->left = node->left;
			left->left->parent = left;
		}
		else if (node->left) {
			left = node->left;
			left->parent = node->parent;
		}
		else if (node->right) {
			left = node->right;
			left->parent = node->parent;
		}
		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = left;
			else
				node->parent->right = left;
		}
		if (*root == node)
			*root = left ? left : NULL;
		adjustTree(root);
	}
}

void levelTraversalAVLTree(AVLNode* root, void(*funcPtr)(AVLNode*))
{
	if (NULL == root)
		return;
	Queue* que = initQueue();
	enQueue(que, root);
	AVLNode *p;
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