#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

    double tiempo_global;
    double tiempo_inicio_local,tiempo_fin_local,tiempo_ejecucion_local;

    /*SINCRONIZACIÓN DE PROCESOS*/
    MPI_Barrier();

    
    tiempo_inicio_local=MPI_Wtime();
        /*CODIGO DE INTERÉS EN MEDIR EL TIEMPO DE EJECUCIÓN*/
    tiempo_fin_local=MPI_Wtime();

    tiempo_ejecucion_local=tiempo_fin_local-tiempo_inicio_local;
    /*EL TIEMPO DE EJECUCIÓN DE CADA PROCESADOR ES ENVIADO
      AL PROCESADOR ENCARGADO DE BUSCAR EL MÁXIMO TIEMPO DE EJECUCIÓN  
    */
     
     if (idproceso==0)
     {
         funcion_maximo_tiempo(&tiempo_global);
         printf('El tiempo de ejecucion maxim es %lf',tiempo_global);
     }
     
    return 0;
}