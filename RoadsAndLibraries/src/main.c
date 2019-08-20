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

long Solve(long n, long m, long costLib, long costRoad, long **roads, bool *discovered);
long DFS(long n, long m, long city, long **roads, bool *discovered);

int main(int argc, char *argv[])
{
	FILE *out = fopen(OUTPUT_PATH, "w+");
	#if NOTHR
	FILE *in = fopen(argv[1], "r");
	#endif

	long queries;
	long n, m;
	long costLib, costRoad;

	long **roads;
	bool *discovered;

	fscanf(INPUT_STREAM, "%ld\n", &queries);
	for (int i = 0; i < queries; i++)
	{
		fscanf(INPUT_STREAM, "%ld %ld %ld %ld", &n, &m, &costLib, &costRoad);
		if (m == 0 || costLib < costRoad)
			fprintf(out, "%ld\n", costLib * n);
		else
		{
			discovered = malloc(sizeof(*discovered) * n);
			for (int j = 0; j < n; j++)
				discovered[j] = false;

			roads = malloc(sizeof(*roads) * m);
			for (int j = 0; j < m; j++)
			{
				roads[j] = malloc(sizeof(*roads[j]) * 2);
				fscanf(INPUT_STREAM, "%ld %ld", &(roads[j][0]), &(roads[j][1]));
			}
			fprintf(out, "%ld\n", Solve(n, m, costLib, costRoad, roads, discovered));
		}
	}

	return 0;
}

long Solve(long n, long m, long costLib, long costRoad, long **roads, bool *discovered)
{
	long result = 0;
	long connectedComponents = 0;

	for (int i = 0; i < m; i++)
	{
		if (!discovered[roads[i][0] - 1])
		{
			long nodes = DFS(n, m, roads[i][0], roads, discovered);
			result += (nodes - 1) * costRoad;
			connectedComponents++;
		}
	}

	result += connectedComponents * costLib;
	return result;
}

long DFS(long n, long m, long city, long **roads, bool *discovered)
{
	long *stack = malloc(sizeof(*stack) * n);
	for (int i = 0; i < n; i++)
		stack[i] = -1;
	stack[0] = city;
	int top = 0;
	long result = 0;
	while (stack[0] != -1 && top > -1)
	{
		long node = stack[top];
		stack[top] = -1;
		top--;
		if (!discovered[node - 1])
		{
			result++;
			discovered[node - 1] = true;
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
