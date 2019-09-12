#include "graph.h"

#include <stdio.h>

int main()
{
	Graph g = CreateGraph(4);

	GraphAddEdge(g, 1, 2);
	GraphAddEdge(g, 2, 1);
	GraphAddEdge(g, 3, 1);
	GraphAddEdge(g, 2, 3);
	GraphAddEdge(g, 4, 2);
	GraphAddEdge(g, 4, 4);

	PrintGraph(g);

	DestroyGraph(g);
	return 0;
}
