#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef NOTHR
#define OUTPUT_PATH "result.txt"
#define INPUT_STREAM in
#else
#define OUTPUT_PATH getenv("OUTPUT_PATH")
#define INPUT_STREAM stdin
#endif

typedef struct graph
{
	long n, m;
	bool *visited;
	int **adjacencies;
} Graph;

Graph CreateGraph(int n, int m);
void DestroyGraph(Graph g);

#define GET(graph, i, j) graph.adjacencies[i * (graph.n) + j]
#define SET(graph, i, j, value) graph.adjacencies[i * (graph.n) + j] = value

typedef struct stack
{
	int n, top;
	int *data;
} Stack;

Stack CreateStack(int n);
void DestroyStack(Stack s);
bool Empty(Stack s);
void Push(Stack s, int i);
int Pop(Stack s);

long Solve(long costLib, long costRoad, Graph graph);

int main(int argc, char *argv[])
{
	FILE *out = fopen(OUTPUT_PATH, "w+");
	#if NOTHR
	FILE *in = fopen(argv[1], "r");
	if (!in)
	{
		printf("WTF?!\n");
		return EXIT_FAILURE;
	}
	#endif

	long queries;
	long n, m, costLib, costRoad;

	fscanf(INPUT_STREAM, "%ld\n", &queries);
	for (long i = 0; i < queries; i++)
	{
		fscanf(INPUT_STREAM, "%ld %ld %ld %ld\n", &n, &m, &costLib, &costRoad);
		Graph g = CreateGraph(n, m);
		for (long j = 0; j < m; j++)
		{
			int u, v;
			fscanf(INPUT_STREAM, "%d %d", &u, &v);
			SET(g, u, v, 1);
			SET(g, v, u, 1);
		}
		fprintf(out, "%ld\n", Solve(costLib, costRoad, g));
		DestroyGraph(g);
	}

	return 0;
}

long Solve(long costLib, long costRoad, Graph graph)
{
	if (costLib < costRoad)
		return costLib * graph.n;
	else
	{
		int unvisited = graph.n;
		int target = 0;

		long roads = 0, components = 0;
		long result = 0;

		while (unvisited > 0)
		{
			int prevUnvisited = unvisited;
			Stack s = CreateStack(graph.n);
			Push(s, target);
			while (!Empty(s))
			{
				int v = Pop(s);
				for (int i = 0; i < graph.n; i++)
				{
					if (!graph.visited[i] && (GET(graph, v, i) || GET(graph, i, v)))
					{
						graph.visited[i] = true;
						roads++;
						unvisited--;
						Push(s, i);
					}
				}
			}
			DestroyStack(s);
			if (prevUnvisited > unvisited) components++;
			target++;
			result += roads * costRoad;
			roads = 0;
		}

		return result + costLib * components;
	}
}

Graph CreateGraph(int n, int m)
{
	Graph g;
	g.n = n;
	g.m = m;
	g.visited = malloc(sizeof(bool) * n);
	for (int i = 0; i < n; i++)
		g.visited[i] = false;
	g.adjacencies = malloc(sizeof(int) * n * n);
	for (int i = 0; i < n * n; i++)
		g.adjacencies[i] = 0;
	return g;
}

void DestroyGraph(Graph g)
{
	free(g.adjacencies);
	free(g.visited);
}

Stack CreateStack(int n)
{
	Stack s;
	s.n = n;
	s.top = -1;
	printf("%d\n", n);
	s.data = malloc(sizeof(int) * n);
	return s;
}

void DestroyStack(Stack s)
{
	free(s.data);
}

bool Empty(Stack s)
{
	return s.top == -1;
}

void Push(Stack s, int i)
{
	s.top++;
	s.data[s.top] = i;
}

int Pop(Stack s)
{
	int result = s.data[s.top];
	s.top--;
	return result;
}
