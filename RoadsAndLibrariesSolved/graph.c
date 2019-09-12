// Utiliza memória dinâmica
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

unsigned int** allocateMatrix(int n, int m){
  unsigned int** mat = alloc(mat,n);
  for(int i=0; i<n; i++) {mat[i] = alloc(mat[i],m);}
  return mat;
}

void set(unsigned int** mat, int i, int j){
  mat[i][j] = mat[j][i] = 1;
}

unsigned int get(unsigned int** mat, int i, int j){
  return mat[i][j];
}

void desallocateMatrix(unsigned int** mat, int n){
  for(int i=0; i<n; i++) {free(mat[i]);}
  free(mat);
}
