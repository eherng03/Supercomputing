//Librería que contiene las funciones scanf y printf
#include <omp.h>
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

//Definimos las constantes del programa
#define ORDEN  100


double wallclock(void);

//Función principal del programa
int main (int argc, char *argv[]) 

{
	
	// Declaro las variables de mi función
	int i,j,t,s,n;
	
    int mA[ORDEN][ORDEN],mB[ORDEN][ORDEN];
	int mC[ORDEN][ORDEN];	
	double time_cpu, t0, t1;
	n=ORDEN;
	
	srand(time(NULL));
	
	//En C las matrices de n filas tienen filas de la 0 a la n-1
	for (i=0;i<ORDEN;i++)
	{
		//En C las matrices de n columnas tienen cols. de la 0 a la n-1
		for (j=0;j<ORDEN;j++)
		{
			//Inicializo las matrices
			mA[i][j]=rand() % 100;
			mB[i][j]=rand() % 100;
		}
	}
	
	t0 = wallclock();
	//Insertar la directiva para que 
	//cada thread trabaje con un bloque de filas de la matriz a
	#pragma omp parallel for private (s, j, t) 
	for (i=0;i<n;i++)
		for(j=0;j<n;j++){
			s=0;
			for(t=0;t<n;t++){	
				s = s + mA[i][t] * mB[t][j];
				
			}
			mC[i][j]=s;
			
		}
	
	t1 = wallclock();
	time_cpu = (t1-t0);
	
	//Imprimo la matriz
	printf("\n");
	
	for (i=0;i<ORDEN;i++)
	{
		//En C las matrices de n columnas tienen cols. de la 0 a la n-1
		for (j=0;j<ORDEN;j++)
		{
			printf("%d\t", mC[i][j]);
		}
		printf("\n");
	}
	
	printf("\n Se ha tardado %f ms\n",(double)time_cpu * 1e3);
	//Fin del programa
	
	return 0;
	
}
double wallclock(void)
{
	struct timeval tv;
	double t;
	
	gettimeofday(&tv, NULL);
	
	t = (double)tv.tv_sec;
	t += ((double)tv.tv_usec)/1000000.0;
	
	return t;
}
