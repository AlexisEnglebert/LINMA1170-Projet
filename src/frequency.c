#include "frequency.h"

double get_frequency(double r1, double r2, double e, double l, double meshSizeFactor)
{
	double E = 0.7e11;  // Young's modulus for Aluminum
	double nu = 0.3;    // Poisson coefficient
	double rho = 3000;  // Density of Aluminum

    designTuningFork(r1, r2, e, l, meshSizeFactor, NULL);

    Matrix *K, *M;
	size_t* boundary_nodes;
	size_t n_boundary_nodes;
	double * coord;
	assemble_system(&K, &M, &coord, &boundary_nodes, &n_boundary_nodes, E, nu, rho);

	Matrix *K_new;
	Matrix *M_new;
	remove_bnd_lines(K, M, boundary_nodes, n_boundary_nodes, &K_new, &M_new, NULL);

	Matrix *KM_new = allocate_matrix(K_new->m, K_new->n);
	
	mat_inv_blas(K_new);
	mat_mul_blas(K_new,M_new,KM_new);

	printf("finished inversing matrix\n");

	// Power iteration + deflation to find k largest eigenvalues
	Matrix * A = KM_new;
	double * v = malloc(A->m * sizeof(double));
	double lambda, freq;
	
    //! 2 BECAUSE FIRST MODE IS INAUDIBLE !!!!!!!!!!
	for(int l = 0; l < 2; l++) {
		lambda = power_iteration(A, v);
		freq = 1./(2*M_PI*sqrt(lambda));

		//printf("lambda = %.9e, f = %.3lf\n", lambda, freq);

		// Deflate matrix
		for(int i = 0; i < A->m; i++){
			for(int j = 0; j < A->n; j++){
				A->a[i][j] -= lambda * v[i] * v[j];
			}
		}
	}

    free_matrix (K);
	free_matrix (M);
	free_matrix (K_new);
	free_matrix (M_new);
	free_matrix (KM_new);

    free(coord);
    free(v);
	free(boundary_nodes);
    return freq;
}