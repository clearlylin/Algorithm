#include "arrayQueue.h"

#include <stdlib.h>
#include <assert.h>

ArrayQueue* initQueue()
{
	ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
	assert(queue);
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

bool isEmpty(ArrayQueue* queue)
{
	if (NULL == queue || queue->rear == queue->front)
		return true;
	return false;
}

bool enQueue(ArrayQueue* queue, void* ele)
{
	if ((queue->rear + 1) % MAXELEMENTS == queue->front)
		return false;
	queue->data[queue->rear] = ele;
	queue->rear = (queue->rear + 1) % MAXELEMENTS;
	return true;
}

bool deQueue(ArrayQueue* queue, void** ele)
{
	if (queue->rear == queue->front)
		return false;
	*ele = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAXELEMENTS;
	return true;
}

int queueSize(ArrayQueue* q)
{
	return (q->rear - q->front + MAXELEMENTS) % MAXELEMENTS;
}

void delQueue(ArrayQueue* q)
{
	free(q);
}
