
/* ***** ***** ***** ***** ***** ***** */
/* Universidad Nacional de Tucumán */
/*      Agosto del 2018 - UNT         */
/*     Autor: Patricio López          */
/* ***** ***** ***** ***** ***** ***** */

#include "header_paralelo.h"
#include <mpi.h>


int main(int argc, char *argv[])
{

	int rank,world_size;

	MPI_Init (NULL, NULL);    
  
  	MPI_Comm_rank (MPI_COMM_WORLD, &rank);       
  	MPI_Comm_size (MPI_COMM_WORLD, &world_size); 

  	double** A;
  	double* B;
  	double* X;
  	double* Xlocal;
  	double* Xsiguiente;
  	double* vectorDeErrores;
	double* ITERACIONES=NULL;
  	double v_errorLocal;

    int* v_almacen_actividad;
  	int* v_procesadores_activos;
  	int v_esta_activo;
	double* v_tiempos;
	double** v_almacen_tiempos;
	double v_maximo_lectura;
	double v_maximo_ejecucion;
	double v_maximo_total;

	double v_lectura_maestro;
	double v_ejecucion_maestro;
	double v_total_maestro;
	
  	
	int v_filasDesplazadasHastaIniciarLectura;  
	int v_elementosDesplazadosHastaIndice;
	int v_filasDeMatrizDelProcesador;
	int v_elementosDeVectorDelProcesador;
	int v_filasDeMatrizMinimasPorProcesador;
    int v_elementosDeVectorMinimosPorProcesador;   
    int v_indiceDelPrimerElemento;
	int v_indiceDeLaPrimerFila;
	int v_elemB_procesador;
	int v_indice_B_procesador;
	int v_elem_despl_B;
	
	int v_indiceDelPrimerElementoLocal;
	int v_indiceDeLaPrimerFilaLocal;
	int v_indice_B_local;

	
	int v_filasDeMatrizRestantesADistribuir;
	int v_elementosRestantesADistribuir;
	int v_procesadoresQueRecibenFilasRestantes;
	int v_procesadoresQueRecibenElementosRestantes;
	int v_numeroDeProcesadoresActivos;
	
	int v_maximaCantidadDeElementos;
	int v_elementosRecibidos;
	int v_indiceRecibido;
	
	double v_inicioLectura,v_inicioJacobi,v_finalLectura,v_finalJacobi,v_finalEjeucion;
	double v_inicioIteracion,v_finIteracion,v_max_iteracion;
	int v_iteracion;
	int* vectorDeInfo;
    int* vectorDeElementos;
    int* vectorDeSubindices;
	int* vectorFilas;
	int* vectorPrimerFila;
	int* vectorB;
	int* vec_indice_B;
	int v_elemB_rest;
	int v_procRecibenBRestantes;
	
	double* XReceptor;
	MPI_Status status;
	int v_tipo_ejecucion;
	int i,j;
	int v_estado_proc;
	
	
	if (rank==0)
	{
		printf("Inicio de configuracion de procesos...\n");
			//INICIO LECTURA DE VECTORES Y MATRICES
	}



	
	
	if (procesador_maestro(rank))
	{	
		calcular_procesadores_activos(&v_numeroDeProcesadoresActivos,world_size,&v_tipo_ejecucion);

		asignarMemoriaDinamicaVector(&Xsiguiente,ELEMENTOSVECTOR);
		asignarMemoriaDinamicaVector(&vectorDeErrores,ELEMENTOSVECTOR);
		asignarMemoriaDinamicaVector(&X,ELEMENTOSVECTOR);

		switch(v_tipo_ejecucion){
			
			case(UNO_ACTIVO):
				
				    v_elementosDeVectorDelProcesador=ELEMENTOSVECTOR;
					v_elementosDesplazadosHastaIndice=rank;

					v_filasDeMatrizDelProcesador=FILASMATRIZ;
					v_filasDesplazadasHastaIniciarLectura=rank;

					v_elemB_procesador=ELEMENTOSVECTOR ;
					v_elem_despl_B=rank;
										

					v_indiceDelPrimerElemento=v_elementosDesplazadosHastaIndice;
					v_indiceDeLaPrimerFila=v_filasDesplazadasHastaIniciarLectura;
					v_indice_B_procesador=v_elem_despl_B;

			        asignarMemoriaDinamicaVector(&B,ELEMENTOSVECTOR);
					asignarMemoriaDinamicaMatriz(&A,v_filasDeMatrizDelProcesador);
					
					v_estado_proc=1;
					
					
			break;
		
			case(FILAS_MATRIZ_MAS_UNO_ACTIVOS):
				//UNA INCOGNIRA POR PROCESADOR - NUNCA OCURRE
					asignarMemoriaDinamicaVectorDeEnteros(&vectorDeElementos,world_size);
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorDeSubindices,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorFilas,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorPrimerFila,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorB,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vec_indice_B,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorDeInfo,7);
			  		asignarMemoriaDinamica_parametrizada_Matriz(&v_almacen_tiempos,TIEMPOS_MEDIDOS,v_numeroDeProcesadoresActivos);
			  		asignarMemoriaDinamicaVector(&v_tiempos,TIEMPOS_MEDIDOS);
					asignarMemoriaDinamicaVectorDeEnteros(&v_procesadores_activos,world_size);
			  		asignarMemoriaDinamicaVectorDeEnteros(&v_almacen_actividad,world_size);
			  		asignarMemoriaDinamicaVector(&XReceptor,1);
			  		balanceo_sencillo(world_size,v_numeroDeProcesadoresActivos,&v_maximaCantidadDeElementos,v_procesadores_activos,v_almacen_actividad,vectorDeElementos,vectorDeSubindices,vectorFilas,vectorPrimerFila,vectorB,vec_indice_B);
			  	
					v_estado_proc=1;
			break;
			
			case(TODOS_ACTIVOS):
				//CASO NORMAL

					asignarMemoriaDinamicaVectorDeEnteros(&vectorDeElementos,world_size);
					asignarMemoriaDinamicaVectorDeEnteros(&vectorDeSubindices,world_size);	
					asignarMemoriaDinamicaVectorDeEnteros(&vectorFilas,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorPrimerFila,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorB,world_size);	
			  		asignarMemoriaDinamicaVectorDeEnteros(&vec_indice_B,world_size);

			  		asignarMemoriaDinamicaVectorDeEnteros(&vectorDeInfo,7);	
			  		asignarMemoriaDinamica_parametrizada_Matriz(&v_almacen_tiempos,TIEMPOS_MEDIDOS,v_numeroDeProcesadoresActivos);
			  		asignarMemoriaDinamicaVector(&v_tiempos,TIEMPOS_MEDIDOS);
			  		asignarMemoriaDinamicaVectorDeEnteros(&v_procesadores_activos,world_size);
			  		asignarMemoriaDinamicaVectorDeEnteros(&v_almacen_actividad,world_size);

			  		v_elementosDeVectorMinimosPorProcesador=ELEMENTOSVECTOR/(world_size-1);
					v_elementosRestantesADistribuir=ELEMENTOSVECTOR%(world_size-1);
					v_procesadoresQueRecibenElementosRestantes=v_elementosRestantesADistribuir;
					
					v_elemB_procesador=ELEMENTOSVECTOR/(world_size-1);	
					v_elemB_rest=ELEMENTOSVECTOR%(world_size-1);
					v_procRecibenBRestantes=v_elemB_rest;
					
					v_filasDeMatrizMinimasPorProcesador=FILASMATRIZ/(world_size-1);
		  		  	v_filasDeMatrizRestantesADistribuir=FILASMATRIZ%(world_size-1);
					v_procesadoresQueRecibenFilasRestantes=v_filasDeMatrizRestantesADistribuir;	

					v_estado_proc=1;

					
					switch(v_elementosRestantesADistribuir){
						case(0):
							   v_maximaCantidadDeElementos=v_elementosDeVectorMinimosPorProcesador	;
							   asignarMemoriaDinamicaVector(&XReceptor,v_maximaCantidadDeElementos);	
							   carga_balanceada(world_size,v_numeroDeProcesadoresActivos,v_elementosDeVectorMinimosPorProcesador,v_filasDeMatrizMinimasPorProcesador,v_elemB_procesador,v_procesadores_activos,v_almacen_actividad,vectorDeElementos,vectorDeSubindices,vectorFilas,vectorPrimerFila,vectorB,vec_indice_B)	;
						break;

						default:
								v_maximaCantidadDeElementos=v_elementosDeVectorMinimosPorProcesador+1;
								asignarMemoriaDinamicaVector(&XReceptor,v_maximaCantidadDeElementos);	
								carga_desbalanceada(world_size,v_numeroDeProcesadoresActivos,v_elementosDeVectorMinimosPorProcesador,v_filasDeMatrizMinimasPorProcesador,v_elemB_procesador,v_procesadoresQueRecibenElementosRestantes,v_procesadoresQueRecibenFilasRestantes,v_procRecibenBRestantes,v_procesadores_activos,v_almacen_actividad,vectorDeElementos,vectorDeSubindices,vectorFilas,vectorPrimerFila,vectorB,vec_indice_B);
	

							
						break;
					}

			break;
		}
	}

	if(procesador_maestro(rank)){

		switch(v_tipo_ejecucion){
			case(UNO_ACTIVO):
			break;   //

			default:
					for (int i = 1; i < world_size; i++)
					{
						vectorDeInfo[0]=v_procesadores_activos[i]; 
						vectorDeInfo[1]=vectorDeElementos[i];
						vectorDeInfo[2]=vectorDeSubindices[i];
						vectorDeInfo[3]=vectorFilas[i];
						vectorDeInfo[4]=vectorPrimerFila[i];
						vectorDeInfo[5]=vectorB[i];
						vectorDeInfo[6]=vec_indice_B[i];

						MPI_Send(vectorDeInfo,7,MPI_INT,i,INFO_PROCESADOR,MPI_COMM_WORLD);
					}
			break;
		}
	}else{
		asignarMemoriaDinamicaVectorDeEnteros(&vectorDeInfo,7);
		MPI_Recv(vectorDeInfo,7,MPI_INT,0,INFO_PROCESADOR,MPI_COMM_WORLD,&status);
		
		configurar_procesador(vectorDeInfo,&v_estado_proc,&v_elementosDeVectorDelProcesador,&v_indiceDelPrimerElemento,&v_filasDeMatrizDelProcesador,&v_indiceDeLaPrimerFila,&v_elemB_procesador,&v_indice_B_procesador);
	
		if (procesador_activo(v_estado_proc)){
			
		    asignarMemoriaDinamicaVector(&Xlocal,v_elementosDeVectorDelProcesador);
			asignarMemoriaDinamicaVector(&Xsiguiente,v_elementosDeVectorDelProcesador);
			asignarMemoriaDinamicaVector(&vectorDeErrores,v_elementosDeVectorDelProcesador);
			asignarMemoriaDinamicaVector(&X,ELEMENTOSVECTOR);  //QUE HACE ESTO ACA??
			asignarMemoriaDinamicaVector(&v_tiempos,TIEMPOS_MEDIDOS);
			asignarMemoriaDinamicaVector(&B,v_elemB_procesador);
			asignarMemoriaDinamicaMatriz(&A,v_filasDeMatrizDelProcesador);
		}
	}

	if (procesador_maestro(rank))
			printf("Lectura ... \n");
		
	if (procesador_activo(v_estado_proc)){
		v_inicioLectura=MPI_Wtime();	
	}

	switch(v_tipo_ejecucion){
		 case(UNO_ACTIVO):

		 		leerVector(B,1,v_elemB_procesador,v_elem_despl_B);
				leerVector(X,0,v_elementosDeVectorDelProcesador,v_elementosDesplazadosHastaIndice);
				leerMatrizBinariaParcial(rank,A,v_indiceDeLaPrimerFila,v_filasDeMatrizDelProcesador);
				
		 break;
		 default:
		 		if (procesador_maestro(rank)){
					leerVector(X,0,ELEMENTOSVECTOR,0);
		 		}else{
		 			if (procesador_activo(v_estado_proc)){
						
		 				leerVector(B,1,v_elemB_procesador,v_indice_B_procesador);
		 				leerMatrizBinariaParcial(rank,A,v_indiceDeLaPrimerFila,v_filasDeMatrizDelProcesador);
		 			}
		 		}
		 break; 
	}
	
	if (procesador_activo(v_estado_proc)){
		v_finalLectura=MPI_Wtime();	
	}
	
	//SINCRONIZACION DE PROCESADORES
	MPI_Barrier(MPI_COMM_WORLD);
	
	if (procesador_maestro(rank))
			printf("Ejecucion\n");

	if ( procesador_activo(v_estado_proc)){
		v_inicioJacobi=MPI_Wtime();
	}
		
	switch(v_tipo_ejecucion){
		case(UNO_ACTIVO):
				//EJECUCION SERIAL
					v_errorLocal=10;
				
					v_iteracion=0;
					while(v_errorLocal>COTADEERROR){
						//FILASMATRIZ SE PUEDE INTERCAMBIAR POR v_filasDeMatrizDelProcesador
			  			v_inicioIteracion=MPI_Wtime();
						for (i = 0; i < FILASMATRIZ; i++)
			  			{
			  				Xsiguiente[i]=0;
			  				for (j = 0; j < COLUMNASMATRIZ; j++)
			  				{
			  					if (i!=j)
			  					{
			  						Xsiguiente[i]=Xsiguiente[i] + A[i][j]*X[j] ;
			  					}
			  				}
			  				Xsiguiente[i]=(B[i] - Xsiguiente[i])/A[i][i];
			  				vectorDeErrores[i]=Xsiguiente[i] - X[i];
			  			}
						
			  			//CALCULO DEL ERROR
			  			v_errorLocal=calcularError(vectorDeErrores,ELEMENTOSVECTOR);
                                       
  						//ASIGNO A X LOS VALORES DE XSIGUIENTE
			  			for (i = 0; i < ELEMENTOSVECTOR; i++)
			  			{
			  				X[i]=Xsiguiente[i];
			  			}	

						v_finIteracion=MPI_Wtime();
						if (ITERACIONES==NULL)
						{
							ITERACIONES = (double*)malloc((v_iteracion+1)* sizeof(double));
						}else{
							ITERACIONES = (double*)realloc(ITERACIONES,  (v_iteracion+1)* sizeof(double));	
						}
					
						ITERACIONES[v_iteracion]=(v_finIteracion-v_inicioIteracion);
						v_iteracion=v_iteracion+1;
					
  					}
			break;

		default:
			 
			 if(procesador_activo(v_estado_proc)){
				
				v_errorLocal=10;
				v_esta_activo=1;	 
				v_iteracion=0;
				 

				//JACOBI
			 		
		  		while(v_errorLocal>COTADEERROR){
		  			if (procesador_maestro(rank))
					{		//REPARTIR A LOS PROCESOS ACTIVOS X 
						
							v_inicioIteracion=MPI_Wtime();
			  				for (i = 1; i < v_numeroDeProcesadoresActivos; i++)
			  				{
			  					
			  					MPI_Send(X,ELEMENTOSVECTOR,MPI_DOUBLE,i,ENVIO_X,MPI_COMM_WORLD);
			  				}

			  				//RECOGER LOS VALORES NUEVOS DE X (SEGUN CANTIDAD MAXIMA DE ELEMENTOS DE PROCESO)
			  				//SEGUN EL ORDEN QUE VAYAN TERMINANDO 
			                for (i = 1; i < v_numeroDeProcesadoresActivos;i++)
			  				{
			  					//RECIBO NUEVOS VALORES
			  			
			  					MPI_Recv(XReceptor,v_maximaCantidadDeElementos,MPI_DOUBLE,MPI_ANY_SOURCE,ENVIO_X_SIGUIENTE,MPI_COMM_WORLD,&status);
								v_elementosRecibidos=vectorDeElementos[status.MPI_SOURCE];
								v_indiceRecibido=vectorDeSubindices[status.MPI_SOURCE];
									
								//ASIGNAR VALORES A X SIGUIENTE SEGUN INDICE CORRESPONDIENTE
								asignarValoresRecibidosAXSiguiente(XReceptor,Xsiguiente,v_elementosRecibidos,v_indiceRecibido);
							}

							//CALCULO DE ERROR
							for (i = 0; i < ELEMENTOSVECTOR; i++)
			  				{
			  					vectorDeErrores[i]=(Xsiguiente[i]-X[i]);
			  				}
			  				v_errorLocal=calcularError(vectorDeErrores,ELEMENTOSVECTOR);
			  				
			  				//ASIGNAR NUEVOS VALORES DE X
			  				for (int i = 0; i < ELEMENTOSVECTOR; ++i)
			  				{
			  					X[i]=Xsiguiente[i];
			  				}

							v_finIteracion=MPI_Wtime();
							
							ITERACIONES = realloc(ITERACIONES,  (v_iteracion+1)* sizeof(double));
							ITERACIONES[v_iteracion]=(v_finIteracion-v_inicioIteracion);
							v_iteracion=v_iteracion+1;

							for (i = 1; i < v_numeroDeProcesadoresActivos; i++)
			  				{
			  					
			  				
								MPI_Send(&v_errorLocal,1,MPI_DOUBLE,i,ENVIO_ERROR,MPI_COMM_WORLD);
			  				}
		  				
		  				
		  			}else{

		  					//INICIO LOS VALORES DE LOS INDICES LOCALES
			  				v_indiceDelPrimerElementoLocal=v_indiceDelPrimerElemento;
			  				v_indiceDeLaPrimerFilaLocal=v_indiceDeLaPrimerFila;
			  			
			  				//RECIBIR X
			  				MPI_Recv(X,ELEMENTOSVECTOR,MPI_DOUBLE,0,ENVIO_X,MPI_COMM_WORLD,&status);

							asignarElementosAVectorLocal(Xlocal,X,v_elementosDeVectorDelProcesador,v_indiceDelPrimerElemento);
			  			
						  	//CALCULAR X SIGUIENTE
			  				for (i = 0; i < v_filasDeMatrizDelProcesador; i++)
			  				{
			  					Xsiguiente[i]=0;
			  					for (j = 0; j < COLUMNASMATRIZ; j++)
			  					{
			  						//EL ELEMENTO A(i,i) SE ENCUENTRA EN LA MATRIZ COMO A(i,indiceDeLaPrimerFilaLoca)
			  						if(j!=v_indiceDeLaPrimerFilaLocal){
			  								Xsiguiente[i]=Xsiguiente[i] + A[i][j] * X[j];
			  						}
			  					}
			  						
			  					Xsiguiente[i]=(B[i] -Xsiguiente[i])/A[i][v_indiceDeLaPrimerFilaLocal];
			  					
			  				    v_indiceDelPrimerElementoLocal++;
			  					v_indiceDeLaPrimerFilaLocal++;
								
							}
			  			
			  			    //MANDAR X SIGUIENTE   

			  				MPI_Send(Xsiguiente,v_elementosDeVectorDelProcesador,MPI_DOUBLE,0,ENVIO_X_SIGUIENTE,MPI_COMM_WORLD);
			  				//RECOBIR ERROR PARA INDICAR FIN DE CALCULO			
				  		    MPI_Recv(&v_errorLocal,1,MPI_DOUBLE,0,ENVIO_ERROR,MPI_COMM_WORLD,&status);
				  	}
				}
			}	
	}

	if( procesador_activo(v_estado_proc)){
		v_finalJacobi=MPI_Wtime();
	}
		
	MPI_Barrier(MPI_COMM_WORLD);
	
	//SE LIBERAN RECURSOS		
	switch(v_tipo_ejecucion){
			case(UNO_ACTIVO):
				
				    liberarMemoriaDinamicaVector(&Xsiguiente);
			  		liberarMemoriaDinamicaVector(&vectorDeErrores);
			  		liberarMemoriaDinamicaVector(&B);
			  		liberarMemoriaDinamicaMatriz(&A,v_filasDeMatrizDelProcesador);
			  		
				break;
			default:
					if (procesador_maestro(rank))
					{
						  liberarMemoriaDinamicaVectorDeEnteros(&vectorDeElementos);
				  		  liberarMemoriaDinamicaVectorDeEnteros(&vectorDeSubindices);  				
				  		  liberarMemoriaDinamicaVectorDeEnteros(&vectorDeInfo);
				  		  liberarMemoriaDinamicaVector(&Xsiguiente);
				  		  liberarMemoriaDinamicaVector(&vectorDeErrores);
				  		  
				  		
					}else{
						  if(procesador_activo(v_estado_proc)){
						  		liberarMemoriaDinamicaVector(&Xlocal);
				  		  		liberarMemoriaDinamicaVector(&Xsiguiente);
				  		  		liberarMemoriaDinamicaVector(&vectorDeErrores);
				  	
				  		  		liberarMemoriaDinamicaVectorDeEnteros(&vectorDeInfo);
				  		  		liberarMemoriaDinamicaVector(&B);
				  		  		liberarMemoriaDinamicaMatriz(&A,v_filasDeMatrizDelProcesador);
				  		}
				  			
					}
				
	}

	if( procesador_activo(v_estado_proc)){
		v_finalEjeucion=MPI_Wtime();  	

	}	
	
		
	switch(v_tipo_ejecucion){
			case(UNO_ACTIVO):
						v_maximo_lectura=(double)( v_finalLectura - v_inicioLectura);
				  		v_maximo_ejecucion=(double)(v_finalJacobi - v_inicioJacobi);
				  		v_maximo_total=(double)(v_finalEjeucion - v_inicioLectura);

				  		v_lectura_maestro=v_maximo_lectura;
						v_ejecucion_maestro=v_maximo_ejecucion;
						v_total_maestro=v_maximo_total;

						calcula_max_elem_vector(ITERACIONES,v_iteracion,&v_max_iteracion );
				  		printf("Procesamiento finalizado...\n");
				  		printf("Escribiendo solucion...\n");
				  		
				  		escribirSolucion(X,v_errorLocal,v_lectura_maestro,v_ejecucion_maestro,v_total_maestro,v_maximo_lectura,v_maximo_ejecucion,v_maximo_total,v_numeroDeProcesadoresActivos,v_max_iteracion);
				  		
				break;
			default:
				
				 if (procesador_activo(v_estado_proc)){
					
						v_maximo_lectura=(double)( v_finalLectura - v_inicioLectura);
			  			v_maximo_ejecucion=(double)(v_finalJacobi - v_inicioJacobi);
			  			v_maximo_total=(double)(v_finalEjeucion - v_inicioLectura);
			  				
			  			

			  			v_tiempos[0]=v_maximo_lectura;
			  			v_tiempos[1]=v_maximo_ejecucion;
			  			v_tiempos[2]=v_maximo_total;
						 
						if (procesador_maestro(rank))
						{
					
							v_lectura_maestro=v_maximo_lectura;
							v_ejecucion_maestro=v_maximo_ejecucion;
							v_total_maestro=v_maximo_total;
							cargar_matriz_de_tiempos(rank,v_tiempos,v_almacen_tiempos);
			  		   		for (i = 1; i < v_numeroDeProcesadoresActivos; ++i)
			  		   		{
			  		   			MPI_Recv(v_tiempos,3,MPI_DOUBLE,MPI_ANY_SOURCE,ENVIO_TIEMPOS,MPI_COMM_WORLD,&status);
			  		   			cargar_matriz_de_tiempos(status.MPI_SOURCE,v_tiempos,v_almacen_tiempos);
			  		   		}
			  		        calcula_max_elem_vector(ITERACIONES,v_iteracion,&v_max_iteracion );								 
			  		   		calcular_mayor_tiempo(&v_maximo_lectura,&v_maximo_ejecucion,&v_maximo_total, v_almacen_tiempos,v_numeroDeProcesadoresActivos);
			  		   		liberarMemoriaDinamicaVector(&v_tiempos );
			  				liberarMemoriaDinamicaMatriz(&v_almacen_tiempos,3);
			  		
			  				printf("Procesamiento finalizado...\n");
			  				printf("Escribiendo solucion...\n");
			  				
			  				escribirSolucion(X,v_errorLocal,v_lectura_maestro,v_ejecucion_maestro,v_total_maestro,v_maximo_lectura,v_maximo_ejecucion,v_maximo_total,v_numeroDeProcesadoresActivos,v_max_iteracion);		
							liberarMemoriaDinamicaVector(&X);
						}else{
						
	  						MPI_Send(v_tiempos,3,MPI_DOUBLE,0,ENVIO_TIEMPOS,MPI_COMM_WORLD);
	  					
	  						liberarMemoriaDinamicaVector(&v_tiempos );
						
						}
					}		
	}
	  		 	
  MPI_Finalize();

  return 0;
  	
}
