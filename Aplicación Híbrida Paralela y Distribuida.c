#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 1024 // Tamaño de las matrices cuadradas

void multiplicar_submatriz(double *A, double *B, double *C, int filas_locales, int n);

int main(int argc, char *argv[])
{
    int rank, size;
    double *A, *B, *C, *subA, *subC;
    int filas_locales;
    double inicio, fin;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    filas_locales = N / size;

    subA = (double *)malloc(filas_locales * N * sizeof(double));
    subC = (double *)calloc(filas_locales * N, sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));

    if (rank == 0)
    {
        A = (double *)malloc(N * N * sizeof(double));
        C = (double *)malloc(N * N * sizeof(double));
        for (int i = 0; i < N * N; i++)
        {
            A[i] = 1.0;
            B[i] = 1.0;
        }
    }

    inicio = MPI_Wtime();

    MPI_Scatter(A, filas_locales * N, MPI_DOUBLE, subA, filas_locales * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    multiplicar_submatriz(subA, B, subC, filas_locales, N);

    MPI_Gather(subC, filas_locales * N, MPI_DOUBLE, C, filas_locales * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    fin = MPI_Wtime();

    if (rank == 0)
    {
        printf("Multiplicación completada.\n");
        printf("Tiempo de ejecución: %f segundos\n", fin - inicio);
        free(A);
        free(C);
    }

    free(subA);
    free(subC);
    free(B);

    MPI_Finalize();
    return 0;
}

void multiplicar_submatriz(double *A, double *B, double *C, int filas_locales, int n)
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < filas_locales; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}
