#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../file_reader.h"

#define PATH "./test.txt"
#define PATH2 "./test2.txt"
#define PATH3 "./test3.txt"


int
array_equal(int tab1[], int tab2[], int n){
	int i;
	for(i=0; i<n; i++)
		if(tab1[i] != tab2[i])
			return -1;
	return 0;
}

void
test_file_read(){
  	FILE *f,*f1,*f2;
	unsigned int l,c;
	int tab[3000];
	int mat1[2][3] = {{123,47,80,},
	  				  {19,-14,86}};
	
	int mat2[3][1]={{12 },
	  				{-93},
					{42}};
	int mat3[4] = {1, 2 ,3 ,4};
	/*Matrix 1 */
	f = file_open(f, PATH);
	assert(file_read_matrix_size(f,&l,&c)==0);
	assert(l==2);
	assert(c==3);

	assert(file_read_line(f,tab,c)== 0);
	assert(array_equal(tab, mat1[0],c)==0);
	
	assert(file_read_line(f,tab,c) ==0);
	assert(array_equal(tab, mat1[1],c)==0);
	
	/*Matrix 2*/
	assert(file_read_matrix_size(f,&l,&c)==0);
	assert(l==3);
	assert(c==1);

	assert(file_read_line(f,tab,c)==0);
	assert(array_equal(tab, mat2[0],c)==0);
	assert(file_read_line(f, tab,c)==0);
	assert(array_equal(tab, mat2[1],c)==0);
	assert(file_read_line(f,tab,c)==0);
	assert(array_equal(tab, mat2[2],c)==0);
	
	/*Matrix 3*/
	assert(file_read_matrix_size(f, &l,&c)==0);
	assert(l==4);
	assert(c==4);
	assert(file_read_line(f,tab,c)==0);
	assert(array_equal(tab,mat3,c)==0);
	assert(file_read_line(f,tab,c)==-1);
	file_close(f);

	/*Matrix 4*/
	f1 = file_open(f1, PATH2);
	assert(file_read_matrix_size(f1, &l,&c)==0);
	assert(l==2);
	assert(c==2);
	assert(file_read_line(f1,tab,c)==-1);
	file_close(f1);

	/*Matrix 5*/
	f2 = file_open(f2, PATH3);
	assert(file_read_matrix_size(f2, &l,&c)==0);
	assert(l==2);
	assert(c==2);
	assert(file_read_line(f2,tab,c)==0);
	assert(file_read_line(f2,tab,c)==0);

	/*Header matrix */
	assert(file_read_matrix_size(f2, &l,&c)==-1);
	assert(file_read_matrix_size(f2, &l,&c)==-1);
	assert(file_read_matrix_size(f2, &l,&c)==-1);
	file_close(f2);
 
}

	
int main(){
	test_file_read();
	printf("All file tests succeded\n");
	return 0;
}
