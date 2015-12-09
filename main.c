#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dist.h"
#include "path.h"


int  contain (int *vet, int size, int node);
double distanceRoute (int *route, int size, double **graph);
void copyroutefrom (int **source, int **goal, int size);
int  sameroutes (int **r1, int **r2, int size);
void printRoute (int *route, int size);
int* aco (double **graph, int size, int alpha, int beta, 
	  double Q, double evaporation, int kmax);

int main() {
  
  double **grafo;
  int     *caminho;

  srand (time(NULL));

  grafo = matrix_maker (M15, 15);
  caminho = aco (grafo, 15, 1, 1, 1, .5, 10);
  printRoute (caminho, 15);
  printf ("\nDistancia = %.2lf\n", distanceRoute (caminho, 15, grafo));

  return 0;
}

int* aco (double **graph, int size, int alpha, int beta, 
	  double Q, double evaporation, int kmax) {

  int i, j, r, ant, shortest, routechanging;
  int sum, acc, stopflag;
  //int kmax = 3;
  //int alpha       = 1;
  //int beta        = 1;
  //double evaporation = 0.5;
  //double Q           = 1;

  int **pheromone   = (int**) malloc (size * sizeof(int*));
  int **deltapher   = (int**) malloc (size * sizeof(int*));
  int **visited     = (int**) malloc (size * sizeof(int*));
  int **antposition = visited;
  int **chance      = (int**) malloc (size * sizeof(int*));
  int **route       = visited;
  int **previousroute = (int**) malloc (size * sizeof(int*));

  double *distancesLk = (double*) malloc (size * sizeof(int ));
  
  for (i = 0; i < size; ++i) {
    pheromone[i] = (int*) malloc (size * sizeof(int));
    deltapher[i] = (int*) malloc (size * sizeof(int));
    visited[i]   = (int*) malloc (size * sizeof(int));
    chance[i]    = (int*) malloc (size * sizeof(int));
    /* route[i]     = (int*) malloc (size * sizeof(int)); */
  }

  for (i = 0; i < size; ++i) {
    route[i][0] = visited[i][0] = i;
    for (j = 0; j < size; ++j) {
      pheromone[i][j] = 1;
      deltapher[i][j] = 0;
      visited[i][j] = -1;
    }
  }

  shortest = 0;
  do {
    for (ant = 0; ant < size; ++ant) {

      visited[ant][0] = ant;

      for (i = 0; i < size - 1; ++i) { //find route
	
	sum = acc = 0;
	for (j = 0; j < size; ++j) 
	  if (!contain(visited[ant], size, j)) 
	    acc += chance[ant][j] = 
	      pow (pheromone[ route[ant][i] ][j], alpha) * 
	      pow (1.0/graph[ route[ant][i] ][j], beta);
      
	for (j = 0; j < size; ++j)
	  if (!contain(visited[ant], size, j)) 
	    sum += chance[ant][j] / acc;

	r = rand () % sum;
	sum = 0;
	for (j = 0; j < size; ++j) 
	  if (!contain (visited[ant], size, j)) {
	    sum += chance[ant][j];
	    if ( sum > r) {
	      visited[ant][i+1] = j;
	      route  [ant][i+1] = j;
	      break;
	    }
	  }
      
      }//for i

      if ( (distancesLk[ant] = distanceRoute (route[ant], size, graph)) 
	   < distancesLk[shortest])
	shortest = ant;
    
    }//for ant

    for (i = 0; i < size; ++i)
      for (j = 0; j < size; ++j)
	deltapher[i][j] = 0;

    for (ant = 0; ant < size; ++ant) 
      for (j = 0; j < size-1; ++j) 
	deltapher[ route[ant][j] ][ route[ant][j+1] ] 
	  = Q / distancesLk[ant];
      
    for (i = 0; i < size; ++i) 
      for (j = 0; j < size; ++j) {
	pheromone[i][j] *= (1.0 - evaporation);
	pheromone[i][j] += deltapher[i][j];
      }

    if (!sameroutes (route, previousroute, size))
      routechanging = 0;

    copyroutefrom (route, previousroute, size);

  }while (routechanging++ < kmax);

  return route[shortest];
}

int contain (int *vet, int size, int node) {
  int i;
  for (i = 0; i < size; ++i) 
    if (vet[i] == node)
      return 1;
  return 0;
}

double distanceRoute (int *route, int size, double **graph) {

  int i;
  double dist = 0;

  for (i = 0; i < size - 1; ++i) 
    dist += graph[route[i]][route[i+1]];
  
  return dist;
}
 
void copyroutefrom (int **source, int **goal, int size) {

  int i,j;
  for (i = 0; i < size; ++i)
    for (j = 0; j < size; ++j)
      goal[i][j] = source[i][j];
}

int sameroutes (int **r1, int **r2, int size) {

  int i,j;
  for (i = 0; i < size; ++i)
    for (j = 0; j < size; ++j)
      if (r1[i][j] != r2[i][j])
	return 0;
  return 1;
}

void printRoute (int *route, int size) {
  
  int i, j;

  printf ("\nRoute:\n");
  for (i = 0; i < size; ++i) 
    printf (" %d", route[i]);
  putchar('\n');
}
