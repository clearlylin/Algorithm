#include "bsTree.h"

#include <stdio.h>

#define  ArrLength(a, b) (sizeof(a)/sizeof(b))

BSNode*  array[100];
int front = 0;
int last = 0;

void traverse(BSNode* node)
{
	array[last] = node;
	last++;
	while(front < last) {
		node = array[front];
		front++;
		if (node) {
			int i = 1;
			printf("(");
			for(; i < node->keyNum; ++i)
				printf("%d,",  node->keys[i]);
			printf("%d) ", node->keys[i]);

			for(i = 0; i <= node->keyNum; ++i) {
				array[last] = node->children[i];
				last++;
			}
		}	
	}

}
int main()
{
	BSTree* tree = initTree(3);
	int b[] = {20,19,18,17,16,15,14,13,12,11,10,21,22,23,24,25,26,27,28,29,30};
	int len = ArrLength(b, int);
	int i = 0;
	for(; i < len; ++i) {
		insertNode(tree, b[i], &b[i]);
		traverse(tree->root);
		printf("\n");
	}
	deleteTree(tree);
	int c = 0;
	scanf("%d", &c);
}