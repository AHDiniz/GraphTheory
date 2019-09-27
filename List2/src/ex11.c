#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
	int begin, end;
	int size, count;
	int *data;
} Queue;

#define NEXT(s, i) i = (i + 1 >= s->size) ? 0 : i + 1;
#define PREV(s, i) i = (i - 1 <= 0) ? s->size - 1 : i - 1;

Queue CreateQueue(int size);
void Add(Queue *s, int i);
int Remove(Queue *s);
unsigned char Empty(Queue s);
void DestroyQueue(Queue s);

typedef struct graph
{
	unsigned char *adjacencies;
	unsigned long n, m;
} Graph;

#define SET(g, i, j) g.adjacencies[i * g.n + j] = 1
#define GET(g, i, j) g.adjacencies[i * g.n + j]

Graph ReadGraph(const char *path);
int BreadthFirstSearch(Graph g, int v, unsigned char *visited);
void DestroyGraph(Graph g);

int main(int argc, char **argv[])
{
	Graph g = ReadGraph(argv[1]);



	DestroyGraph(g);

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

	fscanf(f, "%lu %lu\n", &g.n, &g.m);

	g.adjacencies = malloc(sizeof(unsigned char) * g.n * g.n);

	for (int i = 0; i < g.n * g.n; i++)
		g.adjacencies[i] = 0;

	for (int i = 0; i < g.m; i++)
	{
		int u, v;
		fscanf(f, "%d %d\n", &u, &v);
		SET(g, u, v);
		SET(g, v, u);
	}

	return g;
}

void DestroyGraph(Graph g)
{
	free(g.adjacencies);
}

int BreadthFirstSearch(Graph g, int v, unsigned char *visited)
{
	int result = 0;

	Queue s = CreateQueue(g.n);

	Add(&s, v);
	visited[v] = 1;

	while (!Empty(s))
	{
		int u = Remove(&s);
		
		if (!visited[u]) visited[u] = 1;

		for (int i = 0; i < g.n; i++)
		{
			if (!visited[i] && GET(g, u, i))
			{
				Add(&s, i);
				result++;
			}
		}
	}

	return result;
}

Queue CreateQueue(int size)
{
	Queue s;

	s.size = size;
	s.begin = -1;
	s.end = size;
	s.count = 0;
	s.data = malloc(sizeof(int) * size);

	return s;
}

void Add(Queue *s, int i)
{
	if (s->count + 1 < s->size)
	{
		NEXT(s, s->begin);
		s->count++;
		s->data[s->begin] = i;
	}
}

int Remove(Queue *s)
{
	if (s->count - 1 >= 0)
	{
		int result = s->data[s->end];
		PREV(s, s->end);
		s->count--;
		return result;
	}
	else return -1;
}

unsigned char Empty(Queue s)
{
	return s.count == 0;
}

void DestroyQueue(Queue s)
{
	free(s.data);
}
