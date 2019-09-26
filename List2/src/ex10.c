#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
	int top, size;
	int *data;
} Stack;

Stack CreateStack(int size);
void Push(Stack *s, int i);
int Pop(Stack *s);
unsigned char Empty(Stack s);
void DestroyStack(Stack s);

typedef struct graph
{
	unsigned char *adjacencies;
	unsigned long n, m;
	int k;
} Graph;

#define SET(g, i, j) g.adjacencies[i * g.n + j] = 1
#define GET(g, i, j) g.adjacencies[i * g.n + j]

Graph ReadGraph(const char *path);
int ConnectedComponents(Graph g);
int DepthFirstSearch(Graph g, int v, unsigned char *visited);
void DestroyGraph(Graph g);

int main(int argc, char **argv[])
{
	Graph g = ReadGraph(argv[1]);

	printf("%d\n", ConnectedComponents(g));

	return 0;
}

Graph ReadGraph(const char *path)
{
	FILE *f = fopen(path, "r");
	if (!f)
	{
		fprintf(stderr, "ERROR: Could not read the given graph file: %s\n", path);
		exit(EXIT_FAILURE);
	}

	Graph g;

	fscanf(f, "%d %lu %lu\n", &g.k, &g.n, &g.m);

	g.adjacencies = malloc(sizeof(unsigned char) * g.n * g.n);

	for (int i = 0; i < g.n * g.n; i++)
		g.adjacencies[i] = 0;

	for (int i = 0; i < g.m; i++)
	{
		int u, v;
		fscanf(f, "%d %d\n", &u, &v);
		SET(g, u, v);
	}

	return g;
}

int ConnectedComponents(Graph g)
{
	int result = 0;

	unsigned char *visited = malloc(sizeof(unsigned char) * g.n);
	for (int i = 0; i < g.n; i++)
		visited[i] = 0;

	for (int i = 0; i < g.n; i++)
	{
		if (!visited[i])
		{
			int count = DepthFirstSearch(g, i, visited);
			result++;
		}
	}

	free(visited);

	return result;
}

void DestroyGraph(Graph g)
{
	free(g.adjacencies);
}

int DepthFirstSearch(Graph g, int v, unsigned char *visited)
{
	int result = 0;

	Stack s = CreateStack(g.n);

	Push(&s, v);
	visited[v] = 1;

	while (!Empty(s))
	{
		int u = Pop(&s);
		
		if (!visited[u]) visited[u] = 1;

		for (int i = 0; i < g.n; i++)
		{
			if (!visited[i] && GET(g, u, i))
			{
				Push(&s, i);
				result++;
			}
		}
	}

	return result;
}

Stack CreateStack(int size)
{
	Stack s;

	s.size = size;
	s.top = -1;
	s.data = malloc(sizeof(int) * size);

	return s;
}

void Push(Stack *s, int i)
{
	if (s->top + 1 >= s->size)
		return;
	
	s->data[++s->top] = i;
}

int Pop(Stack *s)
{
	if (s->top < 0)
		return -1;
	
	return s->data[s->top--];
}

unsigned char Empty(Stack s)
{
	return s.top < 0;
}

void DestroyStack(Stack s)
{
	free(s.data);
}
