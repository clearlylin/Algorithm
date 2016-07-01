//M阶B-树
//根节点,关键字[1,m-1],子树[2,m]
//非叶子节点,关键字[ceil(m/2)-1, m-1],子树[ceil(m/2), m]
//P0<=K0<P1<=K1<Pm

#ifndef  _BSTREE_H
#define _BSTREE_H

typedef struct BSNode
{
	int keyNum;
	int* keys;
	void** values;
	struct BSNode* parent;
	struct BSNode** children;
} BSNode;

typedef struct BSTree
{
	int mOrder;
	BSNode* root;
} BSTree;


BSTree* initTree(int m);

void deleteTree(BSTree*);

void insertNode(BSTree*, int key, void* value);

BSNode* findNode(BSTree*, int);

void* deleteKey(BSTree*, int);

#endif