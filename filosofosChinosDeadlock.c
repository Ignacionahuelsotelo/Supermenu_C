#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h> //para hacer sleep
#include <sys/types.h>
#include <signal.h>


sem_t A;
sem_t B;
sem_t C;
sem_t D;
sem_t E;


void do_nothing(int microseconds, char* mensaje){
  usleep(microseconds); //dormir el thread, simula que esta haciendo alguna tarea
  printf("\n %s \n",mensaje); 
}

static void * filosofo1() { 
	while (1) {
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
		sem_post(&E);
		do_nothing(2, "Provecho!");
		sem_post(&A);
	}
}


static void * filosofo2() { 
	while (1) {
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 2 : Pensando");
		do_nothing(2, "Eureka!");
		
		//Estado Agarrando palillo
		sem_wait(&A);
		printf("\n %s \n","Soy el Filósofo 2 : Agarrando palillo izquierdo");
		sem_wait(&B);
		printf("\n %s \n","Soy el Filósofo 2 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 2 : Comiendo");
		sem_post(&A);
		do_nothing(2, "Provecho!");
		sem_post(&B);
	}
}

static void * filosofo3() { 
	while (1) {
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
		sem_post(&B);
		do_nothing(2, "Provecho!");
		sem_post(&C);
	}
}

static void * filosofo4() { 
	while (1) {
		//Estado Pensando
		printf("\n %s \n","Soy el Filósofo 4 : Pensando");
		do_nothing(2, "Eureka!");
		
		//Estado Agarrando palillo
		sem_wait(&C);
		printf("\n %s \n","Soy el Filósofo 4 : Agarrando palillo izquierdo");
		sem_wait(&D);
		printf("\n %s \n","Soy el Filósofo 4 : Agarrando palillo derecho");
		//Estado Comiendo
		printf("\n %s \n","Soy el Filósofo 4 : Comiendo");
		sem_post(&C);
		do_nothing(2, "Provecho!");
		sem_post(&D);
	}
}

static void * filosofo5() { 
	while (1) {
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
		sem_post(&D);
		do_nothing(2, "Provecho!");
		sem_post(&E);
	}
}

static void * mozo() { 
	do_nothing(10000000, "Mozo: Vayan a comer a otro lado!");
	sem_destroy(&A);
	sem_destroy(&B);
	sem_destroy(&C);
	sem_destroy(&D);
	sem_destroy(&E);
	kill(getpid(), SIGKILL);
}

int main(void)    {
        pthread_t thread_1, thread_2, thread_3, thread_4,thread_5,thread_6;
        sem_init(&A,0,1);
        sem_init(&B,0,1);
	sem_init(&C,0,1);
	sem_init(&D,0,1);
	sem_init(&E,0,1);
	

        pthread_create(&thread_1, NULL, *filosofo1, NULL);
        pthread_create(&thread_2, NULL, *filosofo2, NULL);
        pthread_create(&thread_3, NULL, *filosofo3, NULL);
	pthread_create(&thread_4, NULL, *filosofo4, NULL);
	pthread_create(&thread_5, NULL, *filosofo5, NULL);
	pthread_create(&thread_6, NULL, *mozo, NULL);

	

        pthread_join(thread_1, NULL);
        pthread_join(thread_2, NULL);
        pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	pthread_join(thread_5, NULL);
	pthread_join(thread_6, NULL);
        
	sem_destroy(&A);
	sem_destroy(&B);
	sem_destroy(&C);
	sem_destroy(&D);
	sem_destroy(&E);
	
        pthread_exit(NULL);

    
        return 0;
}
