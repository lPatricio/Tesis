#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

    double tiempo_inicio,tiempo_fin;

    tiempo_inicio=MPI_Wtime();
        /*CODIGO DE INTERÉS EN MEDIR EL TIEMPO DE EJECUCIÓN*/
    tiempo_fin=MPI_Wtime();

    printf("El tiempo de ejecucion es %lf ",tiempo_fin-tiempo_inicio);

    return 0;
}