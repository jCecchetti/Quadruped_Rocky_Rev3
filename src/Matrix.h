/*
 * Matrix.h
 *
 *  Created on: Sep 7, 2018
 *      Author: julia
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#pragma once

namespace Matrix{
// matrix-vector multiplication (y = A * x)
void multiply(double a[3][3], const double x[3], double output[3]);

double determinate(double x0, double y0, double x1, double y1);

}
#endif /* MATRIX_H_ */
