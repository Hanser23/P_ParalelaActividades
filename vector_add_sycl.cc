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

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de procesos

    // El proceso 0 pide el tamaño N
    if (rank == 0)
    {
        printf("Introduce la cantidad de valores por proceso (N): ");
        scanf("%d", &N);
    }

    // Enviar N a todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializar semilla aleatoria diferente por proceso
    srand(time(NULL) + rank);

    // Reservar y generar N valores aleatorios por proceso
    valores = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        valores[i] = rand() % 100; // Valores entre 0 y 99
        suma_local += valores[i];
    }

    // Reducir la suma parcial en el proceso raíz
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calcular y enviar el promedio a todos
    if (rank == 0)
    {
        promedio = (float)suma_total / (N * size);
    }

    MPI_Bcast(&promedio, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Cada proceso imprime el promedio
    printf("Proceso %d recibió el promedio: %.2f\n", rank, promedio);

    // Liberar memoria y finalizar
    free(valores);
    MPI_Finalize();
    return 0;
}
