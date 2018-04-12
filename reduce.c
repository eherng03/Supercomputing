#include <stdio.h>
#include <mpi.h>

#define N 10

int main(int argc, char* argv[]){

	//Variables de mi programa
	int size, rank, i, from, to, ndat, part, tag, VA[N], dataSize, sumaParcial, resultado;
	MPI_Status info;

	
	//Inicializo MPI
	MPI_Init(&argc, &argv);
	//Calculo cuántos procesos hay
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	//Calculo qué proceso soy
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	sumaParcial = 0;
	resultado = 0;	
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

	//printf("Proceso %d: VA antes de recibir datos: \n",rank);
	//Para todos: imprimo el vector
	/*printf("Proceso %d: VA antes de recibir datos: \n",rank);
	for (i=0; i<N; i++) {
		printf("%d  ",VA[i]);
	}
	*/
	//Calculamos cuántos datos corresponden a cada proceso
	dataSize = N/size;
	//Dividimos el vector en partes, y las distribuimos entre los procesos 
 	MPI_Scatter(&VA[0], dataSize, MPI_INT, &VA[0], dataSize, MPI_INT, 0, MPI_COMM_WORLD);	
	//Cada proceso multiplica por 2 su parte del vector
	MPI_Barrier(MPI_COMM_WORLD);	

	for(i = 0; i < dataSize; i++){
		VA[i] = VA[i]*2;
		sumaParcial += VA[i]; 

	}
	printf("Proceso %d: VA después de recibir los datos y multiplicarlos por 2: \n", rank);
	//Cada proceso imprime su parte del vector
	for (i=0; i<N; i++) {
		printf("%d  ",VA[i]);
	}
	printf("\n\n");
	//Uso gather para recolectar los valores nuevos en un nuevo vector

	MPI_Reduce(&sumaParcial, &resultado, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	//El maestro imprime el vector final
	if (rank == 0){
		printf("Proceso %d: VA después de recibir los datos: \n", rank);
		//for (i=0; i<N; i++) {
			printf("%d  ",resultado);
		//}	
	}		
	//Cierro MPI
	MPI_Finalize();
	return 0;
}
