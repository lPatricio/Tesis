#include "archivoHeader.h"


	int main(){
		
		
			bool convergeElMetodo;			 
			double* errorObtenido;            
			int* iteracionesUtilizadas;       
			double** A;
			double* B;
			double* X;
			
			printf("Iniciando ejecucion del programa.\n");
			printf("Cargando matrices.\n");
			iteracionesUtilizadas=malloc(sizeof(int));
			errorObtenido=malloc(sizeof(double));
			
			/*ASIGNACION DE MEMORIA*/
			asignarMemoriaDinamicaMatriz(&A);
			asignarMemoriaDinamicaVector(&B);
			asignarMemoriaDinamicaVector(&X);
			
			/*LECTURA DE DATOS*/
			leerMatriz(A);
			leerVector(B,2);
			leerVector(X,1);
			
			printf("Iniciando ejecucion...\n");
			clock_t start= clock();
			convergeElMetodo=metodoDeJacobi(A,B,X,errorObtenido,iteracionesUtilizadas);
			clock_t end=clock();
			
			
			if(convergeElMetodo){
				printf("Resultado exitoso!! \n");
			}else{
				printf("Se ha alcanzado el maximo numero de iteraciones sin exito! \n");
			}
			double tiempoTranscurrido=((double)(end-start)/(double)CLOCKS_PER_SEC );
			printf("Tiempo transcurrido es : %f \n",tiempoTranscurrido);

			escribirSolucion(*errorObtenido,*iteracionesUtilizadas,tiempoTranscurrido);
			printf("Su solucion se ha escrito en la carpeta Soluciones \n");
			
			/*LIBERAR MEMORIA*/
			liberarMemoriaDinamicaMatriz(&A);
			liberarMemoriaDinamicaVector(&B);
			liberarMemoriaDinamicaVector(&X);

			free(iteracionesUtilizadas);
			free(errorObtenido);
	
			return 0;
	}
