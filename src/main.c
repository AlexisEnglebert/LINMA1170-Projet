#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmshc.h>

#include <cblas.h>
#include <lapack.h>


#include "matrix.h"
#include "elasticity.h"
#include "math.h"
#include "lu.h"
#include "design.h"
#include "eigen.h"

 #define max(a,b) \
	 ({ __typeof__ (a) _a = (a); \
			 __typeof__ (b) _b = (b); \
		 _a > _b ? _a : _b; })


int main (int argc, char *argv[]) {

	if (argc < 2){
		printf("Usage: \n"
			"./project <k> <out>\n" 
			"---------------------------- \n\n"
			"- k is the number of frequencies to compute. \n "
			"- out is the output file to write the frequencies. \n "
			"\n");
		return -1;
	} 

	// Define physical constants
	double E = 0.7e11;  // Young's modulus for Aluminum
	double nu = 0.3;    // Poisson coefficient
	double rho = 3000;  // Density of Aluminum

	FILE * file = stdout;
	
	if(argc < 2)
	{
		file = fopen(argv[2], "w"); // open file to write frequencies
	}

	// Initialize Gmsh and create geometry
	int ierr;
	gmshInitialize(argc, argv, 0, 0, &ierr);

	designTuningFork(1e-3, 11e-3, 0.099062, 82e-3, 0.2, NULL);
	
	// Number of vibration modes to find
	int k = atoi(argv[1]);

	// Assemble the 2 matrices of the linear elasticity problem: 
	// M is the mass matrix
	// K is the stiffness matrix
	Matrix *K, *M;
	size_t* boundary_nodes;
	size_t n_boundary_nodes;
	double * coord;
	assemble_system(&K, &M, &coord, &boundary_nodes, &n_boundary_nodes, E, nu, rho);

	// Remove lines from matrix that are boundary
	Matrix *K_new;
	Matrix *M_new;
	remove_bnd_lines(K, M, boundary_nodes, n_boundary_nodes, &K_new, &M_new, NULL);

	Matrix *KM_new = allocate_matrix(K_new->m, K_new->n);
	
	mat_inv_blas(K_new);
	mat_mul_blas(K_new,M_new,KM_new);

	printf("finished inversing matrix\n");

	// Power iteration + deflation to find k largest eigenvalues
	Matrix * A = KM_new; // alias for conciseness
	double * v = malloc(A->m * sizeof(double));
	double lambda, freq;
	
	for(int ki = 0; ki < k; ki++) {
		lambda = power_iteration(A, v);
		freq = 1./(2*M_PI*sqrt(lambda));

		fprintf(file, "%.9lf ", freq);
		printf("lambda = %.9e, f = %.3lf\n", lambda, freq);
		// Deflate matrix
		for(int i = 0; i < A->m; i++){
			for(int j = 0; j < A->n; j++){
				A->a[i][j] -= lambda * v[i] * v[j];
			}
		}

		// Put appropriate BC and plot
		/*double * vall = calloc(K->m, sizeof(double));
		int iv = 0, i_bnd = 0; 
		for(int i = 0; i < K->m/2; i++) {
			if(i_bnd < n_boundary_nodes && i == boundary_nodes[i_bnd]) {
				i_bnd++;
				continue;
			}
			vall[2*(i)]   = v[2*iv];
			vall[2*(i)+1] = v[2*iv+1];
			iv++;
		}
		visualize_in_gmsh(vall, K->m/2);*/
	}

	fclose(file);

	//gmshFltkRun(&ierr);

	free_matrix (K);
	free_matrix (M);
	free_matrix (K_new);
	free_matrix (M_new);
	free_matrix (KM_new);
	free(boundary_nodes);

	return 0;
}
