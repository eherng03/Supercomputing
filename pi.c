#include <omp.h>
#include <stdio.h>
#include <math.h>
double funcion(double a);

int main(int argc, char *argv[]){
	int n, i;
	double PI25DT = 3.141592653589793238462643; 
	double pi, h, sum,x;
	n=100; //Número de intervalos
	h= 1.0 / (double) n;
	sum=0.0; //Suma de intervalos
	
	//La variable pi es una variable de reducción (+)
	#pragma omp parallel for reduction (+:pi)
	for(i=1;i<=n;i++){
		x=h*((double)i - 0.5);
		pi+=funcion(x);
	}
	pi=h*pi;
	printf("\n Pi es aproximadamente %.16f.El error cometido es %.16f\n", pi, fabs(pi-PI25DT));
	return 0;
}

double funcion(double a){
	return (4.0/(1.0 + a*a));
}

