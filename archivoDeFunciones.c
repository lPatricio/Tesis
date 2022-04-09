#include "archivoHeader.h"

 void asignarMemoriaDinamicaMatriz(double ***A){
		//Descripcion:asigna memoria dinamica a un puntero triple que es utilizado como matriz
		//Entrada:A, puntero triple de tipo double
		//Salida: 		
		
		int i;
		
		*A=(double **)malloc(FILASMATRIZ*sizeof(double*));
		
		for(i=0;i<FILASMATRIZ;i++){
			(*A)[i]=(double*)malloc(COLUMNASMATRIZ*sizeof(double));	
			if((*A)[i]==NULL){
				printf("ERROR ");
				return;
			}
		}
		
	}

void liberarMemoriaDinamicaMatriz(double*** A ){
		//Descripcion:libera memoria dinamica de un puntero triple utilizado como matriz
		//Entrada:A,puntero triple de tipo double
		//Salida: 

		int i;
		for(i=0;i<FILASMATRIZ;i++){
			free( (*A)[i]);
		}
				
		free(*A);		
	}	
	
void asignarMemoriaDinamicaVector(double** B){
		//Descripcion:asigna memoria dinamica a un puntero doble utilizado como vector
		//Entrada:B,puntero doble de tipo double   
		//Salida: 
			
		*B= ( double * ) malloc( COLUMNASMATRIZ * sizeof(double*)  ); 
		if(B==NULL){
			printf("ERROR");
			return;
			
		}
	}

	void liberarMemoriaDinamicaVector(double** B ){
		//Descripcion:libera memoria dinamica a un puntero doble utilizado como vector
		//Entrada:B,puntero doble de tipo double   
		//Salida: 
		
		free(*B);
	}

	
double calculoError(double* vectorAuxiliarDeErrores){
		//Descripcion:calcula el error en cada iteracion
		//Entrada: vectorAuxiliarDeErrores vector de double de tamaño ELEMENTOSVECTOR 
		//Salida:  errorCalculado numero real con el valor del error obtenido en cada iteracion
		
		
		//tomo como maximo error el valor almacenado en la posicion 0
		double errorCalculado=fabs( vectorAuxiliarDeErrores[0] );
		int i;

		for(i=1;i<ELEMENTOSVECTOR;i++){
			//si algun valor en auxErr[i] es mayor que el error actual 
			//entonces éste valor es el nuevo error 

			if( fabs( vectorAuxiliarDeErrores[i] )>errorCalculado ){
				errorCalculado=fabs( vectorAuxiliarDeErrores[i] );
			}
		}
		
		return errorCalculado;
	}
	
bool  metodoDeJacobi(double** A,double* B,double* X,double *errorRetornado,int *iteracionesRealizadas){
			//Descripcion:ejecuta el algoritmo de Jacobi
			//Entrada: A matriz de numeros reales de FILASMATRIZxCOLUMNASMATRIZ,
		    //	       B vector de numeros reales de tamaño ELEMENTOSVECTOR,
		    //         X vector de numeros reales con la solucion inicial de tamaño ELEMENTOSVECTOR,
			//Salida : booleano indicando exito o fracaso (dadas las condiciones de la matriz
			//         de entrada siempre retornara un resultado exitoso)	
			//         iteracionesRealizadas puntero a entero que retorna
			//         el numero de iteraciones realizado en caso de hallar una solucion,	     
			//         errorRetornado puntero a real que retorna el error logrado 
			//		   en caso de alcanzar una solucion.		
			//Aux    : vectorDeErrores vector de numeros reales de tamaño ELEMENTOSVECTOR, 
			//		   almacena el error de cada elemento en cada iteracion,
			//         aux numero real utilizado para almacenar la nueva solucion X[i] obtenida en cada iteracion
			//         (se utiliza por comodidad y ademas su almacenamiento es despreciable)
		    //         Xsig vector de numeros reales de tamaño dim utilizado para almacenar el nuevo valor de 

			*iteracionesRealizadas=0;   
			double aux;
			*errorRetornado=100;
			double* vectorDeErrores;
			
			double*  Xsig; 
			  
			int i,j;
			
			asignarMemoriaDinamicaVector(&vectorDeErrores);
			asignarMemoriaDinamicaVector(&Xsig);
			
			while(*iteracionesRealizadas<CANTIDADMAXIMADEITERACIONES && *errorRetornado>=COTADEERROR){
				//CALCULO DE LA PROXIMA ITERACION DE CADA ELEMENTO
				for(i=0;i<FILASMATRIZ;i++){
					aux=0;
					
					for(j=0;j<COLUMNASMATRIZ;j++){
						if(i!=j){
							aux=aux+ A[i][j]*X[j];
						}
					}
					
					aux=( B[i]-aux )/A[i][i];	

					vectorDeErrores[i]=(aux-X[i]);
					Xsig[i]=aux;
				}
			
				
				*iteracionesRealizadas=*iteracionesRealizadas+1;
	            *errorRetornado=calculoError(vectorDeErrores);     
			
				for(i=0;i<ELEMENTOSVECTOR;i++){
					X[i]=Xsig[i];
				}
			}
		
			liberarMemoriaDinamicaVector(&vectorDeErrores);
			liberarMemoriaDinamicaVector(&Xsig);
			
			if(*iteracionesRealizadas<CANTIDADMAXIMADEITERACIONES)
				return true;
			
			return false;
			
	}
	
void escribirSolucion(double error,int numeroDeIteraciones,double tiempoTranscurrido){
		//Descripcion:escribe los datos del resultado de la ejecucion de Jacobi en un archivo de texto
		//Entrada:error de tipo float, numeroDeIteraciones de tipo entero, tiempoTranscurrido de tipo double   
				
		FILE *destino;
		int i;
		
		if((destino=fopen(ARCHIVODESTINOSOLUCION,"wt"))==NULL){
			printf("No se pudo abrir el archivo.");
			return;
		}
		fprintf(destino,"El error alcanzado es %.20lf  \n",error);
	    fprintf(destino,"El numero de iteraciones es %i  \n",numeroDeIteraciones);
	    fprintf(destino, "El tiempo transcurrido es %.20lf\n", tiempoTranscurrido);
	    fprintf(destino, "Su solucion es :\n");

	    fclose(destino);
}

void leerMatriz(double** A){
		//Descripcion:lee datos en una archivo de texto y 
		//los guarda en un puntero doble que representa una matriz.
		//Entrada:A,puntero doble de tipo double que representa una matriz.
	    //Salida: A,puntero doble de tipo double con datos cargados
		
		int file;
		int i;
		
		if((file=open(ARCHIVOMATRIZ,O_RDONLY))<0){
			printf("No se ha encontrado el archivo.");
			return;
		}
		
		for(i=0;i<FILASMATRIZ;i++){
			read( file, &A[i][0] ,sizeof(double)*COLUMNASMATRIZ );	
		}
		
		close(file);	
}

void leerVector(double* B,int archivoFuente){
		//Descripcion:lee datos de un achivo binario y los guarda en puntero que representa un vector
		//Entrada:B,puntero simple de tipo double que representa un vector; 
		//archivoFuente, entero que indica cual sera el archivo fuente.
		//Salida: B,puntero simple de tipo double con datos cargados

		int file;
		char *archivoOrigen;
		
		if (archivoFuente==1){
			archivoOrigen=ARCHIVOSOLUCION;
		}else{
			archivoOrigen=ARCHIVOVECTORTERMINOSINDEPENDIENTES;
		} 
		
		if((file=open(archivoOrigen,O_RDONLY))<0){
			printf("No se ha encontrado el archivo.");
			return;
		}
		
		read( file, &B[0] ,sizeof(double)*ELEMENTOSVECTOR );	
		
		close(file);
}


















	
