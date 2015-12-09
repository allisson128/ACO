#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "path.h"
/* #include "dist.h" */


double dist (double x1, double y1, double x2, double y2) {

  double difx = x1 - x2;
  double dify = y1 - y2;

  double tosqrt = (difx * difx) + (dify * dify);

  return sqrt(tosqrt);
}

double** matrix_maker (double matrix[][2], int size) {

  int i,j;
  double **result = (double **) malloc (sizeof(double *) * size);;
  for (i = 0; i < size; i++) {
    result[i] = (double *) malloc (sizeof(double) * size);
  }
	
  for(i = 0; i < size; i++) {
    for(j = i; j < size; j++) {
      result[j][i] = result[i][j] = dist (matrix[i][0], matrix[i][1], 
					  matrix[j][0], matrix[j][1]);
    }
  }

  return result;
}

/* int main() {

  double** matrix = matrix_maker (dist1, 20);
  int i = 0, j = 0;

  for (i = 0; i < 15; i++) {
    for (j = 0; j < i; j++) {
      printf("%7.2f ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}
*/
