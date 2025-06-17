#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100000000

int main()
{
    int *array = malloc(N * sizeof(int));
    long long suma = 0;

    for (int i = 0; i < N; i++)
    {
        array[i] = 1;
    }

    int hilos[] = {1, 2, 4, 8, 16};

    printf("Hilos\tTiempo (s)\tSuma\n");

    for (int h = 0; h < 5; h++)
    {
        int num_hilos = hilos[h];
        suma = 0;

        double start = omp_get_wtime();

#pragma omp parallel for num_threads(num_hilos) reduction(+ : suma)
        for (int i = 0; i < N; i++)
        {
            suma += array[i];
        }

        double end = omp_get_wtime();
        printf("%d\t%.6f\t%lld\n", num_hilos, end - start, suma);
    }

    free(array);
    return 0;
}
