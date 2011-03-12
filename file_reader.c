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
	
	fscanf(f,"%c",&a);
	while(a == '\n'||a ==' '){
		fscanf(f,"%c",&a);
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
	for(i=0; i<size; i++)
	  	if(fscanf(f,"%d",&tab[i])==0)
		  	return -1;
	t = getc(f);
	if(t!='\n')
		return -1;
	return 0;
}

int
file_read_next_matrix(FILE *f, matrix* matr){
	unsigned int l, c, i;
	int tab[3000];
	if(file_read_matrix_size(f, &l, &c)==-1)
		return -1;
	printf("matrix size %d x %d\n",l,c);
	if(matrix_alloc(&matr,l,c)==-1)
		return -1;
	printf("allocated matrix size %dx%d",matr->l, matr->c);
	for(i=0; i<l; i++){
		if(file_read_line(f, tab, c)==-1){
			return -1;
		}else{
			printf("line %d : %d %d %d",i,tab[0],tab[1],tab[2]);
			if(matrix_fill_line(matr,i,tab)==-1)
				return -1;
		}
		printf("\n");
	}
	return 0;
}
