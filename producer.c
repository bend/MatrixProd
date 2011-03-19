#include "producer.h"




int
producer_init(char* filename,state* s,producer** p){
	*p = malloc(sizeof(producer));
	if(*p == NULL){
		perror("malloc failed");
		return -1;
	}
	if(file_open(&(*p)->f,filename) ==-1)
		return -1;
	(*p)->s = s;
	return 0;
}



