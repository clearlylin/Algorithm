#ifndef _QUEUE_H
#define _QUEUE_H

#ifdef ARRAYQUEUE
#include "arrayQueue.h"
typedef ArrayQueue Queue;
#else
#include "linkQueue.h"
typedef LinkQueue Queue;
#endif

#endif
