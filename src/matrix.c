#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"
#include "lu.h"

Matrix* copy_matrix(Matrix* mat) {
	Matrix* const copy = allocate_matrix(mat->m, mat->n);

	for (size_t i = 0; i < (size_t) mat->n; i++) {
		memcpy(copy->a[i], mat->a[i], mat->m * sizeof *copy->a[i]);
	}

	return copy;
}

int mat_inv(Matrix* A_inv) {
	Matrix* const A = copy_matrix(A_inv);
	double* const v = calloc(A->m, sizeof *v);

	lu(A);

	for (size_t i = 0; i < A->m; i++) {
		// set v to the ith column of I

		memset(v, 0, A->m * sizeof *v);
		v[i] = 1;

		// solve K(K^-1)_i = I_i <=> LU(K^-1)_i = I_i for (K^-1)_i

		solve(A, v);

		for (size_t j = 0; j < A->m; j++)
			A_inv->a[i][j] = v[j];
	}

	free_matrix(A);
	free(v);

	return 0;
}

int mat_mul(Matrix* A, Matrix* B, Matrix* C) {
	if (A->m != B->n) {
		return -1;
	}

	// start by transposing second matrix so that we don't have to jump around memory so much

	Matrix* const B_T = allocate_matrix(B->n, B->m);

	for (size_t i = 0; i < (size_t) B->m; i++) {
		for (size_t j = 0; j < (size_t) B->n; j++)
			B_T->a[i][j] = B->a[j][i];
	}

	// actually do matrix multiplication

	for (size_t i = 0; i < (size_t) A->n; i++) {
		for (size_t j = 0; j < (size_t) B->m; j++) {
			double acc = 0;

			for (size_t k = 0; k < (size_t) A->n; k++)
				acc += A->a[i][k] * B_T->a[j][k];

			C->a[i][j] = acc;
		}
	}

	free_matrix(B_T);

	return 0;
}


lapack_int mat_inv_blas(Matrix* A)
{
    int ipiv[A->n+1];
    lapack_int ret;

	 printf("test\n");

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
