#include "avlTree.h"
#include "common.h"
#include "queue.h"

#include <stdlib.h>
#include <assert.h>

//插入新节点后，更新左右子树差值
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

//插入节点后，检测是否不平衡
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

//static void rotateLeft2(AVLNode* node)
//{
//	AVLNode* p = node->parent;
//	node->parent = p->parent;
//	node->parent->left = node;
//	p->right = node->left;
//	if (p->right)
//		p->right->parent = p;
//	node->left = p;
//	p->parent = node;
//}
////不平衡点的孙子旋转
//static void rotateRight2(AVLNode* node)
//{
//	AVLNode* p = node->parent;
//	node->parent = p->parent;
//	node->parent->right = node;
//	p->left = node->right;
//	if (p->left)
//		p->left->parent = p;
//	node->right = p;
//	p->parent = node;
//}

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

void deleteKey(AVLNode* root, int key)
{
	AVLNode* node = findAVLNode(root, key);
	if (node) {
		if (node->left && node->right) {
			AVLNode* left = node->right;
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
			if (node->parent->left == node)
				node->parent->left = left;
			else
				node->parent->right = left;
			free(node);
		}
		else if (node->left) {
			node->left->parent = node->parent;
			if (node->parent->left == node)
				node->parent->left = node->left;
			else
				node->parent->right = node->left;
			free(node);
		}
		else if (node->right) {
			node->right->parent = node->parent;
			if (node->parent->left == node)
				node->parent->left = node->right;
			else
				node->parent->right = node->right;
			free(node);
		}
		else {
			if (node->parent->left == node)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
		}
	}
}

void levelTraversalAVLTree(AVLNode* root, void(*funcPtr)(AVLNode*))
{
	if (NULL == root)
		return;
	ArrayQueue* que = initQueue();
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