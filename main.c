#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int contain (int *vet, int size, int node);

int main() {
  
  srand(time(NULL));
  aco();
  return 0;
}

int* aco (int **graph, int size) {

  int i,j,k,ant;
  int alpha = 1;
  int beta = 1;

  int **pheromone   = (int**) malloc (size * sizeof(int*));
  int **visited     = (int**) malloc (size * sizeof(int*));
  int **antposition = visited;
  int **chance      = (int**) malloc (size * sizeof(int*));
  int **solution    = (int**) malloc (size * sizeof(int*));
  int *result       = (int*) malloc (size * sizeof(int));
  
  for (i = 0; i < size; ++i) {
    pheromone[i] = (int*) malloc (size * sizeof(int));
    visited[i]   = (int*) malloc (size * sizeof(int));
    chance[i]    = (int*) malloc (size * sizeof(int));
    solution[i]  = (int*) malloc (size * sizeof(int));
  }

  for (i = 0; i < size; ++i) {
    visited[i][0] = i;
    for (j = 0; j < size; ++j) 
      pheromone[i][j] = 1;
  }

  for (i = 0; i < size; ++i) {
    for (ant = 0; ant < size; ++ant) {
      visited[ant][

      if (!contain(visited[k], 6, i)) {
	chance[k][i] = pheromone[k]
	
  
      
    }
  }
  return result;
}
int contain (int *vet, int size, int node) {
  int i;
  for (i = 0; i < size; ++i) 
    if (vet[i] == node)
      return 1;
  return 0;
}
