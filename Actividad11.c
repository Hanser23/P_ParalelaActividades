#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITER 10
#define CHECKPOINT_FILE "checkpoint_rank"
#define FAIL_ITER 5

void save_checkpoint(int rank, int counter)
{
    char filename[100];
    sprintf(filename, "%s%d.dat", CHECKPOINT_FILE, rank);
    FILE *fp = fopen(filename, "w");
    if (fp)
    {
        fprintf(fp, "%d\n", counter);
        fclose(fp);
    }
}

int load_checkpoint(int rank)
{
    char filename[100];
    sprintf(filename, "%s%d.dat", CHECKPOINT_FILE, rank);
    FILE *fp = fopen(filename, "r");
    int counter = 0;
    if (fp)
    {
        fscanf(fp, "%d", &counter);
        fclose(fp);
    }
    return counter;
}

int main(int argc, char **argv)
{
    int rank, size, counter = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    counter = load_checkpoint(rank);
    printf("Proceso %d inició en counter=%d\n", rank, counter);

    for (int i = counter; i < MAX_ITER; i++)
    {
        counter = i;
        printf("Proceso %d iteración %d\n", rank, counter);
        sleep(1);

        MPI_Barrier(MPI_COMM_WORLD);
        save_checkpoint(rank, counter);

        if (counter == FAIL_ITER && rank == 1)
        {
            printf("Proceso %d simulando fallo en iteración %d\n", rank, counter);
            exit(1);
        }
    }

    printf("Proceso %d finalizó correctamente\n", rank);
    MPI_Finalize();
    return 0;
}