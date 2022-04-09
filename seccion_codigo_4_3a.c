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