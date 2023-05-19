#pragma once

#include <stdbool.h>

#include "matrix.h"
#include "elasticity.h"
#include "math.h"
#include "lu.h"
#include "design.h"
#include "eigen.h"

double get_k_frequency(FILE* file, char* outGEO, double r1, double r2, double e, double l, double meshSizeFactor, int k, bool vis_in_gmsh,
                    double** displacements, int* n_nodes, double* frequencies, bool use_blas);

double get_k_frequency_MTFS(FILE* file, char* outGEO,double handle_length, double base_prongs_length, double space_between_base_branch,
                             double space_between_second_layer, double second_prongs_length, double meshSizeFactor, int k, bool vis_in_gmsh,
                    double** displacements, int* n_nodes, double* frequencies, bool use_blas);
                    
//! OUI POUR L'INSTANT ON DÉFINIT QUEL PARAMÈTRE ON CHERCHE MAIS ÇA SERA MODULABLE APRÈS ......
double bin_search_l(double r1, double r2, double e, double maxL, double meshSizeFactor, double tolerence, bool use_blas);


//MOCHE MAIS BON ON EST PLUS À CA PRET...
double bin_search_MTFS_first_l(double handle_length, double maxL, double space_between_base_branch,
                             double space_between_second_layer, double second_prongs_length, double meshSizeFactor,
                            double tolerence, bool use_blas);


double bin_search_MTFS_second_l(double handle_length, double base_prongs_length, double space_between_base_branch,
                             double space_between_second_layer, double maxL, double meshSizeFactor,
                            double tolerence, bool use_blas);
