#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void sumaparcial(double *a, int n);
double sumatotal(double *a, int n, int THREADS);
double suma(double *a, int n, int THREADS);

int main ()
{
	double vector[100],resultado;
	int i,tam=100;
	srand(time(NULL));
	for (i=0; i<tam; i++) 
		vector[i]=rand()%100;
	resultado=suma(vector,tam,5);
	printf("El resultado es %f",resultado);
}
void sumaparcial(double *a, int n){
	//Esta función suma los n primeros elementos del vector a[] y deja el resultado de la suma
	// en a[0]
	int i;
	for(i = 0; i < n; i++){
		a[0] += a[i];	
	}
}
double sumatotal(double *a, int n, int THREADS){
	//Esta función calcula el total de la suma
	//Para ello suma la primera posición de los subvectores de cada thread
	double sumaTotal = 0;
	int i;

	for(i = 0; i < THREADS; i++){
		sumaTotal += a[i*n/THREADS];
	}
	return sumaTotal;

}
//a es el array donde están los datos
//n es el número de datos
//THREADS es el número de threads que intervienen
double suma(double *a, int n, int THREADS){
	int i;
	
//Incluir aquí la directiva correspondiente para parallelizar el bucle for siguiente
	#pragma omp parallel for shared (a, n, THREADS)
	//todos los threas realizan sumas parciales (sumas de los subvectores)
	for (i=0;i<THREADS;i++)
		sumaparcial(&a[i*n/THREADS],n/THREADS);
	//y el maestro acumula los resultados parciales
	return sumatotal(a,n,THREADS);
}
