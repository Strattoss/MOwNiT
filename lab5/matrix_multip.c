#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_blas.h>

#define START 100
#define STEP 100
#define STOP 701

void naive_multiplication(double **A, double **B, double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                (*C)[i * n + j] += (*A)[i * n + k] * (*B)[k * n + j];
            }
        }
    }
}

void better_multiplication(double **A, double **B, double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                (*C)[i * n + j] += (*A)[i * n + k] * (*B)[k * n + j];
            }
        }
    }
}

int main()
{
    // conversion for gsl
    gsl_matrix_view A_gsl, B_gsl, C_gsl;

    clock_t tm_stmp_1, tm_stmp_2, tm_stmp_3, tm_stmp_4;
    double t1, t2, t3;

    srand(time(NULL));

    // allocate A, B and C matrices
    double *A = (double *)malloc(STOP * STOP * sizeof(double));
    double *B = (double *)malloc(STOP * STOP * sizeof(double));
    double *C = (double *)malloc(STOP * STOP * sizeof(double));

    // fill A and B with random values
    for (int i = 0; i < STOP * STOP; i++)
    {
        A[i] = rand();
        B[i] = rand();
    }

    printf("type,matrix_size,time\n");

    for (size_t n = START; n < STOP; n += STEP)
    {
        A_gsl = gsl_matrix_view_array(A, n, n);
        B_gsl = gsl_matrix_view_array(B, n, n);
        C_gsl = gsl_matrix_view_array(C, n, n);

        for (size_t i = 0; i < 10; i++)
        {
            tm_stmp_1 = clock();
            naive_multiplication(&A, &B, &C, n);

            tm_stmp_2 = clock();
            better_multiplication(&A, &B, &C, n);

            tm_stmp_3 = clock();
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                   1.0, &A_gsl.matrix, &B_gsl.matrix,
                   0.0, &C_gsl.matrix);

            tm_stmp_4 = clock();


            t1 = (double)(tm_stmp_2 - tm_stmp_1) / CLOCKS_PER_SEC;
            t2 = (double)(tm_stmp_3 - tm_stmp_2) / CLOCKS_PER_SEC;
            t3 = (double)(tm_stmp_4 - tm_stmp_3) / CLOCKS_PER_SEC;


            printf("naive,%lld,%f\n", n, t1);
            printf("better,%lld,%f\n", n, t2);
            printf("BLAS,%lld,%f\n", n, t3);
        }
    }


    // free memory
    free(A);
    free(B);
    free(C);

    return 0;
}
