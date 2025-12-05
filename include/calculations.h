#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "gsl/gsl_eigen.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_vector.h"
#include <math.h>
#include "misc.h"

#define EIGEN_PRECISION 1e-6 // When do we say a number is an intiger

int calculate_eigen_values(Graph *graph, double *eigen_values_storage);
int calculate_greedy_score(Graph *graph);

#endif