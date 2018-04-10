#include <stdio.h>
#include <mpi.h>

#define N 20

int main(int argc, char* argv[]){

	//Variables de mi programa
	int size, rank, i, from, to, ndat, part, tag, VA[N], dataSize;
	MPI_Status info;

	
	//Inicializo MPI
	MPI_Init(&argc, &argv);
	//Calculo cuántos procesos hay
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	//Calculo qué proceso soy
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//Inicializo vector a 0
	for (i=0; i<N; i++) {
		VA[i] = 0;
	}
	//Si soy maestro, inicializo los elementos del vector para que guarden su posición (i)

	if (rank == 0){
		for (i=1; i<N; i++) {
			VA[i] = i;
		}
	}
	//Para todos: imprimo el vector
	/*printf("Proceso %d: VA antes de recibir datos: \n",rank);
	for (i=0; i<N; i++) {
		printf("%d  ",VA[i]);
	}
	*/	
	//Calculamos cuántos datos corresponden a cada proceso (suponemos que es divisible el 		número de datos entre el número de procesos)
	dataSize = N/size;
	//Dividimos el vector en partes, y las distribuimos entre los procesos usando SCATTER
 	MPI_Scatter(&VA[0], dataSize, MPI_INT, &VA[0], dataSize, MPI_INT, 0, MPI_COMM_WORLD);
	//Sincronizar todos los procesos en este punto
	MPI_Barrier(MPI_COMM_WORLD);
	//Cada proceso imprime su parte del vector
	printf("Proceso %d: VA después de recibir los datos: \n", rank);
	for (i=0; i<N; i++) {
		printf("%d  ",VA[i]);
	}
	printf("\n\n");
	
	MPI_Finalize();
	return 0;
}

