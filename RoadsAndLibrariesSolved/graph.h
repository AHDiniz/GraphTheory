#ifndef GRAPH_H
#define GRAPH_H

#define alloc(array,n)   calloc(n,sizeof(*array))

unsigned int** allocateMatrix(int n, int m);
void set(unsigned int** mat, int i, int j);
unsigned int get(unsigned int** mat, int i, int j);
void desallocateMatrix(unsigned int** mat, int n);

#endif
