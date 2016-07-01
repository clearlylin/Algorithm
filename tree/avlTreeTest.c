#include "avlTree.h"

#include <stdio.h>
#include <assert.h>

//LL {3,2,1}
//LR {6,2,4}
//LR {30, 10, 50, 5, 15, 11}
//LR {30, 10, 50, 5, 15, 16}

//RR {6,7,8}
//RL {10,15,12}
//RL {30,10,60,40,70,35}
//RL {30,10,60,40,70,45}


//Test {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
//{ 20,10,30,5,11,40,12,13 }
//{ 20,10,30,5,15,40,14,13 }
static int keys[] = { 30, 10, 60, 40, 70, 35 };

void pf(AVLNode* node)
{
	//FILE* file = fopen("result.txt", "a+");
	//assert(file);
	//fprintf(file, "%d(%d) ", node->key, node->diff);
	printf("%d(%d) ", node->key, node->diff);
}
void test()
{
	AVLNode* root = NULL;
	AVLNode* node = createAVLNode(50, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(25, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(70, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(20, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(15, NULL);
	insertAVLNode(&root, node);

	levelTraversalAVLTree(root, pf);
	printf("\n");

	//node = createAVLNode(21, NULL);
	//insertAVLNode(&root, node);

	node = createAVLNode(26, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(71, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(72, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(73, NULL);
	insertAVLNode(&root, node);

	node = createAVLNode(61, NULL);
	insertAVLNode(&root, node);


	levelTraversalAVLTree(root, pf);
	printf("\n");
}