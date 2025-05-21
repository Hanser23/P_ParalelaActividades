#include <omp.h>
#include <stdio.h>

int main()
{
    int i;
#pragma omp parallel for
    for (i = 0; i < 10; i++)
    {
        printf("Thread %d ejecuta la iteración %d\n", omp_get_thread_num(), i);
    }
    return 0;
}
