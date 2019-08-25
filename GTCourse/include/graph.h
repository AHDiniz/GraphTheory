#ifndef GRAPH_H_

#define GRAPH_H_

typedef struct graph* Graph;

Graph CreateGraph(int numV);

void GraphAddEdge(Graph g, int v, int w);

int *GraphAdjacent(Graph g, int v);

int GraphVertices(Graph g);

int GraphEdges(Graph g);

const char *GraphStr(Graph g);

void DestroyGraph(Graph g);

#endif
