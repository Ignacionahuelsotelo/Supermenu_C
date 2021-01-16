#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para hacer sleep


sem_t A;
sem_t B;
sem_t C;
sem_t D;
sem_t E;


void do_nothing(int microseconds, char* mensaje){
  usleep(microseconds); //dormir el thread, simula que esta haciendo alguna tarea
  printf("\n %s \n",mensaje); 
}

static void * filosofo1(void *platos) {
	int N = *((int *) platos);
	int i=0; 
	while (i<N) {
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 1 : Pensando");
		do_nothing(2, "Eureka!");

		//Estado Agarrando palillo
		sem_wait(&E);
		printf("\n %s \n","Soy el Filósofo 1 : Agarrando palillo izquierdo");
		sem_wait(&A);
		printf("\n %s \n","Soy el Filósofo 1 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 1 : Comiendo");

		do_nothing(2, "Provecho!");
		i++;
		sem_post(&E);
		sem_post(&A);
	}
}


static void * filosofo2(void *platos) {
	int N = *((int *) platos);
	int i=0; 
	while (i<N){
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 2 : Pensando");
		do_nothing(2, "Eureka!");

		//Estado Agarrando palillo
		sem_wait(&B);
		printf("\n %s \n","Soy el Filósofo 2 : Agarrando palillo izquierdo");
		sem_wait(&A);
		printf("\n %s \n","Soy el Filósofo 2 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 2 : Comiendo");
		do_nothing(2, "Provecho!");
		i++;
		sem_post(&A);
		sem_post(&B);
	}
}

static void * filosofo3(void *platos) {
	int N = *((int *) platos);
	int i=0; 
	while (i<N) {
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 3 : Pensando");
		do_nothing(2, "Eureka!");

		//Estado Agarrando palillo
		sem_wait(&B);
		printf("\n %s \n","Soy el Filósofo 3 : Agarrando palillo izquierdo");
		sem_wait(&C);
		printf("\n %s \n","Soy el Filósofo 3 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 3 : Comiendo");
		do_nothing(2, "Provecho!");
		i++;
		sem_post(&B);
		sem_post(&C);
	}
}

static void * filosofo4(void *platos) {
	int N = *((int *) platos);
	int i=0; 
	while (i<N){
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 4 : Pensando");
		do_nothing(2, "Eureka!");

		//Estado Agarrando palillo
		sem_wait(&D);
		printf("\n %s \n","Soy el Filósofo 4 : Agarrando palillo izquierdo");
		sem_wait(&C);
		printf("\n %s \n","Soy el Filósofo 4 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 4 : Comiendo");
		do_nothing(2, "Provecho!");
		i++;
		sem_post(&C);
		sem_post(&D);
	}
}

static void * filosofo5(void *platos) {
	int N = *((int *) platos);
	int i=0; 
	while (i<N) {
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 5 : Pensando");
		do_nothing(2, "Eureka!");

		//Estado Agarrando palillo
		sem_wait(&D);
		printf("\n %s \n","Soy el Filósofo 5 : Agarrando palillo izquierdo");
		sem_wait(&E);
		printf("\n %s \n","Soy el Filósofo 5 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 5 : Comiendo");
		do_nothing(2, "Provecho!");
		i++;
		sem_post(&D);
		sem_post(&E);
	}
}

int main(void)    {
	pthread_t thread_1, thread_2, thread_3, thread_4,thread_5;

	int *platos = malloc(sizeof(*platos));
	int a;
	printf("%s","Introducir la cantidad de platos permitidos para cada filosofo:  ");
	scanf("%d", &a);

	*platos=a;
	
	sem_init(&A,0,1);														//inicializamos todos los semaforos como disponibles
	sem_init(&B,0,1);
	sem_init(&C,0,1);
	sem_init(&D,0,1);
	sem_init(&E,0,1);


	pthread_create(&thread_1, NULL, *filosofo1, platos);				//Creamos los hilos y les pasamos el número de platos como parametro
	pthread_create(&thread_2, NULL, *filosofo2, platos);
	pthread_create(&thread_3, NULL, *filosofo3, platos);
	pthread_create(&thread_4, NULL, *filosofo4, platos);
	pthread_create(&thread_5, NULL, *filosofo5, platos);



	pthread_join(thread_1, NULL);										//Dormimos los hilos
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	pthread_join(thread_5, NULL);

	sem_destroy(&A);													//Destruimos los semaforos
	sem_destroy(&B);
	sem_destroy(&C);
	sem_destroy(&D);
	sem_destroy(&E);

	pthread_exit(NULL);

	printf("\n %s \n"," ");

        return 0;
}
