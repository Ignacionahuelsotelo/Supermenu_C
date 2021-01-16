#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


sem_t P1;
sem_t terminaP1234;
sem_t P1234;
sem_t P2;
sem_t P3;
sem_t P4;
sem_t P5;
sem_t P6;
sem_t terminaP6;
sem_t P7;



static void * pienso(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
		//Estado Pensando

		sem_wait(&P1234);
		sem_wait(&P1);		
		printf("\n\n%s \n","Pienso");
		sem_post(&P1234);
		sem_post(&P2);
		sem_post(&P3);
		sem_post(&P4);
		sem_post(&P5);
		
		i++;
		
	}
}

static void * lavoPlatos(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P1234);
		sem_wait(&P2);
		printf("%s","Mientras lavo los platos, ");
		sem_post(&terminaP1234);
		sem_post(&P1234);
		
		i++;
	}
}

static void * limpioPisos(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P1234);
		sem_wait(&P3);
		printf("%s","Mientras limpio los pisos, ");
		sem_post(&terminaP1234);
		sem_post(&P1234);

		i++;
	}
}

static void * riegoPlantas(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P1234);
		sem_wait(&P4);
		printf("%s","Mientras riego las plantas, ");
		sem_post(&terminaP1234);
		sem_post(&P1234);

		i++;
	}
}

static void * existo(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P5);
		sem_wait(&terminaP1234);
		sem_wait(&terminaP1234);
		sem_wait(&terminaP1234);
		printf("\n%s\n","Existo!");
		sem_post(&P6);
		sem_post(&P7);
		sem_post(&P5);

		i++;
	}
}

static void * hablar(void *iteracion) {
	int N = *((int *) iteracion);
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P6);
		printf("%s","Hablar, ");
		sem_post(&terminaP6);
		i++;
	}
}

static void * tomarDecision(void *iteracion) {
	int N = *((int *) iteracion); 
	int i=0; 
	while (i<N) {
	//Estado Pensando
		sem_wait(&P7);
		sem_wait(&terminaP6);
		printf("%s","Tomar una decisión");
		sem_post(&P1);

		i++;
	}
}



int main()    {
	int *iteraciones = malloc(sizeof(*iteraciones));
	int a;
	printf("%s","Introducir el número de iteraciones deseado:  ");
	scanf("%d", &a);
	
	*iteraciones= a;

        pthread_t thread_1, thread_2, thread_3, thread_4,thread_5, thread_6,thread_7;
	sem_init(&P1,	0,1);        															//Inicializamos los semaforos
	sem_init(&P2,	0,0);
	sem_init(&P3,	0,0);
	sem_init(&P4,	0,0);
	sem_init(&terminaP1234,	0,0);
        sem_init(&P1234,0,4);
	sem_init(&P5,	0,0);
	sem_init(&P6,	0,0);
	sem_init(&terminaP6,	0,0);
	sem_init(&P7,	0,0);
	

        pthread_create(&thread_1, NULL, *pienso, iteraciones);						//Creamos los hilos
        pthread_create(&thread_2, NULL, *lavoPlatos, iteraciones);
        pthread_create(&thread_3, NULL, *limpioPisos, iteraciones);
	pthread_create(&thread_4, NULL, *riegoPlantas, iteraciones);
	pthread_create(&thread_5, NULL, *existo, iteraciones);
	pthread_create(&thread_6, NULL, *hablar, iteraciones);
	pthread_create(&thread_7, NULL, *tomarDecision, iteraciones);

	

        pthread_join(thread_1, NULL);													//Dormimos los hilos
        pthread_join(thread_2, NULL);
        pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	pthread_join(thread_5, NULL);
	pthread_join(thread_6, NULL);
	pthread_join(thread_7, NULL);
        
	sem_destroy(&P1);																//Destruimos los hilos
	sem_destroy(&P2);
	sem_destroy(&P3);
	sem_destroy(&P4);
	sem_destroy(&terminaP1234);
	sem_destroy(&terminaP6);
	sem_destroy(&P1234);
	sem_destroy(&P5);
	sem_destroy(&P6);
	sem_destroy(&P7);
	
        pthread_exit(NULL);

        printf("\n %s \n"," ");
    
        return 0;
}
