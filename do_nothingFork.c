#include <stdio.h>  //incluimos la libreria de estandar input/output
#include <unistd.h> //para hacer sleep
#include <stdlib.h> //para libreria de numeros random: srand, rand 
#include <time.h>   //para inicializar el tiempo
#include <sys/types.h>
#include <sys/wait.h>

void do_nothing(int microseconds, char* mensaje){
  usleep(microseconds); //dormir el thread, simula que esta haciendo alguna tarea
  printf("\n %s \n",mensaje); 
}

void do_nothing_random(char* mensaje){
  srand(time(NULL));                    //inicializar la semilla del generador random:
  int microseconds = rand() % 1000 + 1; //generar un numer random entre 1 y 1000:
  usleep(microseconds);                 //dormir el thread, simula que esta haciendo alguna tarea
  printf("\n %s \n",mensaje); 
}


int main() {
	char* msg1= "";				
	char* msg2= "";
	int pid= fork();			//Usamos la llamada al sistema fork y guardamos en pid su valor
	int pidC;
	int status; 
	if (pid!=0){					//proceso padre
		printf("\n pid del padre=  %d \n",getpid());	

		printf("\n %s","Padre llama do_nothing");
		do_nothing(2000000, msg1);
		printf("\n %s","Padre Termina do_nothing");

		printf("\n %s","Padre llama do_nothing");
		do_nothing(2000000, msg1);
		printf("\n %s","Padre llama do_nothing");

		pidC = wait(&status);		//Usamos la llamada al sistema wait
	}
	else{ 					//proceso hijo
		printf("\n pid del hijo=  %d \n",getpid());

		printf("\n %s","Hijo llama do_nothing");
		do_nothing(2000000,msg2); //esperar 2 segundos, 1 millon de microsegundos en 1 segundo
		printf("\n %s","Hijo Termina do_nothing");

		printf("\n %s","Hijo llama do_nothing");
		do_nothing(2000000,msg2);
		
		printf("\n %s","Hijo Termina do_nothing");
 	 }
  return 0;
  	
}

//para compilar: gcc do_nothing.c -o ejecutable
//para ejecutar: ./ejecutable

 
