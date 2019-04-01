#include "vector.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

	/* this is the variable that will store the array, you can have
	 * a vector of any type! For example, you may write float *v = NULL, 
	 * and you'd have a vector of floats :-). NULL will have a size 
	 * and capacity of 0. additionally, vector_begin and vector_end will 
	 * return NULL on a NULL vector.
	 */
	int *v = NULL;

	(void)argc;
	(void)argv;		

	/* add some elements to the back */
	v_push_back(v, 10);
	v_push_back(v, 20);
	v_push_back(v, 30);

	/* and remove one too */
	v_pop_back(v);

	/* print out some stats about the vector */
	printf("pointer : %p\n",  (void *)v);
	printf("capacity: %lu\n", v_capacity(v));
	printf("size    : %lu\n", v_size(v));

	/* iterator over the vector using "iterator" style */
	if(v) {
		int * it;
		int i = 0;
		for(it = v_begin(v); it != v_end(v); ++it) {
			printf("v[%d] = %d\n", i, *it);
			++i;
		}
	}

	/* iterator over the vector standard indexing too! */
	if(v) {
		size_t i;
		for(i = 0; i < v_size(v); ++i) {
			printf("v[%lu] = %d\n", i, v[i]);
		}
	}		

	/* well, we don't have destructors, so let's clean things up */
	v_free(v);

	return 0;
}
