#include "traversal.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>



void Dijkstra(ALGraph* graph, int src, int* value, int* path)
{
	for (int i = 0; i < graph->vexNum; ++i) {
		value[i] = INT_MAX;
		path[i] = -1;
	}

	VexNode vex = graph->vexNodes[src];
	ArcNode* arc = vex.first;
	value[src] = 0;
	while(arc) {
	    value[arc->vex] = arc->value;
	    arc = arc->next;
	}

	for (int i = 0; i < graph->vexNum; ++i) {
		if (i == src)
			continue;
		vex = graph->vexNodes[i];
		arc = vex.first;
		while(arc) {
			if (value[i] != INT_MAX) {
				int tmp = value[i] + arc->value;
				if (tmp < value[arc->vex]) {
					value[arc->vex] = tmp;
					path[arc->vex] = i;
				}
			}
			arc = arc->next;
		}
	}
}