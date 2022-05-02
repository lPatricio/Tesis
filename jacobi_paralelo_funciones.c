#include "header_paralelo.h"

void asignarMemoriaDinamicaMatriz(double ***A,int a_filasReservadas){
		//Descripcion:asigna memoria dinamica a un puntero triple que es utilizado como matriz
		//Entrada:A, puntero triple de tipo double; filasReservadas, entero que indica 
		//	      la cantidad de filas que se reservaran
		//Salida: 		
		
		int i;
		
		*A=(double **)malloc(a_filasReservadas*sizeof(double*));
		
		for(i=0;i<a_filasReservadas;i++){     
			(*A)[i]=(double*)malloc(COLUMNASMATRIZ*sizeof(double));	
			if((*A)[i]==NULL){
				printf("ERROR ");
				return;
			}
		}
   }

void asignarMemoriaDinamica_parametrizada_Matriz(double ***A,int a_filasReservadas,int a_columnas_reservadas){
		//Descripcion:asigna memoria dinamica a un puntero triple que es utilizado como matriz
		//Entrada:A, puntero triple de tipo double; filasReservadas, entero que indica 
		//		  la cantidad de filas que se reservaran, columnas_reservadas, entero cantidad de columnas a
		//		  reservar
		//Salida: 		
		
		int i;
		
		*A=(double **)malloc(a_filasReservadas*sizeof(double*));
	
		for(i=0;i<a_filasReservadas;i++){     
			(*A)[i]=(double*)malloc(a_columnas_reservadas*sizeof(double));	
			if((*A)[i]==NULL){
				printf("ERROR ");
				return;
			}
		}
 }

void liberarMemoriaDinamicaMatriz(double*** A,int a_filasLiberadas ){
		//Descripcion:libera memoria dinamica de un puntero triple utilizado como matriz
		//Entrada:A,puntero triple de tipo double
		//Salida: 
		int i;
		for(i=0;i<a_filasLiberadas;i++){
			free( (*A)[i]);
		}
		free(*A);		
	}	

void leerMatrizBinariaParcial(int rank,double** A,int a_filasDesplazadas,int a_filasDeLectura){
		//Descripcion:lee datos en una archivo binario y los almacena en una matriz
		//Entrada:A,puntero triple de tipo double; filasDesplazadas, entero que indica la cantidad de filas
		//		  se deben desplazar antes de inciar lectira
		//		 filasDeLectura, entero que indica cuantas filas de la matriz completa debe leer un proceso 
		//Auxiliar:ARCHIVOMATRIZ constante con el nombre del archivo desde donde se leen los datos
		//Salida: 
		
		
		int file;
		long int a_desplazamiento;
		int i;
		
		
		if((file=open(ARCHIVOMATRIZ,O_RDWR,0777 ))<0){
			printf("No se ha encontrado el archivo.");
			return;
		}

		
		lseek(file,0, SEEK_SET );
		a_desplazamiento=a_filasDesplazadas*COLUMNASMATRIZ*sizeof(double);
		lseek(file,a_desplazamiento, SEEK_SET );
		
		
		for(i=0;i<a_filasDeLectura;i++){
			read( file, &A[i][0] ,sizeof(double)*COLUMNASMATRIZ );	

		}		
	
		close(file);

}	


void asignarMemoriaDinamicaVector(double** B,int a_cantidadDeElementos){
	//Descripcion:asigna memoria dinamica a un puntero doble utilizado como vector
	//Entrada:B,puntero doble de tipo double   
	//Salida: 
			
	*B= ( double * ) malloc( a_cantidadDeElementos * sizeof(double*)  ); 
	if(B==NULL){
			printf("ERROR");
	}
}

void asignarMemoriaDinamicaVectorDeEnteros(int** B,int a_cantidadDeElementos){
	//Descripcion:asigna memoria dinamica a un puntero doble utilizado como vector
	//Entrada:B,puntero doble de tipo entero   
	//Salida: 
			
	*B= ( int * ) malloc( a_cantidadDeElementos * sizeof(int*)  ); 
	if(B==NULL){
			printf("ERROR");
	}
}

void leerVector(double* B,int a_archivoFuente,int a_elementos_b,int a_indice_B){
	//Descripcion:realiza la lectura de un vector desde un archivo binario.
	//Entrada:B,puntero doble de tipo double; archivoFuente, entero que indica si la lectura es del 
	//        archivo solucion o de terminos independientes. 
	//Auxiliares: ARCHIVOSOLUCION constante que indica donde se encuentra el archivo solucion
	//			  ARCHIVOVECTORTERMINOSINDEPENDIENTES constante que indica donde 
	//			  se encuentra el archivo de terminos independientes
	//Salida: 
	
	int file;
	long int a_desplazamiento;
	char *archivoFinal;

	if(a_archivoFuente==1){
		archivoFinal=ARCHIVOVECTORTERMINOSINDEPENDIENTES;
	}else{
		archivoFinal=ARCHIVOSOLUCION;
	}

	
	if((file=open(archivoFinal,O_RDONLY))<0)
	{
		printf("No se pudo abrir el archivo.\n");
		return;
	}

	a_desplazamiento=a_indice_B*sizeof(double);
	lseek(file,a_desplazamiento, SEEK_SET );

	read( file, &B[0] ,sizeof(double)*a_elementos_b);

	close(file);	
}

void asignarElementosAVectorLocal(double* X1,double* X2, int a_cantidadDeElementos, int a_indice){
	//Descripcion:funcion utilizada para asignar a un vector local los elementos 
	//Entrada:    X1 puntero double ; X2 puntero doble ;
	//             cantidadDeElementos , entero que indica la cantidad de 
	//            elementos que le corresponden al proceso que llama a la funcion; 
	//			   indice, entero que indica a partir de que elemento del vector X1
	//            debe empezar a cargar los valores dentro  de X2.
	//  
	//Salida:
	int i;

	for (i = 0; i < a_cantidadDeElementos; ++i)
	{
		X1[i]=X2[a_indice];
		a_indice++;
	}
}

void liberarMemoriaDinamicaVector(double** B ){
	//Descripcion:libera memoria dinamica a un puntero doble utilizado como vector
	//Entrada:B,puntero doble de tipo double   
	//Salida: 
		
	free(*B);
}

void liberarMemoriaDinamicaVectorDeEnteros(int** B ){
	//Descripcion:libera memoria dinamica a un puntero doble de enteros utilizado como vector
	//Entrada:B,puntero doble de tipo double   
	//Salida: 
		
	free(*B);
}

void asignarValoresRecibidosAXSiguiente(double* XRecibidos, double* Xsiguiente,int a_elementos,int a_indice){
	//Descripcion: funcion llamada solamente por el proceso raiz, 
	//			   se encarga de asignar los nuevos valores de X recibidos de los distintos
	//             procesos al vector donde se encuentran todos los valores de la iteracion siguiente.
	//Entrada:     XRecibidos puntero doble con los nuevos valores de X recibidos de algun proceso; 
	//			   Xsiguiente puntero doble donde se almacenan 
	//             los valores de la siguiente iteracion; 
	//			   elementos, entero que indica cuantos valores se recibieron; indice
	//             entero que indica a partir de que elemento debe asignar los nuevos valores.   
	//        
	//Salida:
	int i;
	
	for (i = 0; i < a_elementos; ++i)
	{
		Xsiguiente[a_indice]=XRecibidos[i];
		a_indice++;
	}
}

float calcularError(double* vectorAuxiliarDeErrores,int a_elementosDelVector){
	//Descripcion:calcula el error absoluto en cada iteracion
	//Entrada: vectorAuxiliarDeErrores vector de double 
	//Salida:  errorCalculado numero real con el valor del error obtenido en cada iteracion
		
		
	//tomo como maximo error el valor almacenado en la posicion 0
	float errorCalculado=fabs( vectorAuxiliarDeErrores[0] );
	int i;

	for(i=1;i<a_elementosDelVector;i++){
		//si algun valor en auxErr[i] es mayor que el error actual entonces éste valor es el nuevo error 

		if( fabs( vectorAuxiliarDeErrores[i] )> errorCalculado ){
			errorCalculado=fabs( vectorAuxiliarDeErrores[i] );
		}
	}
		
	return errorCalculado;
}

void escribirSolucion(double* X,double a_error,double a_lectura_maestro,double a_ejecucion_maestro,double a_total_maestro,double a_tiempoTranscurridoLectura,double a_tiempoTranscurridoJacobi,double a_tiempoTranscurridoTotal,int a_numeroProcesos,double a_max_iteracion){
	//Descripcion:escribe los datos del resultado de la ejecucion de Jacobi en un archivo de texto
	//Entrada:    error de tipo float, tiempoTransurrido doble que indica el tiempo de ejecucion; 
	//			  numeroProcesos entero que indica la cantidad de procesadores
	//			  con la que se realizo la ejecucion.
	//Salida: 		

	FILE *destino;
	int i;
		
	if((destino=fopen(ARCHIVODESTINOSOLUCION,"at"))==NULL){
		printf("No se pudo abrir el archivo.");
		return;
	}
	fprintf(destino, "Columnas matriz %d\n", COLUMNASMATRIZ);
	fprintf(destino, "Procesadores %d\n", a_numeroProcesos);
	fprintf(destino,"Error %.20lf  \n",a_error);
	
	if (a_numeroProcesos==1){
		
		fprintf(destino,"Tiempos procesador maestro  \n");
		fprintf(destino,"Lectura %.10lf: \n",a_lectura_maestro);
		fprintf(destino,"Ejecucion %.10lf: \n",a_ejecucion_maestro);
		fprintf(destino,"Total %.10lf: \n",a_total_maestro);

		fprintf(destino,"Maximo tiempo de iteracion %.10lf: \n",a_max_iteracion);
	
		fprintf(destino,"Tiempos maximos  \n");
		fprintf(destino,"Lectura %.10lf: \n",a_tiempoTranscurridoLectura);
		fprintf(destino,"Ejecucion %.10lf: \n",a_tiempoTranscurridoJacobi);
		fprintf(destino,"Total %.10lf: \n",a_tiempoTranscurridoTotal);
	
	}else{

		fprintf(destino,"Tiempos procesador maestro  \n");
		fprintf(destino,"Lectura %.10lf: \n",a_lectura_maestro);
		fprintf(destino,"Ejecucion %.10lf: \n",a_ejecucion_maestro);
		fprintf(destino,"Total %.10lf: \n",a_total_maestro);
	
		fprintf(destino,"Tiempos maximos  \n");
		fprintf(destino,"Lectura %.10lf: \n",a_tiempoTranscurridoLectura);
		fprintf(destino,"Ejecucion %.10lf: \n",a_tiempoTranscurridoJacobi);
		fprintf(destino,"Total %.10lf: \n",a_tiempoTranscurridoTotal);

		fprintf(destino,"Maximo tiempo de iteracion %.10lf: \n",a_max_iteracion);
		
		fprintf(destino,"Tiempos maestro + maximos  \n");
		fprintf(destino,"Lectura %.10lf: \n",a_lectura_maestro + a_tiempoTranscurridoLectura);
		fprintf(destino,"Ejecucion %.10lf: \n",a_ejecucion_maestro + a_tiempoTranscurridoJacobi);
		fprintf(destino,"Total %.10lf: \n",a_ejecucion_maestro + a_tiempoTranscurridoTotal);
	}

	fprintf(destino, "\n" );
	
	fclose(destino);
		
}

void cargar_matriz_de_tiempos(int a_procesador_origen,double* a_tiempos,double ** a_A){
	//Descripcion: carga los tiempos recibidos de cada procesador en una matriz
	//Entrada: a_procesador_origen entero que representa el procesador al que pertenecen las mediciones,
	//         a_tiempos puntero a double que contiene las mediciones realizadas por el procesador
	//			a_A puntero doble a double representa una matriz donde se guardaran los tiempos medidos 
	//Salida:

	int i;

	
	for (i = 0; i < TIEMPOS_MEDIDOS; i++)
	{
		a_A[i][a_procesador_origen]=a_tiempos[i];
	}
	
}

void calcular_mayor_tiempo(double* a_max_lectura,double* a_max_ejecucion,double* a_max_total, double** a_A,int a_procesadores_activos){
	//Descripcion: calcula los maximos valores de tiempos medidos de entre todos los tiempos medidos
	//Entrada:     a_A matriz puntero doble a double que representa una matriz que contiene todos los tiempos medidos
	//Salida:      a_max_lectura puntero double es el maximo tiempo de lectura medido
	//			   a_max_ejecucion puntero a double es el maximo tiempo de ejecucion medido
	//			   a_max_total puntero a double es el maximo tiempo total medido	 	

	int i,j;
	*a_max_lectura=a_A[0][1];
	*a_max_ejecucion=a_A[1][1];
	*a_max_total=a_A[2][1];
	
	for (i = 0; i < TIEMPOS_MEDIDOS; ++i)
	{
	
		for ( j = 1; j < a_procesadores_activos; ++j)
		{
			
			switch(i){

				case 0:
					   if ( a_A[i][j]> *a_max_lectura ){
			 				*a_max_lectura=a_A[i][j];
			 			}
			 			break;
			 	case 1:
			 			if ( a_A[i][j]> *a_max_ejecucion){
			 				*a_max_ejecucion=a_A[i][j];
			 			}
			 			break;
				case 2:
						if ( a_A[i][j]> *a_max_total){
			 				*a_max_total=a_A[i][j];
			 			}
			 			break;
			}
		}
	}
}

void calcular_procesadores_activos(int* a_procesadores_activos,int a_cantidad_procesadores,int* a_tipo_ejecucion){
	//Descripcion: calcula la cantidad de procesadores que se encotraran activos en una ejecucion del programa
	//Entrada: a_cantidad_procesadores entero es la cantidad de procesadores con la que se inicio la ejecucion
	//Salida:  a_procesadores_activos puntero a entero es la cantidad de procesadores activos de la ejecucion
	//		   a_tipo_ejecucion puntero a entero que almacena una constante segun el tipo de ejecucion del programa
	//		   esta solo facilita el diseño del codigo	

	if(a_cantidad_procesadores>FILASMATRIZ){
		*a_procesadores_activos=FILASMATRIZ+1;
		*a_tipo_ejecucion=FILAS_MATRIZ_MAS_UNO_ACTIVOS;
	}
	if (a_cantidad_procesadores<=FILASMATRIZ && a_cantidad_procesadores>1){
		*a_procesadores_activos=a_cantidad_procesadores;
		*a_tipo_ejecucion=TODOS_ACTIVOS;
	}
	if (a_cantidad_procesadores==1){
		*a_procesadores_activos=1;
		*a_tipo_ejecucion=UNO_ACTIVO;
	}

}

bool esta_el_procesador_activo(int a_procesador,int a_procesadores_activos){
	//Descripcion: indica si el procesador que ejecuta el programa esta activo,
	//Entrada:     a_procesador entero es el procesador que realiza la ejecucion del prograema
	//			   a_procesadores_activos entero que indica la cantidad de procesadores que se encuentran activos en la ejecucion	
	//Salida:      booleano que indica el estado del procesador

	bool v_activo=false;

	if ( a_procesador<a_procesadores_activos)
			v_activo=true;

	return v_activo;
}

bool recibe_elementos_restantes(int a_procesador,int a_elementos_restantes){
	//Descripcion: indica si el procesador actual recibe elementos del resto de una division no entera 
	//			   de repartir las incognitas entre los procesdores activos
	//Entrada:     a_procesador entero que indica el procesador que realiza la ejecucion
	//			   a_elementos_restantes entero que indica la cantidad de elementos 
	//			   que restaron de la division entera	
	//Salida:      booleano que indica si el procesador recibe elmenentos restantes 

	bool v_recibe_elementos=false;

	if (a_procesador<=a_elementos_restantes && a_procesador>0)
			v_recibe_elementos=true;
	return v_recibe_elementos;
}

void calcular_elementos_del_procesador(int a_procesador,int a_elementos_minimos_procesador,int* a_elementos_del_procesador,int* a_elementos_desplazados_hasta_indice,int* a_indice_primer_elemento,int a_procesadores_restantes){
	
	//Descripcion: calcula las incognitas (o elementos) que debe calcular el procesador
	//			   cuando existe resto entre la division entera de la cantidad de
	//			   incognitas y los procesadores de la ejecucion
	//Entrada:     a_procesador entero que indica el procesador que realiza la ejecucion, 
	//			   a_elementos_mininmos_procesador entero que indica la minima
	//			   cantidad de elementos que recibe cada procesador, 
	//			    a_procesadores_restantes entero que indica la cantidad de procesadores que reciben elementos
	//				restantes de la division entera
	//Salida:      a_elementos_del_procesador puntero a entero que indica la 
	//			   cantidad de incognitas que debe calcular el procesador
	//			   a_elementos_desplazados_hasta_indice puntero a entero que indica 
	//				la cantidad de elementos que debe desplazarse el procesador hasta iniciar 
	//			   la lectura de las incognitas, 
	//			    a_indice_primer_elementos puntero a entero que indica el 
	//			    indice del primer elemento que le corresponde leer a un procesador 		

	if (recibe_elementos_restantes(a_procesador,a_procesadores_restantes) ){

		*a_elementos_del_procesador=a_elementos_minimos_procesador+1;
		*a_elementos_desplazados_hasta_indice=*a_elementos_del_procesador*(a_procesador-1); 
		*a_indice_primer_elemento=*a_elementos_desplazados_hasta_indice;
	}else{
		if(a_procesador>0){
			*a_elementos_del_procesador=a_elementos_minimos_procesador;
			*a_elementos_desplazados_hasta_indice=(*a_elementos_del_procesador+1)*a_procesadores_restantes + ( (a_procesador-1) - a_procesadores_restantes)*(*a_elementos_del_procesador);
			*a_indice_primer_elemento=*a_elementos_desplazados_hasta_indice;
		}
	}

}

bool recibe_filas_restantes(int a_procesador,int a_filas_restantes){
	
	//Descripcion: indica si el procesador actual recibe filas de matriz restantes
	//Entrada:     a_procesador entero que indica el procesador que realiza la ejecucion
	//			   a_filas_restantes entero que indica la cantidad de filas que restaron 
	//			   de la division entera	
	//Salida:      booleano que indica si el procesador recibe elmenentos restantes 

	bool v_recibe_filas=false;

	if (a_procesador<=a_filas_restantes && a_procesador>0)
	 	v_recibe_filas=true;

	 return v_recibe_filas;
}

void calcular_filas_del_procesador(int a_procesador,int a_filas_minimas_procesador,int* a_filas_del_procesador,int* a_filas_desplazadas_hasta_lectura,int* a_primer_fila,int a_procesadores_restantes){
	
	//Descripcion: calcula las filas de matriz que debe leer el procesador 
	//			   cuando existe resto entre la division entera de la cantidad de
	//			   filas y los procesadores de la ejecucion
	//Entrada:     a_procesador entero que indica el procesador que realiza la ejecucion, 
	//			   a_filas_minimos_procesador entero que indica la minima
	//			   cantidad de filas de matriz que lee cada procesador, 
	//			   a_procesadores_restantes entero que indica la cantidad de procesadores 
	//			    que reciben filas restantes de la division entera 
	//Salida:      a_filas_del_procesador puntero a entero que indica la cantidad 
	//			   de filas de matriz que debe leer el procesador
	//			   a_filas_desplazados_hasta_lectura puntero a entero que indica la 
	//			   cantidad de filas de matriz que debe desplazarse el procesador hasta iniciar 
	//			   lectura, a_primer_fila puntero a entero que indica la primer fila de matriz que le 
	//			   corresponde leer a un procesador 		

	if(recibe_filas_restantes(a_procesador,a_procesadores_restantes)){
		*a_filas_del_procesador=a_filas_minimas_procesador+1;
		*a_filas_desplazadas_hasta_lectura=*a_filas_del_procesador*(a_procesador-1);
		*a_primer_fila=*a_filas_desplazadas_hasta_lectura;
	}else{
		if (a_procesador>0){
			*a_filas_del_procesador=a_filas_minimas_procesador;
			*a_filas_desplazadas_hasta_lectura=(*a_filas_del_procesador+1)*a_procesadores_restantes + ( ( a_procesador-1) - a_procesadores_restantes)*(*a_filas_del_procesador);
			*a_primer_fila=*a_filas_desplazadas_hasta_lectura;
		}
	}	
}

bool procesador_maestro(int a_procesador) {
	//Descripcion: indica si el procesador que esta realizando la ejecucion es el 
	//			   procesador maestro (procesador de rank 0)
	//Entrada:     a_procesador entero que indica el procesador que realiza la ejecucion
	//Salida:      booleano indicando si se trata del procesador maestro 

	bool v_es_maestro=false;

	if(a_procesador==0)
		v_es_maestro=true;

	return v_es_maestro;	
}


void balanceo_sencillo(int a_cantidad_procesadores,int a_procesadores_act,int* a_max_cant_elem,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B){
//Descripcion: realiza el balanceo de carga en el caso mas sencillo: una incognita por procesador
//Entrada:    
//Salida:     
/*
	LA FUNCION REALIZA CONFIGURACION E IMPLICITAMENTE REALIZA EL BALANCEO DE CARGA PARA CADA PROCESADOR
*/		
		*a_max_cant_elem=1;
		a_actividades[0]=1;
		a_procesadores_activos[0]=1;
		a_elementos[0]=-1;
		a_subindices[0]=-1;
		a_filas[0]=-1;
		a_primer_fila[0]=-1;
		a_elem_B[0]=-1;
		a_indice_B[0]=-1;


		for (int i = 1; i < a_cantidad_procesadores; i++)
		{
			if (i<a_procesadores_act)
			{
				a_actividades[i]=1;
				a_procesadores_activos[i]=1;
				a_elementos[i]=1;
				a_subindices[i]=i-1;
				a_filas[i]=1;
				a_primer_fila[i]=i-1;
				a_elem_B[i]=1;
				a_indice_B[i]=i-1;

			}else{
				a_actividades[i]=-1;
				a_procesadores_activos[i]=-1;
				a_elementos[i]=-1;
				a_subindices[i]=-1;
				a_filas[i]=-1;
				a_primer_fila[i]=-1;
				a_elem_B[i]=-1;
				a_indice_B[i]=-1;
			}

		}

}

void carga_balanceada(int a_cantidad_procesadores,int a_procesadores_act,int a_elementos_minimos_procesador,int a_filas_minimas_procesador,int a_elemt_B,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B){
	//Descripcion: balancea la carga cuando no existen incongitas restantes de dividir incognitas/procesadores
	//Entrada:     
	//Salida:      

		a_actividades[0]=1;	
		a_procesadores_activos[0]=1;
		a_elementos[0]=-1;
		a_subindices[0]=-1;
		a_filas[0]=-1;
		a_primer_fila[0]=-1;
		a_elem_B[0]=-1;
		a_indice_B[0]=-1;

		//LA CANTIDAD DE PROCESADORES SIEMPRE VA A COINCIDIR CON LOS PROCESADORES ACTIVOS
		for (int i = 1; i < a_cantidad_procesadores; i++)
		{
			if (i< a_procesadores_act)
			{
				a_actividades[i]=1;
				a_procesadores_activos[i]=1;
				a_elementos[i]=a_elementos_minimos_procesador;
				a_subindices[i]=a_elementos_minimos_procesador*( i-1);
				a_filas[i]=a_filas_minimas_procesador;
				a_primer_fila[i]=a_filas_minimas_procesador*( i-1);
				a_elem_B[i]=a_elemt_B;
				a_indice_B[i]=a_elemt_B*( i-1);

			}else{
				a_actividades[i]=-1;
				a_procesadores_activos[i]=-1;
				a_elementos[i]=-1;
				a_subindices[i]=-1;
				a_filas[i]=-1;
				a_primer_fila[i]=-1;
				a_elem_B[i]=-1;
				a_indice_B[i]=-1;
			}

		}

}

void carga_desbalanceada(int a_cantidad_procesadores,int a_proc_act,int a_elementos_minimos_procesador,int a_filas_minimas_procesador,int a_elemt_B,int a_procesadores_elem_restantes,int a_procesadores_filas_restantes,int a_proc_B_restantes,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B){
	//Descripcion: balancea la carga cuando existen incongitas restantes de dividir incognitas/procesadores
	//Entrada:     
	//Salida: 

		a_actividades[0]=1;	
		a_procesadores_activos[0]=1;
		a_elementos[0]=-1;
		a_subindices[0]=-1;
		a_filas[0]=-1;
		a_primer_fila[0]=-1;
		a_elem_B[0]=-1;
		a_indice_B[0]=-1;

		for (int i = 1; i < a_cantidad_procesadores; i++)
	    {
			  	if (i < a_proc_act)
			  	{
			  		if (i <= a_procesadores_elem_restantes)
			  		{
			  				a_actividades[i]=1;
							a_procesadores_activos[i]=1;
							a_elementos[i]=a_elementos_minimos_procesador + 1;	
							a_subindices[i]=(a_elementos_minimos_procesador + 1) * (i-1);
							a_filas[i]=a_filas_minimas_procesador + 1;
							a_primer_fila[i]= (a_filas_minimas_procesador + 1) * (i-1);
							a_elem_B[i]= a_elemt_B + 1;
							a_indice_B[i]= (a_elemt_B + 1) * (i-1);

					}else{

							a_actividades[i]=1;
							a_procesadores_activos[i]=1;
							a_elementos[i]=a_elementos_minimos_procesador ;	
							a_subindices[i]=(a_elementos_minimos_procesador + 1) * a_procesadores_elem_restantes + ((i-1) - a_procesadores_elem_restantes) * a_elementos_minimos_procesador;
							a_filas[i]=a_filas_minimas_procesador ;
							a_primer_fila[i]= (a_filas_minimas_procesador + 1) * a_procesadores_filas_restantes + ((i-1) - a_procesadores_filas_restantes) * a_filas_minimas_procesador;
							a_elem_B[i]= a_elemt_B ;
							a_indice_B[i]= (a_elemt_B + 1) * a_proc_B_restantes + ((i-1) - a_proc_B_restantes) * a_elemt_B;

			  		}
			  	}else{
			  			//NO SE EJECUTA , SOLO POR CLARIDAD
			  			a_actividades[i]=-1;
						a_procesadores_activos[i]=-1;
						a_elementos[i]=-1;	
						a_subindices[i]=-1;
						a_filas[i]=-1;
						a_primer_fila[i]=-1;
						a_elem_B[i]=-1;
						a_indice_B[i]=-1;
			  	}
		}
}

bool procesador_activo(int a_estado_procesador){
	//Descripcion: indica el estado del procesador que llama a la funcion
	//Entrada:  a_estado_procesador entero, indica su estado    
	//Salida: 
	
	bool activo=false;

	if (a_estado_procesador==1)
	{
		activo=true;
	}

	return activo;

}

void configurar_procesador(int* a_info_procesador,int* a_estado_proc,int* a_elementos_proc,int* a_primer_indice,int* a_filas_proc,int* a_primer_fila,int* a_elem_B,int* a_indice_B){
	//Descripcion: asigna el estado, su carga de incognitas, su indice , sus filas, indice de filas, 
	//			 cantidad de elementos de B, indice de elementos de B a un procesador
	//Entrada:   a_info_procesador vector con la informacion del procesador  
	//Salida:    variables locales con la informacion cargada

		*a_estado_proc=a_info_procesador[0];
		*a_elementos_proc=a_info_procesador[1];
		*a_primer_indice=a_info_procesador[2];
		*a_filas_proc=a_info_procesador[3];
		*a_primer_fila=a_info_procesador[4];
		*a_elem_B=a_info_procesador[5];
		*a_indice_B=a_info_procesador[6];
}

void calcula_max_elem_vector(double* B,int a_elementos,double* max_elemento ){
	int i;
	if(a_elementos>0){
		*max_elemento=B[0];

		for ( i = 1; i < a_elementos; i++)
		{
			if (B[i]>*max_elemento)
				*max_elemento=B[i];
			
		}
		
	} 
}
