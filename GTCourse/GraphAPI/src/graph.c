#include "graph.h"

#include <stdio.h>
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
		g->lengths[v] = 1;
		g->adjacencies[v][0] = w;
		g->e++;
	}
	else
	{
		int pos = g->lengths[v]++;
		g->adjacencies[v] = realloc(g->adjacencies[v], sizeof(int) * g->lengths[v]);
		g->adjacencies[pos] = w;
		g->e++;
	}
}

int *GraphAdjacents(Graph g, int v)
{
	int length = g->lengths[v];
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

void PrintGraph(Graph g)
{
	for (int i = 0; i < g->v; i++)
	{
		printf("%d: ", i);
		for (int j = 0; j < g->lengths[i]; i++)
		{
			printf("%d ", j);
		}
		printf("\n");
	}
}

void DestroyGraph(Graph g)
{
	for (int i = 0; i < g->v; i++)
	{
		for (int j = 0; j < g->lengths[i]; j++)
			free(g->adjacencies[i][j]);
		free(g->adjacencies[i]);
	}
	free(g->lengths);
	free(g);
}
