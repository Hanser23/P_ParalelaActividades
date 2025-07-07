#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, N;
    int *valores = NULL;
    int suma_local = 0, suma_total = 0;
    float promedio;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Introduce la cantidad de valores por proceso (N):  ");
        scanf("%d", &N);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    srand(time(NULL) + rank);

    valores = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        valores[i] = rand() % 100;
        suma_local += valores[i];
    }

    MPI_Reduce(&suma_local, &suma_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        promedio = (float)suma_total / (N * size);
    }

    MPI_Bcast(&promedio, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    printf("Proceso %d recibió el promedio: %.2f\n", rank, promedio);

    free(valores);
    MPI_Finalize();
    return 0;
}
