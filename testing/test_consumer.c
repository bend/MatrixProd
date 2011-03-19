#include "../consumer.h"
#include <assert.h>


void
test_consumer_on_manual_linked_list() {
	matrix* matr,*m_result;
	state* state;
	int m1[]={ 3, 56, -2, 20, 4, 0 }, m2[]={ 45, 34, 2, 2, 1, 1}, result[]={ 247, 158, 62,   -50, -48, 16,     180, 136, 8 };

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
	matrix_print(m_result);
	assert(matrix_cmp(m_result, linked_list_get_first(state->ll))==0);
	assert(matrix_cmp(m_result, linked_list_get_last(state->ll))==0);


}

int 
main(int argc, char const * argv[]){
	test_consumer_on_manual_linked_list();
}
