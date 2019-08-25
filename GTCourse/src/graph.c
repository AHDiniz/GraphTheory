#include "graph.h"

#include <stdlib.h>

struct graph
{
	int v, e;
	int *lengths;
	int **adjacencies;
};

Graph CreateGraph(int numV)
{
	Graph g = malloc(sizeof(*g));
	g->v = numV;
	g->e = 0;
	g->adjacencies = malloc(sizeof((*g->adjacencies)) * numV);
	g->lengths = malloc(sizeof((*g->adjacencies)) * numV);
	for (int i = 0; i < numV; i++)
	{
		g->adjacencies[i] = NULL;
		g->lengths[i] = 0;
	}
	return g;
}

void GraphAddEdge(Graph g, int v, int w)
{
	if (g->adjacencies[v] == NULL)
	{
		g->adjacencies[v] = malloc(sizeof(int));
		g->adjacencies[v][0] = w;
	}
	else
	{
		int pos = sizeof(g->adjacencies[v]) / sizeof(int);
		g->adjacencies[v] = realloc(g->adjacencies[v], sizeof(g->adjacencies[v] + sizeof(int)));
		g->adjacencies[pos] = w;
	}
}

int *GraphAdjacent(Graph g, int v)
{
	int length = sizeof(g->adjacencies[v]) / sizeof(int);
	int *adj = malloc(sizeof(int) * (length - 1));
	for (int i = 0; i < length; i++)
		adj[i] = g->adjacencies[v][i];
	return adj;
}

int GraphVertices(Graph g)
{
	return g->v;
}

int GraphEdges(Graph g)
{
	return g->e;
}

void DestroyGraph(Graph g)
{

}
