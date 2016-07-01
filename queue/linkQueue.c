
#include "linkQueue.h"

#include <stdlib.h>
#include <assert.h>

LinkQueue* initQueue()
{
	LinkQueue* queue = (LinkQueue*)malloc(sizeof(LinkQueue));
	assert(queue);
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

bool isEmpty(LinkQueue *queue) {
	if (queue->front)
		return false;
	else
		return true;
}

bool enQueue(LinkQueue *queue, void* element)
{
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	node->data = element;
	node->next = NULL;
	if (queue->rear) {
		queue->rear->next = node;
		queue->rear = node;
	}
	else
		queue->rear = node;
	if (queue->front == NULL)
		queue->front = node;
	return true;
}

bool deQueue(LinkQueue *queue, void** element)
{
	if (queue->front == NULL)
		return false;
	LinkNode* node = queue->front;
	*element = node->data;
	queue->front = node->next;
	if (queue->rear == node)
		queue->rear = NULL;
	free(node);
	return  true;
}

int queueSize(LinkQueue* queue)
{
	int size = 0;
	LinkNode *next = queue->front;
	while (next) {
		++size;
		next = next->next;
	}
	return size;
}

void delQueue(LinkQueue* queue)
{
	while (queue->front){
		LinkNode* del = queue->front;
		queue->front = del->next;
		free(del);
	}
	free(queue);
}
