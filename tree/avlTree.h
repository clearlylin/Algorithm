#pragma once

typedef struct AVLNode{
	int key;
	void* value;
	int diff;
	struct AVLNode* left;
	struct AVLNode* right;
	struct AVLNode* parent;
}AVLNode;

AVLNode* createAVLNode(int key, void* value);
void insertAVLNode(AVLNode** root, AVLNode* node);
AVLNode* findAVLNode(AVLNode* root, int key);
void* deleteKey(AVLNode** root, int key);

typedef void(*funcPtr)(AVLNode*);
void levelTraversalAVLTree(AVLNode* root, funcPtr);