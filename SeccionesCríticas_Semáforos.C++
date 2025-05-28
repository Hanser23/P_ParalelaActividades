
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_HILOS 5
#define ITERACIONES 1000

int contador = 0;

sem_t semaforo;

void *incrementarContador(void *arg)
{
    for (int i = 0; i < ITERACIONES; i++)
    {
        sem_wait(&semaforo);
        contador++;
        sem_post(&semaforo);
    }
    return NULL;
}

int main()
{
    pthread_t hilos[NUM_HILOS];

    sem_init(&semaforo, 0, 1);

    for (int i = 0; i < NUM_HILOS; i++)
    {
        if (pthread_create(&hilos[i], NULL, incrementarContador, NULL) != 0)
        {
            perror("Error al crear el hilo");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_HILOS; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&semaforo);

    printf("----- RESULTADO FINAL -----\n");
    printf("Nombre: Hanser Luis López Padilla\n");
    printf("Edad: 21 años\n");
    printf("Institución: ITLA (Instituto Tecnológico de Las Américas)\n");
    printf("Cantidad de hilos: %d\n", NUM_HILOS);
    printf("Incrementos por hilo: %d\n", ITERACIONES);
    printf("Valor esperado: %d\n", NUM_HILOS * ITERACIONES);
    printf("Valor final del contador: %d\n", contador);

    if (contador == NUM_HILOS * ITERACIONES)
    {
        printf("✅ Sincronización exitosa. No hubo condiciones de carrera.\n");
    }
    else
    {
        printf("❌ Error de sincronización. Condición de carrera detectada.\n");
    }

    return 0;
}
