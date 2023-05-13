#pragma once

#include <stdbool.h>

#include "matrix.h"
#include "elasticity.h"
#include "math.h"
#include "lu.h"
#include "design.h"
#include "eigen.h"

double get_k_frequency(FILE* file, double r1, double r2, double e, double l, double meshSizeFactor, int k, bool vis_in_gmsh,
                    double** displacements, int* n_nodes);

//! OUI POUR L'INSTANT ON DÉFINIT QUEL PARAMÈTRE ON CHERCHE MAIS ÇA SERA MODULABLE APRÈS ......
double bin_search_l(double r1, double r2, double e, double maxL, double meshSizeFactor, double tolerence);
