#pragma once

#define MAXNODESNUMBER 100


typedef struct TreeNode {
	int key;
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int key, int value);
void insertNode(TreeNode* root, TreeNode* node);
TreeNode* findMin(TreeNode* root);
TreeNode* findMax(TreeNode* root);
TreeNode* findNode(TreeNode* root, int key);
void deleteNode(TreeNode* root, int key);
void freeTree(TreeNode*);

typedef void (*funcPtr)(TreeNode*);

void firstTraversal(TreeNode* root, funcPtr);
void middleTraversal(TreeNode* root, funcPtr);
void lastTraversal(TreeNode* root, funcPtr);
void levelTraversal(TreeNode* root, funcPtr);
