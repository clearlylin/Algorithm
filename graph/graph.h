#ifndef GRAPH_H
#define GRAPH_H

//start index is zero.

typedef struct MGraph {
	int vexNum, arcNum;
	int** edge;
	void (*free)(struct MGraph*);
} MGraph;


typedef struct ArcNode {
	int value;
	int vex;
	struct ArcNode *next;
} ArcNode;

typedef struct VexNode {
	int vex;
	ArcNode *first;
} VexNode;

typedef struct ALGraph {
	int vexNum, arcNum;
	VexNode *vexNodes;
	void (*free)(struct ALGraph*);
} ALGraph;


ALGraph* convertALGraph(MGraph*);
MGraph* convertMGraph(ALGraph*);

#endif // GRAPH_H
