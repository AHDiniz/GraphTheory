#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

void readFile(const char* filename);
int isolatedGroups(int n, unsigned int** cities);
long int roadsAndLibraries(int n, int c_lib, int c_road, unsigned int** cities);

int main(int argc, char const *argv[]) {
  if (argc > 1){
    readFile(argv[1]);
  } else {
    printf("Please, input the filename on command line as argument!\n");
  }
  return 0;
}

void readFile(const char* filename){
  FILE* inFile = fopen(filename,"r");
  int q, n, m, c_lib, c_road;

  fscanf(inFile,"%d\n",&q); //Get number of queries
  for (int problem = 0; problem < q; problem++) {  //Read the setup data
    fscanf(inFile,"%d %d %d %d\n",&n,&m,&c_lib,&c_road);
    unsigned int** cities = allocateMatrix(n,n);

    for (int edge = 0; edge < m; edge++) { //Mark the possible roads
      int i,j;
      fscanf(inFile,"%d %d\n",&i,&j);
      set(cities,i-1,j-1);
    }

    //Calculate the minimum cost
    long int min_cost = roadsAndLibraries(n,c_lib,c_road,cities);
    printf("%ld\n", min_cost);
    desallocateMatrix(cities,n);
  }
}

long int roadsAndLibraries(int n, int c_lib, int c_road, unsigned int** cities){
  if (c_lib <= c_road) return c_lib*n;

  int clusters = isolatedGroups(n,cities);
  return clusters*c_lib + c_road*(n-clusters);
}

int isolatedGroups(int n, unsigned int** cities){
  int* controller = alloc(controller,n); //mark the visited cities
  int* stack = alloc(stack,n); //keep the next cities to visit
  int stack_size = 0, groups = 0;

  for (int city = 0; city < n; city++) { //Certify all cities were visited
    if (controller[city]) continue; //if the city was visited, ignore it

    groups++; //a unvisited city means a new group/cluster
    stack[stack_size++] = city;
    for (int next_city; stack_size > 0;){
      next_city = stack[--stack_size]; //Pop a city from stack
      for (int neighbor = next_city+1; neighbor < n; neighbor++){ //Find new neighbors
        if (controller[neighbor]) continue; //if the city was visited, ignore it

        if (get(cities,next_city,neighbor)) { //is it a neighbor city?
          stack[stack_size++] = neighbor; //push to stack
        }
      }
      controller[next_city] = 1; //mark the city as visited
    }
  }

  free(controller);
  free(stack);
  return groups;
}
