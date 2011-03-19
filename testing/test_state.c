#include "../state.h"
#include <assert.h>


void
test_state(){
	state *s;
	assert(state_alloc(&s)==0);
	assert(s->ll != NULL);
}


int 
main(){
	
	printf("All state tests succeeded\n");
	return 1;
}
