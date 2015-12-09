#include "dist.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist(double x1, double x2, double y1, double y2) {
	double difx = x1 - x2;
	double dify = y1 - y2;

	double tosqrt = (difx * difx) + (dify * dify);

	return sqrt(tosqrt);
}

double** matrix_maker(double matrix[][15], int sizeJ) {
	int i = 0, j = 0;
	double **result;

	result = (double **) malloc(sizeof(double *) * sizeJ);
	for(i = 0; i < sizeJ; i++) {
		result[i] = (double *) malloc(sizeof(double) * sizeJ);
	}
	
	for(i = 0; i < sizeJ; i++) {
		for(j = i; j < sizeJ; j++) {
			result[i][j] = dist(matrix[1][j], matrix[2][j], matrix[1][i], matrix[2][i]);
		}
	}

	return result;
}

int main() {
	double** matrix = matrix_maker(dist1, 20);
	int i = 0, j = 0;

	for(i = 0; i < 15; i++) {
		for(j = 0; j < 15; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}