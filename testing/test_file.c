#include <assert.h>
#include "../file_reader.h"

#define PATH "./test.txt"


test_file_open_close(){
  	FILE *f,*f1;
	assert(file_open(f,PATH) == 0);
	assert(file_open(f1,"") == -1);
	assert(file_close(f) == 0);
	assert(file_close(f2) ==EOF);
}


test_file_read(){
  	FILE *f;
	int l,c;
	int tab[3000];
	int mat1[2][3] = {{123,47,80,},
	  				  {19,-14,86}};
	
	int mat2[3][1]={{12 },
	  				{-93},
					{42}};
	/*Matrix 1 */
	assert(file_open(f, PATH) == 0);
	assert(file_read_matrix_size(f,&l,&c)==0);
	assert(l==2);
	assert(c==3);

	assert(file_read_line(f,tab,c) >0);
	assert(mem_cmp(tab, mat1[0])==0);
	
	assert(file_read_line(f,tab,c) >0);
	assert(mem_cmp(tab, mat1[1])==0);
	
	/*Matrix 2*/
	assert(file_read_matrix_size(f,&l,&c)==0);
	assert(l==4);
	assert(c==4);

	assert(file_read_line(f,tab,c)>0);
	assert(memcmp(tab, mat2[0])==0);
	assert(file_read_line(f, tab,c)>0);
	assert(memcmp(tab, mat2[1])==0);
	assert(file_read_line(f,tab,c)>0);
	assert(memcmp(tab, mat2[2])==0);
	
	/*Matrix 3*/
	assert(file_read_matrix_size(f, &l,&c)==0);
	assert(l==4);
	assert(c==4);
	assert(file_read_line(f,tab,c)==-1);
	assert(file_read_line(f,tab,c)==0);
	assert(file_read_line(f,tab,c)==0);
	assert(file_read_line(f,tab,c)==0);
	
	/*Matrix 4*/
	assert(file_read_matrix_size(f, &l,&c)==0);
	assert(l==2);
	assert(c==2);
	assert(file_read_line(f,tab,c)==-1);
	assert(file_read_line(f,tab,c)==-1);
	assert(file_read_line(f,tab,c)==-1);
	
	/*Matrix 5*/
	assert(file_read_matrix_size(f, &l,&c)==0);
	assert(l==2);
	assert(c==2);
	assert(file_read_line(f,tab,c)==0);
	assert(file_read_line(f,tab,c)==0);

	/*Header matrix */
	assert(file_read_matrix_size(f, &l,&c));
}


int main(){
	test_file_open_close();
	test_file_read();
	printf("File tests succeded\n");
}
