#include "frequency.h"

double get_k_frequency(FILE* file, double r1, double r2, double e, double l, double meshSizeFactor, int k, bool vis_in_gmsh,
                    double** displacements, int* n_nodes)
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

    if(displacements != NULL){
        *displacements = calloc(sizeof **displacements, (k+1)*K->n);

        for(int p = 0; p < K->n; p++){
            (*displacements)[p] = 0;
        }
    }

    if(n_nodes != NULL){
        *n_nodes = K->n;
    }

	Matrix *K_new;
	Matrix *M_new;
	remove_bnd_lines(K, M, boundary_nodes, n_boundary_nodes, &K_new, &M_new, NULL);

	Matrix *KM_new = allocate_matrix(K_new->m, K_new->n);

    /*****************Méthode 1***********************/
	mat_inv_blas(K_new);
	mat_mul_blas(K_new,M_new,KM_new);
    /***********************************************$*/
    
	// Power iteration + deflation to find k largest eigenvalues
	Matrix * A = KM_new;
	double * v = malloc(A->m * sizeof(double));
	double lambda = 0.0;
    double freq = 0.0;
	
    //! 2 BECAUSE FIRST MODE IS INAUDIBLE !!!!!!!!!!
	for(int l = 0; l < k; l++) {
		lambda = power_iteration(A, v);
		freq = 1./(2*M_PI*sqrt(lambda));

		// Deflate matrix
		for(int i = 0; i < A->m; i++){
			for(int j = 0; j < A->n; j++){
				A->a[i][j] -= lambda * v[i] * v[j];
			}
		}
        
        if(file != NULL)
            fprintf(file, "%.9lf ", freq);

        if(l%2 != 0)
            printf("Audible Frequency %.9f\n", freq);

        if(vis_in_gmsh && displacements != NULL){
            int iv = 0, i_bnd = 0; 
            for(int i = 0; i < K->m/2; i++) {
                if(i_bnd < n_boundary_nodes && i == boundary_nodes[i_bnd]) {
                    i_bnd++;
                    continue;
                }
                (*displacements)[(1+l)*K->n+2*(i)]   = v[2*iv];
                (*displacements)[(1+l)*K->n+2*(i)+1] = v[2*iv+1];
                iv++;
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

double bin_search_l(double r1, double r2, double e, double maxL, double meshSizeFactor, double tolerence){
    double start = 0;
    double end = maxL;
    int n = 0;
    int n_max = (int)1000;
    double target_freq = 740.0;
    //Our target is 740
    double freq = 0.0;
    while(n < n_max){
        double middle = (start + end) / 2.0;
        if(start == end){
            return middle;
        }
        
        printf("start %.8lf end %.8lf middle : %.20lf\n",start, end, middle);

        freq = get_k_frequency(NULL, r1, r2, e, middle, meshSizeFactor,2 ,false, NULL, NULL);

        if(fabs(target_freq - freq) < tolerence){
            return middle;
        }
        
        if(freq < target_freq){
            end = middle;
        }else if(freq > target_freq){
            start = middle;
        }else{
            return middle;
        }
        n++;
    }
    return (start + end) / 2.0;
}