#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int number;

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
        number = 100;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Proceso %d ha enviado el número %d al proceso 1.\n", rank, number);
    }
    else if (rank == 1)
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d ha recibido el número %d del proceso 0.\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}