
#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

#include "common/common.h"

typedef struct LinkNode {
	void* data;
	struct LinkNode* next;
} LinkNode;

typedef struct {
	LinkNode *front, *rear;
} LinkQueue;

LinkQueue* initQueue();
bool isEmpty(LinkQueue *queue);
bool enQueue(LinkQueue *queue, void* element);
bool deQueue(LinkQueue *queue, void** element);
int queueSize(LinkQueue* queue);
void delQueue(LinkQueue* queue);

#endif
