bool  metodoDeJacobi(double** A,double* B,double* X,double *errorRetornado,int *iteracionesRealizadas){
		   
		    *iteracionesRealizadas=0;   
			double aux;
			*errorRetornado=100;
			double* vectorDeErrores;
			
			double*  Xsgte; 
			  
			int i,j;
			
			asignarMemoriaDinamicaVector(&vectorDeErrores);
			asignarMemoriaDinamicaVector(&Xauxiliar);
			
			while(*iteracionesRealizadas<CANTIDADMAXIMADEITERACIONES && *errorRetornado>=COTADEERROR){
				
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
			
				
				 *iteracionesRealizadas=*iteracionesRealizadas+1;
	             *errorRetornado=calculoError(vectorDeErrores);     
			
				for(i=0;i<ELEMENTOSVECTOR;i++){
					X[i]=Xsgte[i];
				}
			}
		
			if(*iteracionesRealizadas<CANTIDADMAXIMADEITERACIONES)
				return true;
			
			return false;
			
	}