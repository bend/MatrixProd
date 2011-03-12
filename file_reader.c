#include "file_reader.h"

FILE*
file_open(FILE* f, char* path){
	f = fopen(path, "r");
	return f;
}

int
file_close(FILE* f){
	return fclose(f);
}

int
file_read_matrix_size(FILE* f, unsigned int *l, unsigned int *c){
	char x;
	char a;
	
	fscanf(f,"%c",&a);
	while(a == '\n'||a ==' '){
		fscanf(f,"%c",&a);
	}
	fseek(f, -1, SEEK_CUR);
	
	if(fscanf(f,"%d%c%d",l,&x,c) !=3)
	  	return -1;
	if(x!='x')
	  	return -1;
	return 0;
  
}

int
file_read_line(FILE* f, int tab[], unsigned int size){
	int i;
  	char t;
	for(i=0; i<size; i++)
	  	if(fscanf(f,"%d",&tab[i])==0)
		  	return -1;
	t = getc(f);
	if(t!='\n')
		return -1;
	return 0;
		  

}

int
file_read_matrix(FILE *f, matrix* matr, unsigned int l, unsigned int c){
	return -1;
}
