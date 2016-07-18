#include "graph.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void freeMGraph(MGraph* graph)
{
	free(graph->edge[0]);
	free(graph->edge);
	free(graph);
}


MGraph* create(int vexNum)
{
	MGraph* graph = (MGraph*)malloc(sizeof(MGraph));
	assert(graph);
	graph->edge = (int**)malloc(sizeof(int*) * vexNum);
	assert(graph->edge);
	graph->edge[0] = (int*)malloc(sizeof(int) * vexNum * vexNum);
	for (int i = 1; i < vexNum; ++i) {
		graph->edge[i] = graph->edge[i - 1] + vexNum;
	}
	graph->vexNum = vexNum;
	graph->arcNum = 0;
	for (int i = 0; i < vexNum; ++i) {
		for (int j = 0; j < vexNum; ++j) {
			if (i == j)
				graph->edge[i][j] = 0;
			else {
				int value = rand() % 10;
				if (value)
					++graph->arcNum;
				graph->edge[i][j] = value;
			}
		}
	}
	graph->free = freeMGraph;
	return graph;
}

void printMGraph(MGraph* graph)
{
	for (int i = 0; i < graph->vexNum; ++i) {
		for(int j = 0; j < graph->vexNum; ++j)
			printf("%d ", graph->edge[i][j]);
		printf("\n");
	}
}

void printALGraph(ALGraph* graph)
{
	printf("VexNum:%d, ArcNum:%d\n", graph->vexNum, graph->arcNum);
	for (int i = 0; i < graph->vexNum; ++i) {
		VexNode vex = graph->vexNodes[i];
		ArcNode* arc = vex.first;
		while(arc) {
		    printf("(%d, %d, %d) ", vex.vex, arc->vex, arc->value);
		    arc = arc->next;
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	MGraph* graph = create(20);

	ALGraph* agraph = convertALGraph(graph);
	printALGraph(agraph);


	MGraph* mgraph = convertMGraph(agraph);

	printMGraph(graph);
	printf("\n");
	printMGraph(mgraph);

	graph->free(graph);
	agraph->free(agraph);
	mgraph->free(mgraph);

	return 0;
}