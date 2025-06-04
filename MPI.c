#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    const int TAM = 5;
    int datos[TAM];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        if (rank == 0)
        {
            printf("Este programa requiere al menos 2 procesos.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        for (int i = 0; i < TAM; i++)
        {
            datos[i] = i * 10;
        }
        MPI_Send(datos, TAM, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Proceso 0 envió el arreglo: ");
        for (int i = 0; i < TAM; i++)
        {
            printf("%d ", datos[i]);
        }
        printf("\n");
    }
    else if (rank == 1)
    {
        MPI_Recv(datos, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso 1 recibió el arreglo: ");
        for (int i = 0; i < TAM; i++)
        {
            printf("%d ", datos[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}