#pragma once

#include "common/common.h"

#define  MAXELEMENTS 100

typedef struct
{
	void* data[MAXELEMENTS];
	int front, rear;
} ArrayQueue;

ArrayQueue* initQueue();
bool isEmpty(ArrayQueue* queue);
bool enQueue(ArrayQueue* queue, void* ele);
bool deQueue(ArrayQueue* queue, void** ele);
int queueSize(ArrayQueue* q);
void delQueue(ArrayQueue* q);
