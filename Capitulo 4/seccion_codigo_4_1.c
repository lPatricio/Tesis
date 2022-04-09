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