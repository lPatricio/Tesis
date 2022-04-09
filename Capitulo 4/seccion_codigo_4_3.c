void leerMatriz(double** A){
		//Descripcion:lee datos en una archivo de texto y 
		//los guarda en un puntero doble que representa una matriz.
		//Entrada:A,puntero doble de tipo double que representa una matriz.
	    //Salida: A,puntero doble de tipo double con datos cargados
		
		
		FILE *fuente;
		
		if((fuente=fopen(ARCHIVOMATRIZ,"rb"))==NULL){
			printf("No se ha encontrado el archivo.");
			return;
		}
		int i,j;
	
		for(i=0;i<FILASMATRIZ;i++){
			fread( &A[i][0] ,sizeof(double),COLUMNASMATRIZ, fuente );	
		}
		
		fclose(fuente);	
}