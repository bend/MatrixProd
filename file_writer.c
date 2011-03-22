#include "file_writer.h"


int
file_wopen(FILE** f, char* path){
	if((*f = fopen(path, "w"))==NULL)
		return -1;
	return 0;
}

int
file_write_matrix_size(FILE* f, unsigned int l, unsigned int c){
	if(fprintf(f,"%ux%u\n",l,c)<1)
		return -1;
	return 0;
}

int
file_write_line(FILE *f, int tab[], unsigned int size){
	unsigned int i;
	for(i=0; i<size; i++){
		if(i==size-1){
			if(fprintf(f,"%d\n",tab[i]) == 0)
				return -1;
		}else{
			if(fprintf(f,"%d ",tab[i]) == 0)
				return -1;
		}
	}
	return 0;
}


int
file_write_matrix(FILE* f, matrix* matr){
	fprintf(f," ");
	printf("%d\n",matr->l);
	return 0;

}
