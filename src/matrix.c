#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"



lapack_int mat_inv_blas(Matrix* A)
{
    int ipiv[A->n+1];
    lapack_int ret;

    ret =  LAPACKE_dgetrf(LAPACK_COL_MAJOR,
						A->n,
						A->n,
						A->data,
						A->n,
						ipiv);

    if (ret !=0)
        return ret;

    ret = LAPACKE_dgetri(LAPACK_COL_MAJOR,
						A->n,
						A->data,
						A->n,
						ipiv);
    return ret;
}

lapack_int mat_lu_blas(Matrix* A, int* ipiv){
    lapack_int ret;

    ret =  LAPACKE_dgetrf(LAPACK_COL_MAJOR,
						A->n,
						A->n,
						A->data,
						A->n,
						ipiv);
	return ret;
}



int mat_mul_blas(Matrix* A, Matrix* B, Matrix* C)
{
	
	int m = A->m;
	int k = A->n; 
	int n = B->n;

	cblas_dgemm(CblasRowMajor, 
			CblasNoTrans, 
			CblasNoTrans,
			m,
			n,
			k,
			1.0f,
			A->data, 
			k,
			B->data,
			n,
			0.0, 
			C->data,
			n );

	return 0;
}

int mat_mul_vector_blas(Matrix* A, double* vector, double* out)
{
	cblas_dgemv(CblasRowMajor,
			CblasNoTrans,
			A->m,
			A->n,
			1.0,
			A->data,
			A->n,
			vector,
			1.0,
			0, //TODO:  see if we need beta for the deflation / eigen value calculation
			out,
			1.0 );
	
	return 0;
}


Matrix *allocate_matrix(int m, int n)
{
    Matrix *mat = malloc(sizeof(Matrix));
    
    if(mat == NULL){
        fprintf(stderr, "Error malloc failed : %s\n", strerror(errno));
        exit(-1);
    }

    mat->m = m;
    mat->n = n;

    mat->data = calloc(n * m, sizeof(*mat->data));
    if(mat->data == NULL){
        fprintf(stderr, "Error calloc failed in allocate_matrix : %s\n",strerror(errno));
    }

    mat->a = malloc(sizeof(*mat->a) * m);

    for (int i = 0; i < m; i++)
    {
        mat->a[i] = &mat->data[i * n];
    }

    return mat;
}

void free_matrix(Matrix * mat) {
		
	free(mat->a);
	free(mat->data);
	free(mat);
}

void print_vector(double * v, int n) {
	for(int i = 0; i < n; i++)
		printf("%.3e ", v[i]);
	printf("\n");
}

void print_matrix(Matrix * A) {
	for(int i = 0; i < A->m; i++)
		print_vector(A->a[i], A->n);
}

int is_symmetric(Matrix * K) {
	int symmetric = 1;
	for(int i = 0; i < K->m; i++)
		for(int j = i+1; j < K->n; j++)
			if(fabs((K->a[i][j] - K->a[j][i]) / K->a[i][j]) > 1e-12) {
				printf("%d %d\n", i, j);
				printf("%lf %lf\n", K->a[i][j], K->a[j][i]);
				symmetric = 0;
			}
	return symmetric;
}

typedef struct {
	int i;		// index
	double x,y;	// coordinates
} Node;

// Comparateur
int cmp(const void * a, const void * b) {
	
	Node * na = (Node *) a;
	Node * nb = (Node *) b;
	if (na->x > nb->x) return 1;
	else return -1;
}

int compute_permutation(int * perm, double * coord, int n_nodes) {

	// for(int i = 0; i < n_nodes; i++) 
	// 	perm[i] = i;

	// qsort_r(perm, n_nodes, sizeof(int), coord, cmp);

	// Create Node structs
	Node * nodes = malloc(n_nodes * sizeof(Node));
	for(int i = 0; i < n_nodes; i++) {
		nodes[i].i = i;
		nodes[i].x = coord[2*i];
		nodes[i].y = coord[2*i+1];
	}

	// Sort nodes
	qsort(nodes, n_nodes, sizeof(Node), cmp);

	// Fetch permutation (we assume perm is allocated)
	for(int i = 0; i < n_nodes; i++)
		perm[i] = nodes[i].i;

	return 0;
}
