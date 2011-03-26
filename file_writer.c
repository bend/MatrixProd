#include "file_writer.h"


int
file_wopen(FILE** f, char* path){
	if((*f = fopen(path, "w"))==NULL)
		return -1;
	return 0;
}

int
file_write_matrix_size(FILE* f, unsigned int l, unsigned int c){
	if(fprintf(f,"%ux%u\n",l,c)<1){
		perror("Error while writing to file");
		return -1;
	}
	return 0;
}

int
file_write_line(FILE *f, mpz_t tab[], unsigned int size){
	unsigned int i;
	for(i=0; i<size; i++){
		if(i==size-1){
			if(gmp_fprintf(f,"%Zd\n",tab[i]) == 0)
				return -1;
		}else{
			if(gmp_fprintf(f,"%Zd ",tab[i]) == 0)
				return -1;
		}
	}
	return 0;
}


int
file_write_matrix(FILE* f, matrix* matr){
	mpz_t v;
	mpz_init(v);
	unsigned int i,j;
	if(file_write_matrix_size(f, matr->l, matr->c)==-1)
		return -1;
	
	for (i=0; i<matr->l; i++){
		for(j=0; j<matr->c;j++){
			matrix_get_elem_at(v,i,j,matr);
			if(gmp_fprintf(f," %Zd",v)==-1){
				perror("error while writing to file");
				return -1;
			}
		}
		if(gmp_fprintf(f,"\n")==-1){
			perror("error while writing to file");
			return -1;
		}
	}
	
	
	return 0;

}
