#include "graph.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


static void freeMGraph(MGraph* graph)
{
	if (graph) {
		free(graph->edge[0]);
		free(graph->edge);
		free(graph);
	}
}

MGraph* convertMGraph(ALGraph* graph)
{
	MGraph* mgraph = (MGraph*)malloc(sizeof(MGraph));
	assert(mgraph);
	if (graph->vexNum) {
		mgraph->edge = (int**)malloc(sizeof(int*) * graph->vexNum);
		mgraph->edge[0] = (int*)malloc(sizeof(int) * graph->vexNum * graph->vexNum);
		assert(mgraph->edge);
		assert(mgraph->edge[0]);
		for (int i = 1; i < graph->vexNum; ++i)
			mgraph->edge[i] = mgraph->edge[i - 1] + graph->vexNum;
		//memset(mgraph->edge[0], 0, sizeof(int) * graph->vexNum * graph->vexNum);
	}
	else {
		mgraph->edge = NULL;
	}
	mgraph->vexNum = graph->vexNum;
	mgraph->arcNum = graph->arcNum;
	for (int i = 0; i < graph->vexNum; ++i) {
		VexNode vex = graph->vexNodes[i];
		ArcNode* arc = vex.first;
		while(arc) {
		    mgraph->edge[vex.vex][arc->vex] =  arc->value;
		    arc = arc->next;
		}
	}
	mgraph->free = freeMGraph;
	return mgraph;
}


static void freeALGraph(ALGraph* graph)
{
	if (graph) {
		for (int i = 0; i < graph->vexNum; ++i) {
			VexNode vex = graph->vexNodes[i];
			ArcNode* arc = vex.first;
			while(arc) {
			    ArcNode* f = arc;
			    arc = arc->next;
			    free(f);
			}
		}
		free(graph->vexNodes);
		free(graph);
	}
}

ALGraph* convertALGraph(MGraph* graph)
{
	ALGraph* agraph = (ALGraph*)malloc(sizeof(ALGraph));
	assert(agraph);
	agraph->vexNum = graph->vexNum;
	agraph->arcNum = graph->arcNum;
	if (agraph->vexNum) {
		agraph->vexNodes = (VexNode*)malloc(sizeof(VexNode) * agraph->vexNum);
		assert(agraph->vexNodes);
	}
	else {
		agraph->vexNodes = NULL;
	}
	for (int i = 0; i < agraph->vexNum; ++i) {
		VexNode* vex = &agraph->vexNodes[i];
		vex->vex = i;
		vex->first = NULL;
		for( int j = 0; j < agraph->vexNum; ++j) {
			if (graph->edge[i][j] > 0) {
				ArcNode* arc = (ArcNode*)malloc(sizeof(ArcNode));
				assert(arc);
				arc->value = graph->edge[i][j];
				arc->vex = j;
				arc->next = vex->first;;
				vex->first = arc;
			}
		}
	}
	agraph->free = freeALGraph;
	return agraph;
}