
#include <stdio.h>

#define ARRAYQUEUE
#include "queue.h"

static int arr[] = { 1, 2, 3, 4, 5, 6, 7, 10, 34, 55, 61, 8, 100 };

int main(int argc, char const *argv[])
{
	Queue* queue = initQueue();
	bool empty = isEmpty(queue);
	if (empty)
		printf("queue is empty\n");
	else
		printf("queue is not empty, error\n");
	bool success = enQueue(queue, &arr[0]);
	if (success)
		printf("enQueue success\n");
	else
		printf("enQueue failed, error\n");
	int* ele;
	success = deQueue(queue, &ele);
	if (success)
		printf("%d, deQueue success", *ele);
	else
		printf("error\n");
	printf("isEmpty: %d\n", isEmpty(queue));
	printf("queueSize: %d\n", queueSize(queue));
	enQueue(queue, &arr[1]);
	enQueue(queue, &arr[2]);
	enQueue(queue, &arr[3]);
	enQueue(queue, &arr[4]);
	enQueue(queue, &arr[5]);
	enQueue(queue, &arr[6]);
	enQueue(queue, &arr[7]);
	enQueue(queue, &arr[8]);
	printf("isEmpty: %d\n", isEmpty(queue));
	printf("queueSize: %d\n", queueSize(queue));
	success = deQueue(queue, &ele);
	if (success)
		printf("%d, deQueue success\n", *ele);
	else
		printf("deQueue error\n");

	int count = 105;
	while (count > 0) {
		if (enQueue(queue, &arr[9]))
			--count;
		else
			break;
	}
	printf("count: %d\n", count);
	printf("queueSize: %d\n", queueSize(queue));
	return 0;
}
