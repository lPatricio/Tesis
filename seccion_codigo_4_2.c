bool  metodoDeJacobi(double** A,double* B,double* X,double *errorRetornado,int *iteraciones){
		   
		    *iteraciones=0;   
			double aux;
			*errorRetornado=100;
			double* vectorDeErrores;
			
			double*  Xsgte; 
			  
			int i,j;
			
			asignarMemoriaDinamicaVector(&vectorDeErrores);
			asignarMemoriaDinamicaVector(&Xsgte);
			
			while(*iteraciones<ITERACIONESMAXIMAS && *errorRetornado>=COTADEERROR){
				
				for(i=0;i<FILASMATRIZ;i++){
					aux=0;
					
					for(j=0;j<COLUMNASMATRIZ;j++){
						if(i!=j)
							aux=aux+ A[i][j]*X[j];
						
					}
					
					aux=( B[i]-aux )/A[i][i];	

					vectorDeErrores[i]=(aux-X[i]);
					Xsgte[i]=aux;
				}
			
				
				 *iteraciones=*iteraciones+1;
	             *errorRetornado=calculoError(vectorDeErrores);     
			
				for(i=0;i<ELEMENTOSVECTOR;i++){
					X[i]=Xsgte[i];
				}
			}
		
			if(*iteraciones<ITERACIONESMAXIMAS)
				return true;
			
			return false;
			
	}