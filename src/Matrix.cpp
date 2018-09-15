/*
 * Matrix.cpp
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#include "Matrix.h"

namespace Matrix{
// matrix-vector multiplication (y = A * x)
void multiply(double a[3][3], const double x[3], double output[3]) {
	int m = 3;
	int n = 3;
	double y[3] = {0,0,0};
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			y[i] += a[i][j] * x[j];
		}
		output[i] = y[i];
	}

}

double determinate(double x0, double y0, double x1, double y1){
	return x0*y1 - x1*y0;
}

}
