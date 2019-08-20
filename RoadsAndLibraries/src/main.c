#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef NOTHR
#define OUTPUT_PATH "result.txt"
#define INPUT_STREAM in
#else
#define OUTPUT_PATH getenv("OUTPUT_PATH")
#define INPUT_STREAM stdin
#endif

long Solve(int n, int m, int costLib, int costRoad, int **roads, bool *discovered);
long DFS(int n, int m, int city, int costLib, int costRoad, int **roads, bool *discovered);

int main(int argc, char *argv[])
{
	FILE *out = fopen(OUTPUT_PATH, "w+");
	#if NOTHR
	FILE *in = fopen(argv[1], "r");
	#endif

	int queries;
	int n, m;
	int costLib, costRoad;

	int **roads;
	bool *discovered;

	fscanf(INPUT_STREAM, "%d\n", &queries);
	for (int i = 0; i < queries; i++)
	{
		fscanf(INPUT_STREAM, "%d %d %d %d", &n, &m, &costLib, &costRoad);
		if (costLib < costRoad)
			fprintf(out, "%d\n", costLib * n);
		else
		{
			discovered = malloc(sizeof(*discovered) * n);
			for (int j = 0; j < n; j++)
				discovered[j] = false;

			roads = malloc(sizeof(*roads) * m);
			for (int j = 0; j < m; j++)
			{
				roads[j] = malloc(sizeof(*roads[j]) * 2);
				fscanf(INPUT_STREAM, "%d %d", &(roads[j][0]), &(roads[j][1]));
			}

			fprintf(out, "%ld\n", Solve(n, m, costLib, costRoad, roads, discovered));
		}
	}

	return 0;
}

long Solve(int n, int m, int costLib, int costRoad, int **roads, bool *discovered)
{
	int result = 0;

	for (int i = 0; i < m; i++)
	{
		if (!discovered[roads[i][0]])
		{
			result += DFS(n, m, roads[i][0], costLib, costRoad, roads, discovered);
		}
	}

	return result;
}

long DFS(int n, int m, int city, int costLib, int costRoad, int **roads, bool *discovered)
{
	int *stack = malloc(sizeof(*stack) * n);
	for (int i = 0; i < n; i++)
		stack[i] = -1;
	stack[0] = city;
	int top = 0;
	int result = 0;
	while (stack[0] != -1 && top > -1)
	{
		int node = stack[top];
		stack[top] = -1;
		top--;
		if (!discovered[node])
		{
			result += (result == 0) ? costLib : costRoad;
			discovered[node] = true;
			for (int i = 0; i < m; i++)
			{
				if (roads[i][0] == city)
				{
					top++;
					stack[top] = roads[i][1];
				}
				else if (roads[i][1] == city)
				{
					top++;
					stack[top] = roads[i][0];
				}
				
			}
		}
	}
	// free(stack);
	return result;
}
