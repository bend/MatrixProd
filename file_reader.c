#include "file_reader.h"

int
file_open(FILE** f, char* path){
	if((*f = fopen(path, "r"))==NULL)
		return -1;
	return 0;
}

int
file_close(FILE* f){
	return fclose(f);
}

int
file_read_matrix_size(FILE* f, unsigned int *l, unsigned int *c){
	char x;
	char a;
	int r;
	fscanf(f,"%c",&a);
	while(a == '\n'||a ==' '|| a==EOF){
		r = fscanf(f,"%c",&a);
		if(r==EOF)
			return -1;
	}
	fseek(f, -1, SEEK_CUR);
	
	if(fscanf(f,"%u%c%u",l,&x,c) !=3)
	  	return -1;
	if(x!='x')
	  	return -1;
	return 0;
  
}

int
file_read_line(FILE* f, int tab[], unsigned int size){
	unsigned int i;
  	char t;
	int r;
	for(i=0; i<size; i++)
	  	r=fscanf(f,"%d",&tab[i]);
		if(r==0||r==EOF )
			return -1;
	t = getc(f);
	if(t!='\n')
		return -1;
	return 0;
}

int
file_read_next_matrix(FILE *f, matrix** matr){
	unsigned int l, c, i;
	int tab[3000];
	if(file_read_matrix_size(f, &l, &c)==-1)
		return -1;
	if(matrix_alloc(matr,l,c)==-1)
		return -1;
	for(i=0; i<l; i++){
		if(file_read_line(f, tab, c)==-1){
			return -1;
		}else{
			if(matrix_fill_line(*matr,i,tab)==-1)
				return -1;
		}
	}
	return 0;
}
