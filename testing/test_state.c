#include "../state.h"
#include <assert.h>
#define BUFFER_SIZE	10

void
test_state(){
	state *s;
	assert(state_alloc(&s,BUFFER_SIZE)==0);
	assert(s->ll != NULL);
}


int 
main(){
	
	printf("All state tests succeeded\n");
	return 1;
}
