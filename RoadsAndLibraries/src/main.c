#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long Solve(int n, int costLib, int costRoad, int **cities, bool *discovered);
long DFS(int **cities, int m, int node, int cl, int cr, bool *discovered);

/**
 * Fazer DFS:
 * 
 * Adicionar custo de biblioteca quando iniciar busca em "novo grafo"
 * Adicionar custo de rua toda vez que caminhar pelo grafo e nó não estiver descoberto
*/


int main(int argc, char const *argv[])
{
	int queries;
	int n;
	int m;
	int costLib;
	int costRoad;
	int **cities;

	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen("result.txt", "w+");

	fscanf(in, "%d\n", &queries);

	for (int i = 0; i < queries; i++)
	{
		fscanf(in, "%d %d %d %d\n", &n, &m, &costLib, &costRoad);
		cities = malloc(sizeof(int) * m);
		for (int j = 0; j < m; j++)
		{
			cities[j] = malloc(sizeof(int) * 2);
			fscanf(in, "%d %d\n", &cities[j][0], &cities[j][1]);
		}

		if (costLib < costRoad)
			fprintf(out, "%d\n", n * costLib);
		else
		{
			bool *discovered = malloc(sizeof(bool) * n);
			for (int i = 0; i < n; i++)
				discovered[i] = false;
			fprintf(out, "%ld\n", Solve(m, costLib, costRoad, cities, discovered));
		}

		free(cities);
	}

	// fclose(in);
	// fclose(out);

	return 0;
}

long Solve(int n, int costLib, int costRoad, int **cities, bool *discovered)
{
	int result = 0;

	for (int i = 0; i < n; i++)
	{
		if (!discovered[cities[i][0]])
			result += DFS(cities, n, cities[i][0], costLib, costRoad, discovered);
	}

	return result;
}

long DFS(int **cities, int m, int node, int cl, int cr, bool *discovered)
{
	int result = 0;
	if (!discovered[node])
	{
		discovered[node] = true;
		result = cl;
	}
	for (int i = 0; i < m; i++)
	{
		if (cities[i][0] == node)
		{
			if (!discovered[cities[i][1]])
			{
				discovered[cities[i][1]] = true;
				result += cr + DFS(cities, m, cities[i][1], cl, cr, discovered);
			}
		}
		else if (cities[i][1] == node)
		{
			if (!discovered[cities[i][0]])
			{
				discovered[cities[i][0]] = true;
				result += cr + DFS(cities, m, cities[i][0], cl, cr, discovered);
			}
		}
	}
	return result;
}
