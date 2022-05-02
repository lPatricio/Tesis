/*contiene declaracion de variables y funciones*/
#ifndef ARCHIVOHEADER
#define ARCHIVOHEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//CONSTANTES
#define CANTIDADMAXIMADEITERACIONES 1000
#define COTADEERROR 0.0000000000001
#define FILASMATRIZ 15000
#define COLUMNASMATRIZ 15000
#define ELEMENTOSVECTOR 15000

#define STRINGIZE(x) #x
#define NAME_FROM_MACROS(x, y, z)      x  STRINGIZE(y)"_" z   
#define ARCHIVOMATRIZ NAME_FROM_MACROS("Matrices y Vectores/",COLUMNASMATRIZ, "matrizDiagonalDominanteBinario.dat")
#define ARCHIVOSOLUCION NAME_FROM_MACROS("Matrices y Vectores/",ELEMENTOSVECTOR, "vectorSolucion.dat") 
#define ARCHIVOVECTORTERMINOSINDEPENDIENTES  NAME_FROM_MACROS("Matrices y Vectores/",ELEMENTOSVECTOR, "vectorDeTerminosIndependientes.dat") 
#define ARCHIVOMATRIZDEHILBERT NAME_FROM_MACROS("Matrices y Vectores/",FILASMATRIZ, "matrizDeHilbert.txt") 
#define ARCHIVODESTINOSOLUCION  NAME_FROM_MACROS("Soluciones/",ELEMENTOSVECTOR, "archivoSolucion.txt") 

//FUNCIONES
void asignarMemoriaDinamicaMatriz(double*** A);
void asignarMemoriaDinamicaVector(double** B);
void liberarMemoriaDinamicaMatriz(double*** A );
void liberarMemoriaDinamicaVector(double** B );
double calculoError(double* vectorAuxiliarDeErrores);
bool metodoDeJacobi(double** A,double* B,double* X,double *errorRetornado,int *iteracionesRealizadas);
void escribirSolucion(double error,int numeroDeIteraciones,double tiempoDeEjecucion);
void leerMatriz(double**  A);
void leerVector(double* B,int archivoFuente);
#endif
