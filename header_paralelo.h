/*contiene declaracion de variables y funciones*/
#ifndef JACOBIHEADERHV6
#define JACOBIHEADERHV6

#include <math.h>
#include <string.h>	
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DIM 13 
#define CANTIDADMAXIMADEITERACIONES 1000
#define COTADEERROR 0.0000000000001  
#define FILASMATRIZ 5       
#define COLUMNASMATRIZ 5
#define PASO COLUMNASMATRIZ/FILASMATRIZ
#define ELEMENTOSVECTOR 5
#define TIEMPOS_MEDIDOS 3
/*BANDERAS PARA LOS MSJ MPI*/
#define ENVIO_X 1
#define BANDERA_ACTIVIDAD 2
#define INFO_PROCESADOR 3
#define ENVIO_X_SIGUIENTE 4
#define ENVIO_TIEMPOS 5
#define ENVIO_ERROR 6
/*CONSTANSTES PARA TIPO DE EJECUCION -SOLO PARA PERMITIR REALIZAR UN CODIGO MAS CLARO-*/
#define UNO_ACTIVO 1
#define TODOS_ACTIVOS 2
#define FILAS_MATRIZ_MAS_UNO_ACTIVOS 3

#define STRINGIZE(x) #x
#define NAME_FROM_MACROS(x, y, z)      x  STRINGIZE(y)"_" z   
#define ARCHIVOMATRIZ NAME_FROM_MACROS("Matrices y Vectores/",COLUMNASMATRIZ, "matrizDiagonalDominanteBinario.dat")
#define ARCHIVOSOLUCION NAME_FROM_MACROS("Matrices y Vectores/",ELEMENTOSVECTOR, "vectorSolucion.dat") 
#define ARCHIVOVECTORTERMINOSINDEPENDIENTES  NAME_FROM_MACROS("Matrices y Vectores/",ELEMENTOSVECTOR, "vectorDeTerminosIndependientes.dat") 
#define ARCHIVOMATRIZDEHILBERT NAME_FROM_MACROS("Matrices y Vectores/",FILASMATRIZ, "matrizDeHilbert.txt") 
#define ARCHIVODESTINOSOLUCION  NAME_FROM_MACROS("Soluciones/",FILASMATRIZ, "archivoSolucion.txt") 



void asignarMemoriaDinamicaMatriz(double ***A,int filasReservadas);
void liberarMemoriaDinamicaMatriz(double*** A,int filasLiberadas );
void asignarMemoriaDinamicaVector(double** B,int cantidadDeElementos);
void asignarMemoriaDinamicaVectorDeEnteros(int** B,int cantidadDeElementos);
void asignarElementosAVectorLocal(double* X1,double* X2, int cantidadDeElementos, int indice);
void liberarMemoriaDinamicaVector(double** B );
void liberarMemoriaDinamicaVectorDeEnteros(int** B );
void asignarValoresRecibidosAXSiguiente(double* XRecibidos, double* Xsiguiente,int elementos,int indice);
float calcularError(double* vectorAuxiliarDeErrores,int elementosDelVector);
void escribirSolucion(double* X,double error,double a_lectura_maestro,double a_ejecucion_maestro,double a_total_maestro, double tiempoTranscurridoLectura,double tiempoTranscurridoJacobi,double tiempoTranscurridoTotal,int numeroProcesos,double a_max_iteracion);
void asignarMemoriaDinamica_parametrizada_Matriz(double ***A,int filasReservadas,int columnas_reservadas);
void cargar_matriz_de_tiempos(int a_proceso_origen,double* a_tiempos,double ** a_A);
void calcular_mayor_tiempo(double* a_max_lectura,double* a_max_ejecucion,double* a_max_total, double** a_A,int a_procesadores_activos);
void calcular_procesadores_activos(int* a_procesadores_activos,int a_cantidad_procesadores,int* a_tipo_ejecucion);
bool esta_el_procesador_activo(int a_procesador,int a_procesadores_activos);
bool recibe_elementos_restantes(int a_procesador,int a_elementos_restantes);
void calcular_elementos_del_procesador(int a_procesador,int a_elementos_minimos_procesador,int* a_elementos_del_procesador,int* a_elementos_desplazados_hasta_indice,int* a_indice_primer_elemento,int a_procesadores_restantes);
bool recibe_filas_restantes(int a_procesador,int a_filas_restantes);
void calcular_filas_del_procesador(int a_procesador,int a_filas_minimas_procesador,int* a_filas_del_procesador,int* a_filas_desplazadas_hasta_lectura,int* a_primer_fila,int a_procesadores_restantes);
bool procesador_maestro(int a_procesador) ;
void balanceo_sencillo(int a_cantidad_procesadores,int a_procesadores_act,int* a_max_cant_elem,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B);
void carga_balanceada(int a_cantidad_procesadores,int a_procesadores_act,int a_elementos_minimos_procesador,int a_filas_minimas_procesador,int a_elemt_B,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B);
void carga_desbalanceada(int a_cantidad_procesadores,int a_proc_act,int a_elementos_minimos_procesador,int a_filas_minimas_procesador,int a_elemt_B,int a_procesadores_elem_restantes,int a_procesadores_filas_restantes,int a_proc_B_restantes,int* a_procesadores_activos,int* a_actividades,int* a_elementos,int* a_subindices,int* a_filas,int* a_primer_fila,int* a_elem_B,int* a_indice_B);
bool procesador_activo(int a_estado_procesador);
void configurar_procesador(int* a_info_procesador,int* a_estado_proc,int* a_elementos_proc,int* a_primer_indice,int* a_filas_proc,int* a_primer_fila,int* a_elem_B,int* a_indice_B);
void calcula_max_elem_vector(double* B,int a_elementos,double* max_elemento );
void leerMatrizBinariaParcial(int rank,double** A,int filasDesplazadas,int filasDeLectura);
void leerVector(double* B,int a_archivoFuente,int a_elementos_b,int a_indice_B);

#endif
