#pragma once 

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmshc.h>
#include <string.h>

int assemble_system(Matrix** K, Matrix** M, double ** coord, size_t** boundary_nodes, size_t* n_boundary_nodes, double E, double nu, double rho);

int visualize_in_gmsh(double* SOL, int n_nodes);
