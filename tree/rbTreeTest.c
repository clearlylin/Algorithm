#include "rbTree.h"

#include <stdio.h>

RBNode* queue[100];
int front = 0, last = 0;

void levelTraversal(RBTree* tree)
{
	queue[last++] = tree->root;
	while(front != last) {
		RBNode* node = queue[front++];
		if (node != tree->nil) {
			queue[last++] = node->left;
			queue[last++] = node->right;
			printf("%d", node->key);
			if (node->color == BLACK)
				printf("(B) ");
			else
				printf("(R) ");
		}
	}
}
int main(int argc, char const *argv[])
{
	RBTree* tree = initTree();
	int arr[] = {10,9,8,7,21,23,44,45,29,4,5};
	int len = sizeof(arr)/sizeof(int);
	int i;
	for (i = 0; i < len; ++i)
		insertKey(tree, arr[i], &arr[i]);

	levelTraversal(tree);
	printf("\n");
	return 0;
}