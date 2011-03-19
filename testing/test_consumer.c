#include "../consumer.h"
#include <assert.h>


void
test_consumer_on_manual_linked_list_2_elements() {
	matrix* matr,*m_result;
	state* state;
	int m1[]={ 3, 56, -2, 20, 4, 0 }, 
		m2[]={ 45, 34, 2, 2, 1, 1}, 
		result[]={ 247, 158, 62,   -50, -48, 16,     180, 136, 8 };

	/* initialise state
	 */
	if (state_alloc(&state)==-1){
			perror("Could not initialise state in test_consumer_on_manual_linked_list");
			exit(1);
	}
	
	/* First matrix:
	 *  3  56
	 * -2  20
	 *  4   0
	 */
	if (matrix_alloc(&matr,3,2)==-1){
		perror("Could not allocate m1 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m1);
	linked_list_add_last(state->ll, matr);

	/* Second matrix:
	 *  45  34  2
	 *   2   1  1
	 */
	if (matrix_alloc(&matr,2,3)==-1){
		perror("Could not allocate m2 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m2);
	linked_list_add_last(state->ll, matr);

	/* Expected result
	 *    247   158    62
	 *    -50   -48    16
	 *    180   136     8
	 *
	 *
	 * */
	matrix_alloc(&m_result, 3, 3);
	matrix_fill(m_result, result);

	/* start consumer */
	consumer_start(state);

	/* Check that the only matrix in the linked list is the result
	 */
	if (matrix_cmp(m_result, linked_list_get_first(state->ll))!=0){
		printf("Expected this matrix: \n");
		matrix_print(m_result);
		printf("But computed result is: \n");
		matrix_print(linked_list_get_first(state->ll));
	}
	assert(state->ll->head->next->next==state->ll->tail);
	assert(matrix_cmp(m_result, linked_list_get_first(state->ll))==0);
	assert(matrix_cmp(m_result, linked_list_get_last(state->ll))==0);


}

void
test_consumer_on_manual_linked_list_4_elements() {
	matrix* matr,*m_result;
	state* state;
	int m1[]={
               32 , -100 ,   46 ,   17,  
             -120 ,    1 ,   10 , -114,
                3 ,  -97 ,  -62 ,  -19,
              -71 ,  100 ,  -39 ,  -56,
               73 ,   80 ,   69 ,   -5},
		m2[]={ 
			  -104,   126 ,   47 ,  -21 ,   54 ,  -60,
			   117,   -98 ,   37 ,  123 ,   26 , -111,
			   -47,    90 ,   65 ,   22 ,   48 ,  122,
			   -28,  -104 ,  -68 ,  -20 ,   15 ,   -8},

		m3[]={ 
				97 ,  -64 ,  -64 , -106 ,  -70,   -32,   -58,  -126,   -62,   -54,
				52 , -103 , -108 ,   10 ,  -13,   -21,   -23,  -115,   118,    21,
				24 ,   93 ,   46 ,  -13 ,  -84,    88,    85,    -4,   -27,   -65,
			   -45 ,   26 ,   82 ,  121 ,  -14,   -89,   -82,    31,   104,   -15,
			   -80 ,  -75 , -121 ,  -73 ,    2,  -101,    18,  -108,  -118,    92,
			   -88 ,  -96 ,   28 ,  109 ,  104,   -20,    45,   -86,   109,  -120},
		m4[] = {
				45 ,   76,    29,
			   -39 ,  107,   -66,
				28 ,  -69,    90,
				-9 ,   93,   -31,
			   -64 ,  -32,   -59,
				59 ,  120,   111,
			   -42 , -109,    53,
			   106 , -108,   -92,
				76 ,  -97,    94,
			   -20 ,  -81,   -82},


		result[]={ 
			  -179138609,  -484370457,   408733558,
			   137477547,   357038556,   608813014,
				62805889,  -172808164,   143668513,
			   218286886,   596502822,  -187402570,
			  -111281023,    62583897,   -48414318};


	/* initialise state
	 */
	if (state_alloc(&state)==-1){
			perror("Could not initialise state in test_consumer_on_manual_linked_list");
			exit(1);
	}
	
	/* First matrix:
	 */
	if (matrix_alloc(&matr,5,4)==-1){
		perror("Could not allocate m1 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m1);
	linked_list_add_last(state->ll, matr);

	/* Second matrix:
	 */
	if (matrix_alloc(&matr,4,6)==-1){
		perror("Could not allocate m2 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m2);
	linked_list_add_last(state->ll, matr);

	/* Third matrix:
	 */
	if (matrix_alloc(&matr,6,10)==-1){
		perror("Could not allocate m2 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m3);
	linked_list_add_last(state->ll, matr);
	/* Fourth matrix:
	 */
	if (matrix_alloc(&matr,10,3)==-1){
		perror("Could not allocate m2 in test_consumer_on_manual_linked_list");
		exit(1);
	}
	matrix_fill(matr,m4);
	linked_list_add_last(state->ll, matr);

	/* Expected result
	 * */
	matrix_alloc(&m_result, 5, 3);
	matrix_fill(m_result, result);

	/* start consumer */
	consumer_start(state);

	/* Check that the only matrix in the linked list is the result
	 */
	if (matrix_cmp(m_result, linked_list_get_first(state->ll))!=0){
		printf("Expected this matrix: \n");
		matrix_print(m_result);
		printf("But computed result is: \n");
		matrix_print(linked_list_get_first(state->ll));
	}
	assert(state->ll->head->next->next==state->ll->tail);
	assert(matrix_cmp(m_result, linked_list_get_first(state->ll))==0);
	assert(matrix_cmp(m_result, linked_list_get_last(state->ll))==0);


}
int 
main(){
/*
	test_consumer_on_manual_linked_list_2_elements();
*/
	test_consumer_on_manual_linked_list_4_elements();
	printf("All consumer tests passed\n");
	return 0;
}
