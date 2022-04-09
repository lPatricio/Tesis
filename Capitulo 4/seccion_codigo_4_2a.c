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